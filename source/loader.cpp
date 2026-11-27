// loader.cpp - the OpenGTANG loader (GtaBeamD1.asi), v2.85.
//
// Script Hook V loads an .asi once and can't unload it, so every new build of the mod used to need a GTA restart. This small
// .asi is what Script Hook V loads now. It loads the mod itself, GtaBeamD1_core.dll next to it, from a copy in
// %TEMP%\OpenGTANG, and runs it in its own Script Hook V script and Present callback. On "Restart the mod" (the F7 menu's
// Restart GTA/Mod section, or Ctrl+Shift+F7) the mod puts the game back, ends its threads, sockets and D3D11 hooks and returns;
// the loader stops calling it, lets GTA draw a few frames, lets it free its video memory, unloads it and loads
// GtaBeamD1_core.dll again. A new build copied over GtaBeamD1_core.dll (it isn't locked: the copy is what's loaded) is then
// used without restarting GTA. This file itself stays loaded until GTA closes: keep it small and change it rarely.

#include <windows.h>

#include <atomic>
#include <cstdarg>
#include <cstdint>
#include <cstdio>

#include "shv.h"

namespace
{
	using AttachFn = int (*)(HMODULE, int);
	using MainFn = int (*)();
	using PresentFn = void (*)(void*);
	using VoidFn = void (*)();
	constexpr int kCoreApi = 1;

	HMODULE               g_self = nullptr;
	HMODULE               g_core = nullptr;
	char                  g_base[MAX_PATH] = "";  // GtaBeamD1.asi's path without ".asi"
	char                  g_copy[MAX_PATH] = "";  // the loaded copy
	SRWLOCK               g_lock = SRWLOCK_INIT;  // Present (shared) against unloading (exclusive)
	PresentFn             g_present = nullptr;
	VoidFn                g_request = nullptr;
	std::atomic<uint64_t> g_frames{ 0 };
	std::atomic<bool>     g_retry{ false };
	int                   g_loads = 0;

	void LLog(const char* fmt, ...)
	{
		char path[MAX_PATH + 16];
		snprintf(path, sizeof(path), "%s_loader.log", g_base);
		FILE* f = fopen(path, "a");
		if (!f) return;
		SYSTEMTIME t;
		GetLocalTime(&t);
		fprintf(f, "[%02d:%02d:%02d.%03d] ", t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
		va_list ap;
		va_start(ap, fmt);
		vfprintf(f, fmt, ap);
		va_end(ap);
		fputs("\n", f);
		fclose(f);
	}

	bool GtaInFront()
	{
		DWORD pid = 0;
		GetWindowThreadProcessId(GetForegroundWindow(), &pid);
		return pid == GetCurrentProcessId();
	}

	// the copies of earlier loads (this session's, unloaded, and older sessions')
	void DeleteOldCopies(const char* dir)
	{
		char pat[MAX_PATH + 32];
		snprintf(pat, sizeof(pat), "%sGtaBeamD1_core_*.dll", dir);
		WIN32_FIND_DATAA fd;
		HANDLE           h = FindFirstFileA(pat, &fd);
		if (h == INVALID_HANDLE_VALUE) return;
		do {
			char p[MAX_PATH * 2];
			snprintf(p, sizeof(p), "%s%s", dir, fd.cFileName);
			DeleteFileA(p);  // (fails for one still loaded: fine)
		} while (FindNextFileA(h, &fd));
		FindClose(h);
	}

	MainFn   g_main = nullptr;
	VoidFn   g_final = nullptr;
	bool     g_missingLogged = false;

	bool LoadCore()
	{
		char core[MAX_PATH + 16];
		snprintf(core, sizeof(core), "%s_core.dll", g_base);
		if (GetFileAttributesA(core) == INVALID_FILE_ATTRIBUTES) {
			if (!g_missingLogged) LLog("%s is missing: put it next to GtaBeamD1.asi (it's tried again every few seconds)", core);
			g_missingLogged = true;
			return false;
		}
		g_missingLogged = false;
		char dir[MAX_PATH];
		const DWORD n = GetTempPathA(MAX_PATH, dir);
		if (!n || n > MAX_PATH - 16) return false;
		strcat(dir, "OpenGTANG\\");
		CreateDirectoryA(dir, nullptr);
		DeleteOldCopies(dir);
		snprintf(g_copy, sizeof(g_copy), "%sGtaBeamD1_core_%lu_%d.dll", dir, GetCurrentProcessId(), g_loads + 1);
		if (!CopyFileA(core, g_copy, FALSE)) {
			LLog("could not copy %s to %s (error %lu)", core, g_copy, GetLastError());
			return false;
		}
		HMODULE m = LoadLibraryA(g_copy);
		if (!m) {
			LLog("could not load %s (error %lu)", g_copy, GetLastError());
			DeleteFileA(g_copy);
			return false;
		}
		auto attach = reinterpret_cast<AttachFn>(reinterpret_cast<void*>(GetProcAddress(m, "OgCoreAttach")));
		auto main = reinterpret_cast<MainFn>(reinterpret_cast<void*>(GetProcAddress(m, "OgCoreMain")));
		auto present = reinterpret_cast<PresentFn>(reinterpret_cast<void*>(GetProcAddress(m, "OgCorePresent")));
		auto request = reinterpret_cast<VoidFn>(reinterpret_cast<void*>(GetProcAddress(m, "OgCoreRequestRestart")));
		auto fin = reinterpret_cast<VoidFn>(reinterpret_cast<void*>(GetProcAddress(m, "OgCoreFinal")));
		if (!attach || !main || !present || !request || !fin) {
			LLog("%s isn't an OpenGTANG core (an old GtaBeamD1.asi renamed?): not used", core);
			FreeLibrary(m);
			DeleteFileA(g_copy);
			return false;
		}
		const int api = attach(g_self, g_loads + 1);
		if (api != kCoreApi) {
			LLog("%s speaks loader version %d, this loader %d: not used (update GtaBeamD1.asi too and restart GTA)", core, api, kCoreApi);
			// (it has started its log only: nothing to put back)
			FreeLibrary(m);
			DeleteFileA(g_copy);
			return false;
		}
		++g_loads;
		g_core = m;
		g_main = main;
		g_final = fin;
		AcquireSRWLockExclusive(&g_lock);
		g_present = present;
		g_request = request;
		ReleaseSRWLockExclusive(&g_lock);
		LLog("load %d: %s (from %s)", g_loads, g_copy, core);
		return true;
	}

	void UnloadCore()
	{
		AcquireSRWLockExclusive(&g_lock);
		g_present = nullptr;
		g_request = nullptr;
		ReleaseSRWLockExclusive(&g_lock);
		// GTA draws a few frames without it (calls into its D3D11 hooks that were under way finish)
		const uint64_t  f0 = g_frames.load();
		const ULONGLONG t0 = GetTickCount64();
		while ((g_frames.load() - f0 < 3 || GetTickCount64() - t0 < 300) && GetTickCount64() - t0 < 5000) scriptWait(0);
		g_final();
		FreeLibrary(g_core);
		g_core = nullptr;
		g_main = nullptr;
		g_final = nullptr;
		DeleteFileA(g_copy);
		LLog("load %d unloaded (%llu frames, %llu ms)", g_loads, (unsigned long long)(g_frames.load() - f0), (unsigned long long)(GetTickCount64() - t0));
	}

	void LoaderMain()
	{
		LLog("OpenGTANG loader running");
		for (;;) {
			if (!LoadCore()) {
				const ULONGLONG t0 = GetTickCount64();
				while (!g_retry.exchange(false) && GetTickCount64() - t0 < 5000) scriptWait(250);
				continue;
			}
			g_main();  // (returns for Restart the mod)
			UnloadCore();
		}
	}

	void LoaderPresent(void* swapChain)
	{
		g_frames.fetch_add(1);
		// Ctrl+Shift+F7 with GTA in front: restart the mod (or, with none loaded, try loading it now)
		static bool keyWas = false;
		const bool  key = (GetAsyncKeyState(VK_F7) & 0x8000) && (GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_SHIFT) & 0x8000);
		const bool  press = key && !keyWas && GtaInFront();
		keyWas = key;
		AcquireSRWLockShared(&g_lock);
		if (press) {
			if (g_request) g_request();
			else g_retry.store(true);
		}
		if (g_present) g_present(swapChain);
		ReleaseSRWLockShared(&g_lock);
	}
}

extern "C" BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID)
{
	switch (reason) {
	case DLL_PROCESS_ATTACH: {
		g_self = instance;
		DisableThreadLibraryCalls(instance);
		GetModuleFileNameA(instance, g_base, MAX_PATH);
		if (char* dot = strrchr(g_base, '.')) *dot = 0;
		char path[MAX_PATH + 16];
		snprintf(path, sizeof(path), "%s_loader.log", g_base);
		DeleteFileA(path);  // (a new log each GTA session)
		scriptRegister(instance, LoaderMain);
		presentCallbackRegister(LoaderPresent);
		break;
	}
	case DLL_PROCESS_DETACH:
		presentCallbackUnregister(LoaderPresent);
		scriptUnregister(instance);
		break;
	}
	return TRUE;
}
