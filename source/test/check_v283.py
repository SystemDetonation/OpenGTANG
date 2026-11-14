#!/usr/bin/env python3
"""check_v283.py - v2.83 TrafficProxies end-to-end checks (run in test/run after run_e2e.sh). FAKE GTA and FAKE BeamNG only: they
test the two sides' code paths (the box pool, the assign, the hit, the contact log, the release, TrafficProxies=0 = v2.82). Whether
BeamNG's box really lands on GTA's car, holds BeamNG's car and bends it is Treto's in-game test.
  proxy  : PuppetSolid=1, TrafficProxies=4, FAKE_TRAFFIC=1 FAKE_PSKICK=1: 4 boxes ready before the drive; the parked GTA car gets
           one before the car meets it; the fake BeamNG car hits the box; the contact is logged as BeamNG's; GTA's car copies the
           box; the hidden car is set not to collide with that GTA car (so the fake's GTA crash never happens); back to GTA.
  vjump  : the same with FAKE_TWIN_VJUMP=1 (the box's speed reads 9000 m/s one frame after its teleport): that pose is not taken
           and the box is not thrown.
  middle : the same with FAKE_BOX_MIDDLE=1 (BeamNG places a box by its bottom middle, not its position): learned from the first
           box (it came out exactly that offset away), put again, then as proxy.
  stale  : the same with FAKE_TWIN_STALE=3 (BeamNG says the box's old spot for 3 frames after its teleport): no pose goes to GTA
           until it is where it was asked; not thrown.
  size   : the same with FAKE_BOX_SIZE=3 (the boxes measure 3 x the size asked; they are right): used at the size asked, said so.
  default: FAKE_BOX_DEFAULT=1 (the boxes come out the jbeam's default 0.5 x 0.5 x 1 m): none is used; GTA's own crash (v2.82).
  v282   : TrafficProxies=0: no boxes asked; GTA's own crash, as v2.82."""
import os, re, sys

mode = sys.argv[1] if len(sys.argv) > 1 else 'proxy'
fails = []
def check(cond, what):
    print(('PASS ' if cond else 'FAIL ') + what)
    if not cond: fails.append(what)
def rd(p): return open(p, errors='replace').read() if os.path.exists(p) else ''
log, host, ev, blog = rd('GtaBeamD1.log'), rd('host_out.txt'), rd('fake_beam_events.txt'), rd('gtabridge/gtabridge_log.txt')
gtaCrash = "GTA's crash: a GTA car (9001" in log
if mode in ('proxy', 'vjump', 'middle', 'stale', 'size'):
    check('settings: v2.83: TrafficProxies 4 (boxes in BeamNG' in log, 'setting read')
    check('proxy (v2.83): asked BeamNG for 4 boxes' in log and '"fb":[]' in log, 'the pool asked for (no BeamNG car instead)')
    n = len(re.findall(r'proxy \(v2\.83\): box \d ready: a box:', log))
    check(n == 4, '4 boxes ready (%d)' % n)
    i_r, i_on = log.rfind('proxy (v2.83): box'), log.find('Drive ON on GTA')
    if mode == 'size':
        check(len(re.findall(r'proxy boxes: box \d measures [\d.]+ x [\d.]+ x [\d.]+ m .*used at the size asked', blog)) == 4, "BeamNG's log: 4 boxes measured oddly, used at the size asked")
    else:
        check(len(re.findall(r'proxy boxes: box \d ready: [\d.]+ x [\d.]+ x [\d.]+ m, \d+ kg asked', blog)) == 4, "BeamNG's log: 4 boxes, the size asked and measured")
    check(re.search(r'proxy boxes: box \d is where it was asked \d+ ms after its teleport', blog) is not None and 'NOT where it was asked' not in blog, "BeamNG's log: the box is where it was asked")
    if mode == 'middle':
        check(len(re.findall(r'proxy boxes: BeamNG places a box by its bottom middle', blog)) == 1, 'placing by the bottom middle learned, once')
    else:
        check('BeamNG places a box by' not in blog, 'placed by its position (nothing to learn)')
    check(len(re.findall(r'PROPSPAWN', ev)) == 0 and len(re.findall(r'TWIN gtab_twin_\d spawned: a gtab_prop', ev)) == 4, 'spawned as the mod\'s gtab_prop')
    m = re.search(r'proxy \(v2\.83\): GTA car 9001 .*meets the car in [\d.]+ s: box (\d) \(box:([\d.]+):([\d.]+)', log)
    check(m is not None, 'the GTA car got a box before the meeting')
    check('TWINHIT' in ev, "BeamNG's car hit the box in BeamNG")
    c = re.search(r"contact \(v2\.83\): a GTA car \(9001, [\d.]+ m long\) at \d+ km/h: resolved by BeamNG \(its box \d.*the hidden car [\d.]+ m from BeamNG's car", log)
    check(c is not None, 'the contact: resolved by BeamNG, the hidden car\'s distance')
    check('FAKE: traffic car posed' in host and re.search(r'traffic car velocity set -?[1-9]', host) is not None, "GTA's car copied its box (pushed along)")
    check(re.search(r'no collision (100 with 9001|9001 with 100)', host) is not None and not gtaCrash, "the hidden car set not to collide with it; no GTA crash with it")
    check('PuppetSolid: snap' not in log, 'no teleport')
    r = re.search(r'proxy \(v2\.83\): GTA car 9001 back to GTA \(([^)]*)\) after [\d.]+ s: its box \d was hit by BeamNG\'s car.*exists 1', log)
    check(r is not None, 'back to GTA, hit, still there (%s)' % (r.group(1) if r else '-'))
    check('CONFLICT' not in log, 'no conflict line')
    check(re.search(r'proxy \(v2\.83\): 10 s: TrafficProxies ON: 1 GTA cars got a box, 1 hit', log) is not None, '10 s line counts it')
    if mode == 'vjump':
        check(re.search(r"proxy \(v2\.83\): box \d's pose not taken [\d.]+ s after its first .*: \d+ km/h after", log) is not None, 'the odd pose not taken, with its numbers')
        check('THROWN' not in log and 'thrown in BeamNG' not in log, 'not thrown')
    else:
        check("pose not taken" not in log and 'THROWN' not in log, 'no odd poses')
elif mode == 'default':
    check(len(re.findall(r'proxy boxes: box \d came out', blog)) == 4, "BeamNG's log: 4 boxes came out the jbeam's default size")
    check(len(re.findall(r'proxy \(v2\.83\): box \d failed in BeamNG \(box size wrong\)', log)) == 4, 'GTA told: 4 failed')
    check('takes its place' not in log and gtaCrash, "no box used: GTA's own crash (v2.82)")
else:
    check('settings: v2.83: TrafficProxies 0' in log, 'setting read as 0')
    check('asked BeamNG for' not in log and 'proxy (v2.83)' not in log.replace('settings: v2.83', ''), 'no boxes asked, no proxy lines')
    check(gtaCrash, "GTA's own crash, as v2.82")
print('ALL PASS' if not fails else '%d FAIL' % len(fails))
sys.exit(1 if fails else 0)
