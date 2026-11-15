#!/bin/sh
# v2.83: TrafficProxies scenarios against the fake GTA and the fake BeamNG (about 6 minutes). Run from test/: sh run_v283.sh
# Code paths only (the box pool, the assign, the hit, the contact log, TrafficProxies=0 = v2.82); not either game's physics.
W=${W:-/home/claude/w}
cd $W/test/run
cp ../script_*.txt . 2>/dev/null
r() { script=$1; secs=$2; shift 2; sh ../run_e2e.sh $script $secs "$@" HOST_FRAME_MS=${HOST_FRAME_MS:-55} >/dev/null 2>&1; }
cp GtaBeamD1.ini ini_saved.txt
sed -i 's/^PuppetSolid=.*/PuppetSolid=1/; s/^PuppetNoMap=.*/PuppetNoMap=1/; s/^TrafficProxies=.*/TrafficProxies=4/' GtaBeamD1.ini
echo "== proxy"; r script_world.txt 90 FAKE_RAYCAP=12 FAKE_TRAFFIC=1 FAKE_PSKICK=1; python3 ../check_v283.py proxy
echo "== vjump"; r script_world.txt 90 FAKE_RAYCAP=12 FAKE_TRAFFIC=1 FAKE_PSKICK=1 FAKE_TWIN_VJUMP=1; python3 ../check_v283.py vjump | tail -4
echo "== middle"; r script_world.txt 90 FAKE_RAYCAP=12 FAKE_TRAFFIC=1 FAKE_PSKICK=1 FAKE_BOX_MIDDLE=1; python3 ../check_v283.py middle | tail -4
echo "== stale"; r script_world.txt 90 FAKE_RAYCAP=12 FAKE_TRAFFIC=1 FAKE_PSKICK=1 FAKE_TWIN_STALE=3; python3 ../check_v283.py stale | tail -4
echo "== size";  r script_world.txt 90 FAKE_RAYCAP=12 FAKE_TRAFFIC=1 FAKE_PSKICK=1 FAKE_BOX_SIZE=3; python3 ../check_v283.py size | tail -4
echo "== default"; r script_world.txt 90 FAKE_RAYCAP=12 FAKE_TRAFFIC=1 FAKE_PSKICK=1 FAKE_BOX_DEFAULT=1; python3 ../check_v283.py default | tail -4
sed -i 's/^TrafficProxies=.*/TrafficProxies=0/' GtaBeamD1.ini
echo "== v282";  r script_world.txt 90 FAKE_RAYCAP=12 FAKE_TRAFFIC=1 FAKE_PSKICK=1; python3 ../check_v283.py v282 | tail -4
cp ini_saved.txt GtaBeamD1.ini
