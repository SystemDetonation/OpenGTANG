# OpenGTANG

**Drive BeamNG.drive's soft-body cars, trucks and motorcycles in GTA V's world.**

OpenGTANG is a fork of [GTA x Beam](https://github.com/Treto420/GTANG) by **Treto420** (MIT licence). GTA V runs the world, the walking and the guns. BeamNG.drive runs the car. Both games run at the same time and talk to each other on your PC. In GTA you see and drive your BeamNG car, with its real crumple, on GTA's streets, and GTA's traffic, people and lamp posts react to it.

All of that is Treto420's work. OpenGTANG adds motorcycles, an in-game menu, a one-button car setup, a hot-reloading mod, and much more coming soon (see [What OpenGTANG adds](#what-opengtang-adds)). The original mod's full guide is in **[ORIGINAL_README.md](ORIGINAL_README.md)**, kept as Treto420 wrote it: how it works, tips, what works, known issues and all the settings.

> Single-player only (story mode). Script Hook V closes GTA V in GTA Online. Free, non-commercial fan project; not affiliated with Rockstar Games, BeamNG GmbH or Treto420.

## Contents
- [What OpenGTANG adds](#what-opengtang-adds)
- [Requirements](#requirements)
- [Download](#download)
- [Install](#install)
- [First drive](#first-drive)
- [Updating](#updating)
- [Uninstall](#uninstall)
- [Keys](#keys-in-gta)
- [The F7 menu](#the-f7-menu)
- [Settings](#settings)
- [Known issues](#known-issues)
- [Troubleshooting and bug reports](#troubleshooting-and-bug-reports)
- [Building from source](#building-from-source)
- [Credits and licences](#credits-and-licences)

## What OpenGTANG adds
New in **2.84**:
- **Motorcycles.** BeamNG bikes ride on GTA bikes, with the lean, the rider's pose, getting off and on, and GTA's crash ejection.

New in **2.85**:
- **In-game menu (F7).** The main switches and actions, saved to the ini as you change them.
- **Get car from BeamNG.** One button: exports your BeamNG car, gets you the GTA vehicle that matches it (spawned under you if you're on foot) and puts the BeamNG car on it. Then F10 drives.
- **Auto-match.** The hidden GTA vehicle is picked by kind (BeamNG's Body Style: sedan, pickup, bus, chopper, wheel loader...), then by where you'd sit, then by size. Each pick is remembered per BeamNG vehicle.
- **Restart GTA/Mod.** The bottom of the F7 menu restarts GTA V, or reloads the mod without closing GTA (also Ctrl+Shift+F7). A new mod build is picked up live.
- **Seat adjust** works with `PuppetSolid=1`.
- **GTA's bikes** get crash boxes in BeamNG.
- **Fixes:**
  - BeamNG 0.40's driver seat.
  - Bikes that lean on their stand.
  - Heavy machinery: parts under two parents, wide tyres.
  - Right-side wheels spinning backwards.

## Requirements
- **GTA V Legacy** for PC (Steam, Rockstar Games Launcher or Epic), in story mode. Not the Enhanced edition.
- **[Script Hook V](http://www.dev-c.com/gtav/scripthookv/)** with its ASI loader (`dinput8.dll`). It isn't included: get it from its own site, in the version for your GTA update.
- **BeamNG.drive** 0.40 or newer.
- A PC that can run both games at once. 8 GB of video memory or more is recommended; video memory is what runs out first.

## Download
Get **`OpenGTANG_v2.85.zip`** from **[Releases](https://github.com/SystemDetonation/OpenGTANG/releases/latest)**. Don't use the green **Code** button: that's the source code. Unzip it anywhere.

Inside:
```
OpenGTANG_v2.85\
  GTA\        -> goes into your GTA V folder
  BeamNG\     -> the gtabridge folder goes into BeamNG's mods folder
  INSTALL.txt, README.md, ORIGINAL_README.md, LICENSE, licences\
```

## Install
### 1. Script Hook V (once)
1. Download Script Hook V from [dev-c.com](http://www.dev-c.com/gtav/scripthookv/).
2. From its `bin` folder, copy `ScriptHookV.dll` and `dinput8.dll` into your **GTA V folder** (the one with `GTA5.exe`).

Where the GTA V folder usually is:

| Store | Folder |
|---|---|
| Steam | `C:\Program Files (x86)\Steam\steamapps\common\Grand Theft Auto V` (or Steam: right-click GTA V, **Manage**, **Browse local files**) |
| Rockstar Games Launcher | `C:\Program Files\Rockstar Games\Grand Theft Auto V` |
| Epic Games | `C:\Program Files\Epic Games\GTAV` |

### 2. The GTA V part
Copy **everything in the zip's `GTA` folder** into your GTA V folder, next to `GTA5.exe`:

| File | What it is |
|---|---|
| `GtaBeamD1.asi` | The OpenGTANG loader. Script Hook V loads it. |
| `GtaBeamD1_core.dll` | The mod itself. The loader loads it. Both files are needed. |
| `GtaBeamD1.ini` | Settings, with comments. |
| `GtaBeamD1_props.json`, `GtaBeamD1_surfaces.json`, `GtaBeamD1_traffic.json`, `GtaBeamD1_weapons.json` | Game content: props, ground grip, traffic masses, weapon damage. |

### 3. The BeamNG.drive part
1. Open this folder: paste `%LOCALAPPDATA%\BeamNG\BeamNG.drive\current\mods\unpacked\` into Explorer's address bar and press Enter. If `unpacked` doesn't exist yet, make it.
2. Copy the zip's **`BeamNG\gtabridge`** folder into it. The result is `...\mods\unpacked\gtabridge\lua\...`, `...\gtabridge\scripts\...` and `...\gtabridge\vehicles\...`.
3. In BeamNG, check that **gtabridge** is enabled in the **Mods** menu.

### 4. GTA's graphics setting
Turn **MSAA off** in GTA's graphics settings. With MSAA on, the car can't be drawn inside GTA's frame and can look dark, see-through or glitchy.

## First drive
1. **Start BeamNG first.** Load the level **Grid, Small, Pure** (small and light) and spawn your car or bike.
2. **Start GTA V** in story mode. A message says the mod has loaded.
3. Press **F7** and pick **Get car from BeamNG**. The first export takes a while.
4. Press **F10** to drive: BeamNG's physics drive the car, with your own BeamNG controls. **F10** again stops.

The classic keys still work: **Shift+F11** gets the car, **F11** puts it on the GTA car you're in, **F10** drives.

**Tip:** run BeamNG small and light (window mode, 1280x720, the lowest graphics settings). You only see GTA's picture, so BeamNG's graphics are wasted video memory. More tips are in [ORIGINAL_README.md](ORIGINAL_README.md#tips).

## Updating
**From an older OpenGTANG**, or **from Treto420's GTA x Beam (2.77, 2.83)**:
1. Back up your `GtaBeamD1.ini` if you changed settings.
2. Copy the zip's `GTA` files into the GTA V folder and say yes to replacing. GTA x Beam's single `GtaBeamD1.asi` is replaced by the OpenGTANG loader, and `GtaBeamD1_core.dll` is new.
3. Copy `BeamNG\gtabridge` over the old one in `mods\unpacked` and say yes to replacing. Restart BeamNG: the BeamNG mod changed in 2.85.
4. Put your own values back in the new `GtaBeamD1.ini`. An old ini also still works: settings it doesn't have use their defaults.

Later OpenGTANG builds can be swapped in without closing GTA: copy a new `GtaBeamD1_core.dll` over the old one and press **Ctrl+Shift+F7**. A new `GtaBeamD1.asi` still needs a GTA restart.

## Uninstall
- GTA V folder: delete `GtaBeamD1.asi`, `GtaBeamD1_core.dll`, every `GtaBeamD1*` file (ini, json, logs, txt), and the `GtaBeamD1_map` folder (the saved ground of GTA's world).
- BeamNG: delete `%LOCALAPPDATA%\BeamNG\BeamNG.drive\current\mods\unpacked\gtabridge` and `...\current\gtabridge` (exports and the log).
- Remove Script Hook V (`ScriptHookV.dll`, `dinput8.dll`) only if no other mod uses it.

## Keys (in GTA)
| Key | What it does |
|---|---|
| **F7** | OpenGTANG menu (see below) |
| **Ctrl+Shift+F7** | Restart the mod without closing GTA (loads a new `GtaBeamD1_core.dll` if there is one) |
| **Shift+F11** | Get the car from BeamNG (export). Do it again after you change the car in BeamNG. |
| **F11** | Put the BeamNG car on the GTA car you're in or next to (again: take it off) |
| **F10** | Drive mode on/off: BeamNG's physics drive the car |
| **Shift+F10** | On-screen drive check (what goes to BeamNG and back) |
| **Ctrl+Shift+F10** | Seat adjust in drive mode: arrow keys and Page Up / Page Down, again to save |
| **Ctrl+F9** | Crash damage to you on/off (off by default) |
| **Ctrl+F10** | Timing recording (only for bug reports) |
| **Ctrl+F11** | Re-read the ini and json files without restarting |
| **Ctrl+Shift+F11** | Show cars: park the BeamNG car on a GTA car and keep it there (up to 4) |
| **Ctrl+Shift+F12** | View modes (for testing) |
| **D-pad down** | Swap the controller between GTA (aim, shoot) and BeamNG (drive) while driving |

Driving uses your own BeamNG controls and bindings (gears, clutch, drive modes).

## The F7 menu
Up / Down pick, Left / Right change, Enter does it, Backspace or F7 closes. Changes are used at once and saved to `GtaBeamD1.ini`. Settings that drive mode reads when it starts are locked while you drive.

- **Car**:
  - **Get car from BeamNG** (all in one).
  - Export only.
  - Put on / show / take off.
  - Drive mode.
  - Auto-match hidden car.
  - **Match hidden car now**: forgets the remembered pick and picks again.
- **Crashes and world**: crash damage to you, GTA's world reacts (`PuppetSolid`), traffic crash boxes, weapons, props, dents.
- **Driving**: BeamNG gravity, speed gauge, pause sync, tyre smoke, seat adjust, and what seat adjust moves.
- **Bikes**: lean steer, full lean, lean feedback.
- **Other**: reload the ini and json files, close.
- **Restart GTA/Mod** (in red, at the bottom). Each button asks Yes / No first:
  - **Restart Grand Theft Auto V?** stops drive mode, closes GTA and starts it again: through Steam for the Steam version, else with `PlayGTAV.exe`. Unsaved story progress is lost. If it doesn't come back for your launcher, set `RestartGtaCommand` in the ini to the link or .exe that starts your GTA.
  - **Restart the OpenGTANG mod?** stops drive mode, takes the car off, unloads the mod and loads it again, without closing GTA.

## Settings
Everything is in `GtaBeamD1.ini`, with comments. The original settings are explained in [ORIGINAL_README.md](ORIGINAL_README.md#settings). Added by OpenGTANG:
- `MenuKey=0x76`: the menu's key (F7).
- `AutoMatchCar=0`: `1` makes F11 swap the GTA car for the matching one too. The menu's Get car always matches.
- `AutoMatchModels=`: the GTA models auto-match picks from. Empty: the built-in list, from cars and bikes to buses and heavy machinery.
- `SeatMoves=gta`: with `PuppetSolid=1`, seat adjust moves the hidden GTA car and you, so the BeamNG car stays on its wheels. `beamng`: it moves the drawn car instead.
- `TrafficProxies=5`: crash boxes in BeamNG for GTA's traffic, including one bike-size box.
- `RestartGtaCommand=`: what Restart GTA starts. Empty: Steam's GTA V Legacy (`steam://rungameid/271590`), else `PlayGTAV.exe`.
- `BikeLeanSteer`, `BikeLeanFullDeg`, `BikeLeanFeedback`: how a GTA bike follows BeamNG's lean.

Picks made by auto-match are kept in `GtaBeamD1_carmatch.txt` next to GTA, and GTA's measured model sizes in `GtaBeamD1_carsizes.txt`.

## Known issues
The original mod's known issues are in [ORIGINAL_README.md](ORIGINAL_README.md#known-issues). In OpenGTANG:
- Auto-match deletes the GTA car it replaces (unless someone else is in it).
- GTA has no close match for some BeamNG vehicles (a 12 m wheel loader gets GTA's Bulldozer). The closest of the same kind is used.
- With `PuppetSolid=1` you sit in the GTA car's seat in first person, not BeamNG's. Auto-match picks the closest seat, and seat adjust fine-tunes it.
- **Restart GTA** was tested with the Steam version. The Rockstar and Epic versions are started with `PlayGTAV.exe`; if that doesn't work for yours, set `RestartGtaCommand`.

## Troubleshooting and bug reports
- **Nothing happens in GTA**:
  - Check that Script Hook V is installed and matches your GTA update: `ScriptHookV.log` in the GTA folder.
  - Check that both `GtaBeamD1.asi` and `GtaBeamD1_core.dll` are next to `GTA5.exe`.
  - `GtaBeamD1_loader.log` says whether the loader found and loaded the mod.
- **"Asking BeamNG to export" never finishes**: start BeamNG first, check that gtabridge is enabled in BeamNG's Mods menu, and spawn a car.
- **The car looks dark or see-through**: turn MSAA off.

Please attach both logs to bug reports ([Issues](https://github.com/SystemDetonation/OpenGTANG/issues)):
- `GtaBeamD1.log`, in the GTA V folder.
- `gtabridge_log.txt`, in `%LOCALAPPDATA%\BeamNG\BeamNG.drive\current\gtabridge\`.

## Building from source
The source is in `source\`. The mod is two files:
- `GtaBeamD1.asi`, from `loader.cpp`: a small loader. Script Hook V loads it once and can't unload it.
- `GtaBeamD1_core.dll`, from `GtaBeamD1.cpp` + `carmodel.cpp`: the mod itself. The loader runs a copy of it from `%TEMP%\OpenGTANG`, so the file in the GTA folder isn't locked and a new build loads with Ctrl+Shift+F7.

To build:
- **Visual Studio 2022:** run `source\build_vs2022.bat`. It needs the Script Hook V SDK's `ScriptHookV.lib` in `source\sdk\lib\`.
- **zig** (`pip install ziglang`):
  ```
  python -m ziglang c++ -target x86_64-windows-gnu -std=c++17 -O2 -c -o build\GtaBeamD1.o GtaBeamD1.cpp
  python -m ziglang c++ -target x86_64-windows-gnu -std=c++17 -O2 -c -o build\carmodel.o carmodel.cpp
  python -m ziglang c++ -target x86_64-windows-gnu -std=c++17 -O2 -c -o build\loader.o loader.cpp
  python -m ziglang c++ -target x86_64-windows-gnu -std=c++17 -O2 -shared -o build\GtaBeamD1_core.dll build\GtaBeamD1.o build\carmodel.o build\ScriptHookV.lib -luser32 -lws2_32
  python -m ziglang c++ -target x86_64-windows-gnu -std=c++17 -O2 -shared -o build\GtaBeamD1.asi build\loader.o build\ScriptHookV.lib -luser32
  ```
- `-DGTANG_STANDALONE` builds the old single `GtaBeamD1.asi` (no loader, no mod restart). The tests in `source\test\` use it: a fake Script Hook V and a fake BeamNG for runs under Wine (`build_all.sh`). They test the code, not GTA's physics.

## Credits and licences
- **[GTA x Beam](https://github.com/Treto420/GTANG) by Treto420**: the mod this is built on. MIT licence ([LICENSE](LICENSE)).
- **OpenGTANG changes** by SystemDetonation, under the same MIT licence.
- [Script Hook V](http://www.dev-c.com/gtav/scripthookv/) by Alexander Blade (not included).
- [cgltf](https://github.com/jkuhlmann/cgltf) (MIT), [stb_image](https://github.com/nothings/stb) (MIT / public domain), [bcdec](https://github.com/iOrange/bcdec) (MIT / Unlicense).
- Inspired by [SkyCraft](https://github.com/chasmlol/SkyCraft) (Skyrim x Minecraft passthrough).
- Licence texts are in `licences\`.
- No Rockstar or BeamNG game files are included. The mod reads your own installs at run time.
