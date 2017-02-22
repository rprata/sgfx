# IButterFree 

 [![N|Solid](http://vignette1.wikia.nocookie.net/pokedex-br/images/d/d8/Butterfree_NB.png/revision/latest?cb=20151222212223&path-prefix=pt-br)](http://vignette1.wikia.nocookie.net/pokedex-br/images/d/d8/Butterfree_NB.png/revision/latest?cb=20151222212223&path-prefix=pt-br)

## What is IButterFree?
IButterFree is a lightweight embedded library for displays and touchscreens providing everything required to build a fully featured embedded GUI. The IButterFree library has been designed to be the smallest, fastest and most advanced embedded library for display and touchscreen solutions.

## Goals of IButterFree
* Small memory Footprint;
* Maximize utilities of hardware acceleration;
* Support of advanced graphics operations such as multiple alpha blending modes;
* No kernel modifications;
* Lightweight, OpenSource, Portable and Modular;

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
IButterFree is licensed under the GNU Lesser General Public License (LGPL) version 2.1 or later. However, IButterFree incorporates several optional parts and optimizations that are covered by the GNU General Public License (GPL) version 3. If those parts get used the GPL applies to all of IButterFree.