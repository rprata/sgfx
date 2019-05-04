# IButterFree 

## What is IButterFree?
IButterFree is a lightweight embedded library for displays and touchscreens providing everything required to build a fully featured embedded GUI. The IButterFree library has been designed to be the smallest, fastest and most advanced embedded library for display and touchscreen solutions. For more information, access the [official website](http://ibutterfree.com).

## Goals of IButterFree
* Small memory Footprint;
* Maximize utilities of hardware acceleration;
* Support of advanced graphics operations such as multiple alpha blending modes;
* No kernel modifications;
* Lightweight, OpenSource, Portable and Modular;
* Lua support

## Installation
IButterFree requires [CMake](https://cmake.org/) to compile. Follow the instructions:
```sh
$ cd ibutterfree
$ mkdir build
$ cmake CMakeLists.txt -Bbuild
$ cd build
$ make
```
In case of cross compilation:
```sh
$ cd ibutterfree
$ mkdir build
$ cmake CMakeLists.txt -Bbuild -DCMAKE_TOOLCHAIN_FILE=toolchains/<toolchain_file>.cmake
$ cd build
$ make
```

## License
IButterFree may be modified and distributed under the terms of the MIT license. See the LICENSE file for details.