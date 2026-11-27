# GTA x Beam

**Drive BeamNG.drive's soft-body cars in GTA V's world.**

> **OpenGTANG** is a fork of [Treto420's GTA x Beam](https://github.com/Treto420/GTANG) (MIT). It adds motorcycles (2.84); an in-game menu with one-button setup, a hidden GTA vehicle matched to your BeamNG one by kind, seat position and size, crash boxes for GTA's bikes, and fixes for heavy machinery, wide tyres, right-side wheel spin and seat adjust (2.85). Everything else below is the original mod's.

GTA V runs the world, the walking and the guns. BeamNG.drive runs the car. Both games run at the same time and talk to each other on your PC. In GTA you see and drive your BeamNG car, with its real crumple, on GTA's streets, and GTA's traffic, people and lamp posts react to it like they would to a normal GTA car.

> Single-player only (story mode). Script Hook V closes GTA V in GTA Online. Free, non-commercial fan project; not affiliated with Rockstar Games or BeamNG GmbH.

## Quick start (5 minutes)
1. **Download** `GTA_X_BEAM_v2.77.zip` from [Releases](https://github.com/Treto420/GTANG/releases/latest) (not the green **Code** button: that's the source code) and unzip it.
   - For **2.83** (newer than that release): use the green **Code** button, **Download ZIP**, and take the `GTA` and `BeamNG` folders from it.
2. **GTA V files:** copy everything in the `GTA` folder into your GTA V folder (the one with `GTA5.exe`).
3. **BeamNG mod:** copy the `BeamNG\gtabridge` folder into `%LOCALAPPDATA%\BeamNG\BeamNG.drive\current\mods\unpacked\` (paste that path into Explorer's address bar). Say yes to replacing files.
4. **Start BeamNG first.** Load the level **Grid, Small, Pure** and spawn your car.
5. **Start GTA V** (story mode). Get in a GTA car about the **same size** as your BeamNG car (see Tips).
6. In GTA press **Shift+F11** (gets your car from BeamNG; the first time takes a while), then **F11** (puts it on your GTA car), then **F10** (drive).
   - **Or the OpenGTANG way:** press **F7** and pick **Get car from BeamNG**. It exports your car, gets you the GTA vehicle that matches it (spawned under you if you're on foot) and puts the BeamNG car on it. Then press **F10**.
7. **Turn MSAA off** in GTA's graphics settings. With MSAA on, the car can't be drawn inside GTA's frame and can look dark, see-through or glitchy.

## Requirements
- GTA V **Legacy** for PC (not the Enhanced edition), story mode, with [Script Hook V](http://www.dev-c.com/gtav/scripthookv/) and its ASI loader (`dinput8.dll`).
- BeamNG.drive (made on 0.40).
- A PC that can run both games at once. 8 GB of video memory or more is recommended; video memory is what runs out first.

## Keys (in GTA)
| Key | What it does |
|---|---|
| **F7** | In-game menu (2.85): the main switches and actions, saved to the ini as you change them. Its **Get car from BeamNG** does the whole setup: exports the car, gets you the GTA vehicle closest to its size (spawned where you stand if you're on foot) and puts the BeamNG car on it, so F10 is all that's left |
| **Shift+F11** | Get the car from BeamNG (export). Do it again after you change the car in BeamNG. |
| **F11** | Put the BeamNG car on the GTA car you're in or next to (press again to take it off) |
| **F10** | Drive mode on/off: BeamNG's physics drive the car |
| **Shift+F10** | On-screen drive check (what goes to BeamNG and back) |
| **Ctrl+Shift+F10** | Seat adjust in drive mode: arrow keys and Page Up / Page Down, press again to save |
| **Ctrl+F9** | Crash damage to you on/off (off by default, 2.81) |
| **Ctrl+F10** | Timing recording (only for bug reports) |
| **Ctrl+F11** | Re-read the ini and json files without restarting |
| **Ctrl+Shift+F11** | Show cars: park the BeamNG car on a GTA car and keep it there (up to 4) |
| **Ctrl+Shift+F12** | View modes (for testing) |
| **D-pad down** | Swap the controller between GTA (aim, shoot) and BeamNG (drive) while driving |

Driving uses your own BeamNG controls and bindings (gears, clutch, drive modes).

## Tips
- **Pick a GTA car the same size as your BeamNG car.** GTA's traffic, people and props hit an invisible GTA car hidden under your BeamNG car. If the GTA car is smaller, things go into your BeamNG car before they react; if it's bigger, they react before they touch it. A trainer such as Menyoo makes it easy to spawn the right one (a sedan for a sedan, a jeep for a lifted truck). **Or let the mod pick it** (see Auto-match below).
- **Auto-match** (2.85; F7 menu's **Get car from BeamNG**, or `AutoMatchCar=1` for F11). The mod picks the GTA vehicle in three steps:
  1. **Same kind.** BeamNG's own vehicle info (its "Body Style": Sedan, Hatchback, Pickup, Bus, Chopper, Sport bike, Wheel Loader...) decides the GTA kind: a chopper gets a GTA chopper, a bus a bus, a wheel loader heavy machinery. GTA bikes are sorted by hand into choppers, cruisers, sport bikes, dirt bikes and scooters.
  2. **Where you sit.** A hidden copy of your character sits in the closest GTA vehicles of that kind, and the one whose driver's head lands nearest BeamNG's driver seat wins (typically within 10-20 cm for cars). Vehicles without a driver's camera in BeamNG (like many motorcycle mods) skip this step.
  3. **Size**, and a GTA model your BeamNG vehicle is named after wins outright (`gta4b_bati` gets the Bati).

  Each pick is remembered per BeamNG vehicle in `GtaBeamD1_carmatch.txt`. **Match hidden car now** in the F7 menu forgets it and picks again. The first match measures GTA's models, which takes a few seconds once.
- **Motorcycles** (2.84): export a BeamNG bike and ride a GTA motorcycle. The rider leans with BeamNG's lean, GTA still throws you off in a crash, and you can get off and back on.
- **Seat adjust** (Ctrl+Shift+F10 in drive mode, or the F7 menu): moves you in the car, saved per BeamNG vehicle. Since 2.85 it also works with `PuppetSolid=1`: it moves the hidden GTA car (and you in it), so the drawn car stays on its wheels where BeamNG has it. GTA's traffic and props then meet the hidden car that far from the drawn one.
- **Run BeamNG small and light.** Window mode at 1280x720 with the lowest graphics settings. You only see GTA's picture, so BeamNG's graphics are wasted video memory.
- **Start BeamNG first**, on Grid, Small, Pure, with only your car spawned.
- **The first drive in an area is slower.** GTA's ground is measured and built in BeamNG as you go. It's saved in `GtaBeamD1_map\` next to GTA, so later drives there are instant.
- **Controller:** a PlayStation pad works through DS4Windows.

## What works
- **Your BeamNG car in GTA,** drawn with its paint, materials, glass and lights, in GTA's light, shadows and reflections.
- **BeamNG's physics.** GTA's streets, hills, walls and ground surfaces are built in BeamNG, so the car grips, crumples and breaks the BeamNG way. Since 2.81 (`PuppetNoMap=1`) only BeamNG meets walls, kerbs and solid posts, so slow wall hits bend the bumper too.
- **GTA's world reacts the vanilla way** (`PuppetSolid=1`, new in 2.77). GTA's cars get pushed and dented, people ragdoll, lamp posts break and bins fly, and your BeamNG car takes the hit.
- **Traffic crashes crumple your car** (`TrafficProxies=4`, new in 2.83). A GTA car about to meet yours gets a box in BeamNG at its place, with a car's size and weight. BeamNG resolves that crash, so your car really hits something, and GTA's car is shoved the way its box was.
- **Real damage on the car.** BeamNG's dents, broken glass, lost bumpers and wheels show in GTA.
- **GTA's guns.** Bullets dent the car, leave holes, pop tyres and break windows. Explosions push it and set it on fire; a car that blows up becomes a charred wreck.
- **On foot.** Get out, walk around the car, shoot it. Get back in and keep driving.
- **Show cars** (Ctrl+Shift+F11), **pause sync** (pausing one game pauses the other), **BeamNG's engine sound** and GTA's radio on the phone.

## Known issues
- Things react to GTA's hidden car, not the exact shape of your BeamNG car (see Tips). The parts of your BeamNG car that stick out past the GTA car crumple against walls BeamNG's way; GTA's people and signs push your car and dent it at the contact point.
- Traffic (2.83): the box in BeamNG is a hard block, so hits are harsher than car on car, and the GTA car you hit shows no dent yet. Trucks and buses still crash the 2.82 way (a push and a small dent). GTA's bikes get a bike-size box since 2.85 (`TrafficProxies=5` and the 5th `proxyPool` box). The first F10 of a BeamNG session waits about 10 seconds while the boxes are made.
- Auto-match (2.85) deletes the GTA car it replaces (unless someone else is in it). GTA has no close match for some BeamNG vehicles (a 12 m wheel loader gets GTA's Bulldozer); the closest of the same kind is used.
- With `PuppetSolid=1` you sit in the GTA car's seat in first person, not BeamNG's (Auto-match picks the GTA vehicle whose seat is closest; seat adjust fine-tunes it).
- MSAA in GTA's graphics settings must be off (the log and an on-screen message say so when it's on).
- Some hillsides and bridge decks can have holes or show up a few seconds late.
- The camera can lag a little at low speed.
- Crashes don't hurt you by default (2.81). Ctrl+F9 or `CrashHurt=1` turns it on; `crashMinDv` in `GtaBeamD1_weapons.json` sets how hard a crash must be.
- Show cars stand still and can look flat-lit or show through the car you drive.
- Door glass is missing on some cars. Tyre smoke is off (`TireSmoke=1` to try it).
- Other mods' extra objects on the car in BeamNG (like a DARS driver) aren't brought into GTA.

## Settings
Everything is in `GtaBeamD1.ini`, with comments. The ones you're most likely to want:
- `PuppetSolid=1` (default): GTA's world reacts to your car with GTA's own physics. `0` goes back to the 2.76 way (traffic you touch vanishes, set by `TrafficMode`).
- `PuppetNoMap=1` (default, 2.81): GTA's hidden car ignores GTA's map and BeamNG's solid posts; BeamNG alone hits them. `0`: the 2.77 way.
- `CrashHurt=0` (default, 2.81): crashes don't hurt you. `1`: they do (Ctrl+F9 switches it in game).
- `AutoMatchCar=0` (2.85): `1` makes F11 swap the GTA car for the matching one (kind, seat, size; see Tips). `AutoMatchModels` lists the GTA models it picks from (empty: 164 built in, cars to buses and heavy machinery). The F7 menu's Get car always matches.
- `MenuKey=0x76` (2.85): the in-game menu's key (F7).
- `TrafficProxies=5` (default since 2.85, was 4 in 2.83; needs the 2.83 BeamNG mod): that many boxes wait in BeamNG. A GTA car about to meet yours gets one (sizes and weights: `proxyPool` in `GtaBeamD1_traffic.json`), BeamNG resolves the crash, GTA's car copies its box and the hidden car ignores that GTA car. `0`: the 2.82 way.
- `PuppetPassCar=1` (2.82): only for GTA cars with no box. It doesn't stop GTA removing a traffic car the hidden car is teleported onto.
- `Weapons=0` turns off weapon damage on the car.
- `DriveGravity` sets how heavy the car feels (1.1).
- `ShowCarsMax` (4) is how many show cars you can park; each one uses video memory.
- `DriverSeatForwardM`, `DriverSeatUpM`, `DriverSeatRightM` move you in the seat for every car.

Game content lives in JSON next to the ini: `GtaBeamD1_surfaces.json` (GTA ground → BeamNG grip), `GtaBeamD1_props.json` (props), `GtaBeamD1_weapons.json` (damage per weapon; `crashMinDv` is how hard a crash must be to hurt you), `GtaBeamD1_traffic.json` (masses).

## Bug reports
Please attach both logs:
- `GtaBeamD1.log` (GTA V folder)
- `gtabridge_log.txt` (`%LOCALAPPDATA%\BeamNG\BeamNG.drive\current\gtabridge\`)

## Roadmap
Planned, in rough order. No dates, and things may change with your feedback.

**Done in 2.85 (OpenGTANG)**
- In-game menu (F7), with **Get car from BeamNG**: export, match and attach in one button.
- The hidden GTA vehicle matched to your BeamNG one: by kind (BeamNG's Body Style), where you sit, and size; remembered per vehicle.
- GTA's motorcycles and bicycles get a crash box in BeamNG; a hard hit knocks the rider off.
- BeamNG 0.40: the driver's seat is read from its new occupant cameras (the seat feature had stopped finding it).
- Bikes that lean on their stand when placed (the GTA IV Angel) start drive mode.
- Heavy machinery: exports with a part under two parents (the wl40 wheel loader) load, and wide tyres (0.8 m) spin and follow their hubs.
- Fix: the right-side wheels of every car spun backwards in drive mode.
- Fix: seat adjust did nothing with `PuppetSolid=1`.

**Done in 2.84 (OpenGTANG)**
- Motorcycles: BeamNG bikes on GTA bikes, with the lean, the rider's pose, getting off and on, and GTA's crash ejection.

**Done in 2.83**
- Low-speed crashes: your BeamNG car crumples against walls, kerbs and posts at any speed.
- Crash damage on/off key (Ctrl+F9), off by default.
- Fix for slow motion (Wasted, weapon wheel) making the car jump.
- Soft-body hits from GTA's traffic: your car crumples where it's hit.

**Planned**
- Better soft-body hits from GTA's people and props: your car crumples where it's hit.
- Tyre smoke and screech when the wheels spin.
- No more holes on hills and bridges.
- Smoother camera at low speed.
- UI: BeamNG's menus and apps usable from inside GTA.
- A launcher: one click starts BeamNG (Grid, Small, Pure) and then GTA.
- Show cars with proper lighting; door glass on every car.
- Steering wheel and force feedback support.
- A second BeamNG car on the road (AI chases, trailers).
- GTA V Enhanced edition support.

## Building from source
The source is in `source\`.
- Windows with Visual Studio 2022: run `source\build_vs2022.bat` (needs the Script Hook V SDK's `ScriptHookV.lib`).
- Linux/CI: `zig c++ -target x86_64-windows-gnu` (see `source\test\build_all.sh`). That folder also has the tests, with a fake Script Hook V and a fake BeamNG for runs under Wine. They test the code, not GTA's physics.

## Credits and licences
- **GTA x Beam** by Treto420, [MIT licence](LICENSE): use, change and share the code freely, including in your own mods, as long as you keep the licence and credit (Treto420). Third-party parts below keep their own licences.
- [Script Hook V](http://www.dev-c.com/gtav/scripthookv/) by Alexander Blade.
- [cgltf](https://github.com/jkuhlmann/cgltf) (MIT), [stb_image](https://github.com/nothings/stb) (MIT / public domain), [bcdec](https://github.com/iOrange/bcdec) (MIT / Unlicense).
- Inspired by [SkyCraft](https://github.com/chasmlol/SkyCraft) (Skyrim x Minecraft passthrough).
- Licence texts are in `licences\`.
- No Rockstar or BeamNG game files are included. The mod reads your own installs at run time.
