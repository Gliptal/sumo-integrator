# README

## CONTENTS

<!-- TOC -->

- [DESCRIPTION](#description)
- [FOLDER STRUCTURE](#folder-structure)
- [CODE CONVENTIONS](#code-conventions)
- [TESTING](#testing)
    - [OUTPUT-BASIC](#output-basic)
    - [OUTPUT-SETS](#output-sets)
    - [EGO-BASIC](#ego-basic)
    - [EGO-ASYNC](#ego-async)
    - [EGO-INPUT](#ego-input)
    - [EGO-SUBSCRIBE](#ego-subscribe)
- [CHANGELOG](#changelog)

<!-- /TOC -->

## DESCRIPTION

sumo-integrator is a C++ static library that provides abstract integration tools geared towards connecting [SUMO](http://sumo.dlr.de/index.html) with a (any) graphic engine(s).

sumo-integrator is currently compiled and developed for Unix systems only (`.a`); accordingly, the functionality tests are provided as `.out` executables.

## FOLDER STRUCTURE

Folders are structured following a typical generic C/C++ template:

- `bin`: binaries and executables
- `build`: temporary build files
- `config`: miscellaneous configuration files
- `doc`: instructions and documentation
- `include`: public API headers
- `lib`: external libraries
- `src`: library source files
- `test`: test source files

A `makefile` in the project root
mates the building of both the library's facilities and all the assorted functionality tests: documentation on all the available targets can be obtained from `make` or `make help`.

In a normal Unix environment (i.e. both `g++` and `ar` are installed) `make all` should be enough for a successful build.

## CODE CONVENTIONS

See [doc/CONVENTIONS.md](doc/CONVENTIONS.md).

## TESTING

The functionality tests all require a running instance of SUMO, reachable on the network (either on LAN or WAN):

```
sumo-gui.exe --remote-port 6666
```

Files related and required by SUMO are _not_ part of this repository.

### OUTPUT-BASIC

**SCOPE** - This functionality test ensures that data about SUMO-driven vehicles can be correctly obtained from the SUMO process.

**SETUP** - The network is formed by a single two-lane road looped in the shape of a rectangle (dimensioned at 100m x 200m). The SUMO vehicle (yellow car) spawns  adjacent to the North-West corner of the loop.

**RUN** - SUMO must be started _before_ `outputbasic.out` with the following options:

```
-c outputbasic.sumocfg
--step-length 0.01
--default.action-step-length 0.01
```

**RESULT** - The SUMO vehicle (yellow) should drive the loop in the right lane; its position, angle, and speed should be displayed on the `stdout` device.

### OUTPUT-SETS

**SCOPE** - This functionality test ensures that data about SUMO-driven vehicles can be correctly obtained from the SUMO process.

**SETUP** - The network is formed by a single two-lane road looped in the shape of a rectangle (dimensioned at 100m x 200m). The SUMO vehicle (yellow car) spawns  adjacent to the North-West corner of the loop.

**RUN** - SUMO must be started _before_ `outputsets.out` with the following options:

```
-c outputsets.sumocfg
--step-length 0.01
--default.action-step-length 0.01
```

**RESULT** - The SUMO vehicle (yellow) should drive the loop in the right lane; its position, angle, speed, acceleration, lights state, and stop state should be displayed on the `stdout` device.

### EGO-BASIC

**SCOPE** - This functionality test ensures that SUMO-driven vehicles correctly interact (e.g. avoid, overtake) with a programmatically-driven ego vehicle.

**SETUP** - The network is formed by a single two-lane road, looped in the shape of a rectangle (dimensioned at 100m x 200m). The ego vehicle (red car) and the SUMO vehicles (yellow cars) spawn adjacent to the North-West corner of the loop, at different times.

**RUN** - SUMO must be started _before_ `egobasic.out` with the following options:

```
-c egobasic.sumocfg
--step-length 0.01
--default.action-step-length 0.01
--lateral-resolution 100
```

**RESULT** - The ego vehicle (red) should drive the loop in the right lane at different speeds; the SUMO vehicles (yellow) should also drive the loop, organically overtaking the ego vehicle (and possibly each other). Some imprecisions in the curved sections of the road is to be expected.

### EGO-ASYNC

**SCOPE** - This functionality test ensures that SUMO-driven vehicles correctly interact (e.g. avoid, overtake) with a programmatically-driven ego vehicle, when the latter's simulation is asynchronous.

**SETUP** - The network is formed by a single two-lane road, looped in the shape of a rectangle (dimensioned at 100m x 200m). The ego vehicle (red car) and the SUMO vehicles (yellow cars) spawn adjacent to the North-West corner of the loop, at different times.

**RUN** - SUMO must be started _before_ `egoasync.out` with the following options:

```
-c egoasync.sumocfg
--step-length 0.01
--default.action-step-length 0.01
--lateral-resolution 100
```

**RESULT** - The ego vehicle (red) should drive the loop in the right lane; the SUMO vehicles (yellow) should also drive the loop, organically overtaking the ego vehicle (and possibly each other). Some imprecisions in the curved sections of the road is to be expected.

### EGO-INPUT

**SCOPE** - This functionality test ensures that SUMO-driven vehicles correctly interact (e.g. avoid, overtake) with an user-driven ego vehicle. The ego vehicle can be controlled with the 'w' (accelerate), 's' (decelerate) keys, 'a' (switch to left lane) and 'd' (switch to right lane).

**SETUP** - The network is formed by a single two-lane road, looped in the shape of a rectangle (dimensioned at 100m x 200m). The ego vehicle (red car) and the SUMO vehicles (yellow cars) spawn adjacent to the North-West corner of the loop, at different times.

**RUN** - SUMO must be started _before_ `egoinput.out` with the following options:

```
-c egoinput.sumocfg
--step-length 0.1
--default.action-step-length 0.1
--lateral-resolution 100
```

Note that both the `--step-length` and `--default.action-step-length` must be `>= 0.1` (this applies to the test's configuration file as well).

**RESULT** - The ego vehicle (red) should drive the loop at the speed and on the lane set by the user (negative speeds should result in reverse); lane switching is discrete by implementation. The SUMO vehicles (yellow) should also drive the loop, organically overtaking the ego vehicle (and possibly each other). Some imprecisions in the curved sections of the road is to be expected.

### EGO-SUBSCRIBE

**SCOPE** - This functionality test ensures that ego neighbours subscriptions correctly return the appropriate amount of vehicles, based on a given radius.

**SETUP** - The network is formed by a single two-lane road, looped in the shape of a rectangle (dimensioned at 100m x 200m). The ego vehicle (red car) and the SUMO vehicles (yellow cars) spawn adjacent to the North-West corner of the loop, at different times.

**RUN** - SUMO must be started _before_ `egosubscribe.out` with the following options:

```
-c egosubscribe.sumocfg
--step-length 0.01
--default.action-step-length 0.01
--lateral-resolution 100
```

**RESULT** - The ego vehicle (red) should drive the loop in the right lane at a lower speed than; the SUMO vehicles (yellow). As the former overtake the latter, the subscribed count should first increase and then decrease back to 0.

## CHANGELOG

The full changelog is available in [doc/CHANGELOG.md](doc/CHANGELOG.md). Versioning (mostly) follows the semantic versioning specification ([Semantic Versioning 2.0](https://semver.org/)).
