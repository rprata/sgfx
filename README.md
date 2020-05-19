
# SGFX
[![CircleCI](https://circleci.com/gh/rprata/sgfx.svg?style=svg)](https://circleci.com/gh/rprata/sgfx)

## What is SGFX?
SGFX is a lightweight embedded library for displays and touchscreens providing everything required to build a fully featured embedded GUI. The SGFX library has been designed to be the smallest, fastest and most advanced embedded library for display and touchscreen solutions. For more information, access the [official website](https://rprata.github.io/sgfx).

## Goals of SGFX
* Small memory Footprint;
* Maximize utilities of hardware acceleration;
* Support of advanced graphics operations such as multiple alpha blending modes;
* No kernel modifications;
* Lightweight, OpenSource, Portable and Modular;
* Lua support

## Supported compilers
- [x] GCC
- [x] Clang

## Supported architectures
- [x] x86
- [x] x86_64
- [x] ARMv5
- [x] ARMv6
- [x] ARMv7
- [x] ARMv8 (32-bit/64-bit)

## Tested platforms
- [x] Raspberry Pi 1 Model B
- [x] Raspberry Pi 2 Model B
- [x] Raspberry Pi 3
- [ ] Raspberry Pi 4
- [ ] Odroid C2
- [x] Beagle Bone Black

If you have a suggestion or want contribuite with a new portings, create an issue :wink:

## Installation
SGFX requires [CMake](https://cmake.org/) and [Ninja](https://ninja-build.org/) to compile. Follow the instructions:
```sh
$ cd sgfx
$ mkdir build
$ cmake CMakeLists.txt -Bbuild -GNinja
$ cmake --build build
```
In case of cross compilation:
```sh
$ cd sgfx
$ mkdir build
$ cmake CMakeLists.txt -Bbuild -GNinja -DCMAKE_TOOLCHAIN_FILE=toolchains/<toolchain_file>.cmake
$ cmake --build build
```

## Running examples
First, you must configure framebuffer filedescriptor used by target archtecture. Default value used is `/dev/fb0`, however you can change it creating a `.sgfxconfig`:

```txt
FDFB=/dev/fb
```

After that run examples (remember to run as a superuser):
```bash
cd build
./examples/<example>
```

| Examples         | Definition                      |
|:----------------:|:-------------------------------:|
| helloworld       | Hello World Example             |
| drawprimitives   | Primitives (rect, line...)      |
| drawimages       | PNG, BMP and TIF                |
| drawtext         | Draw simple text                |
| eventexample     | Touch event example             |

## License
SGFX may be modified and distributed under the terms of the MIT license. See the LICENSE file for details.