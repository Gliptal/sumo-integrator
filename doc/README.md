# README

## CONTENTS

<!-- TOC -->

- [DESCRIPTION](#description)
- [FOLDER STRUCTURE](#folder-structure)
- [CODE CONVENTIONS](#code-conventions)
- [TESTING](#testing--todo-add-output-basic)
    - [OUTPUT-BASIC](#output-basic)
    - [EGO-BASIC](#ego-basic)
    - [EGO-ASYNC](#ego-async)
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

**RESULT** - The SUMO car (yellow) should drive the loop in the right lane; its position, angle, and speed should be displayed on the `stdout` device.

### OUTPUT-SETS

**SCOPE** - This functionality test ensures that data about SUMO-driven vehicles can be correctly obtained from the SUMO process.

**SETUP** - The network is formed by a single two-lane road looped in the shape of a rectangle (dimensioned at 100m x 200m). The SUMO vehicle (yellow car) spawns  adjacent to the North-West corner of the loop.

**RUN** - SUMO must be started _before_ `outputbasic.out` with the following options:

```
-c outputsets.sumocfg
--step-length 0.01
--default.action-step-length 0.01
```

**RESULT** - The SUMO car (yellow) should drive the loop in the right lane; its position, angle, speed, acceleration, lights state, and stop state should be displayed on the `stdout` device.

### EGO-BASIC

**SCOPE** - This functionality test ensures that SUMO-driven vehicles correctly interact (e.g. avoid, overtake) with a programmatically-driven ego vehicle.

**SETUP** - The network is formed by a single two-lane road, looped in the shape of a rectangle (dimensioned at 100m x 200m). The ego vehicle (red car) and  the SUMO vehicles (yellow cars) spawn adjacent to the North-West corner of the loop, at different times.

**RUN** - SUMO must be started _before_ `egobasic.out` with the following options:

```
-c egobasic.sumocfg
--step-length 0.01
--default.action-step-length 0.01
--lateral-resolution 100
```

**RESULT** - The ego car (red) should drive the loop in the right lane at different speeds; the SUMO cars (yellow) should also drive the loop, organically overtaking the ego car (and possibly each other). Some imprecisions in the curved sections of the road is to be expected.

### EGO-ASYNC

**SCOPE** - This functionality test ensures that SUMO-driven vehicles correctly interact (e.g. avoid, overtake) with a programmatically-driven ego vehicle, when the latter's simulatin is asynchronous.

**SETUP** - The network is formed by a single two-lane road, looped in the shape of a rectangle (dimensioned at 100m x 200m). The ego vehicle (red car) and  the SUMO vehicles (yellow cars) spawn adjacent to the North-West corner of the loop, at different times.

**RUN** - SUMO must be started _before_ `egobasic.out` with the following options:

```
-c egoasync.sumocfg
--step-length 0.01
--default.action-step-length 0.01
--lateral-resolution 100
```

**RESULT** - The ego car (red) should drive the loop in the right lane; the SUMO cars (yellow) should also drive the loop, organically overtaking the ego car (and possibly each other). Some imprecisions in the curved sections of the road is to be expected.

## CHANGELOG

The full changelog is available in [doc/CHANGELOG.md](doc/CHANGELOG.md). Versioning (mostly) follows the semantic versioning specification ([Semantic Versioning 2.0](https://semver.org/)).
