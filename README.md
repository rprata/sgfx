# IButterFree 

 [![N|Solid](http://vignette1.wikia.nocookie.net/pokedex-br/images/d/d8/Butterfree_NB.png/revision/latest?cb=20151222212223&path-prefix=pt-br)](http://vignette1.wikia.nocookie.net/pokedex-br/images/d/d8/Butterfree_NB.png/revision/latest?cb=20151222212223&path-prefix=pt-br)

## What is IButterFree?
IButterFree is a set of graphics APIs implemented on top of the Linux Frame Buffer (fbdev) abstraction layer. 

## Goals of IButterFree
* Small memory Footprint;
* Maximize utilities of hardware acceleration;
* Support of advanced graphics operations such as multiple alpha blending modes;
* No kernel modifications;
* No library dependencies, except for libc;

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
$ cmake CMakeLists.txt -Bbuild DCMAKE_TOOLCHAIN_FILE=toolchains/<toolchain_file>.cmake
$ cd build
$ make
```
