# GTest-CMake-example

An example about building a GTest project using CMake.

## Introduction

This `GTest` project is a demo that uses `CMake` to build, and supports `GCC` and `Clang`.

I want to practice `CMake` with this project, so it may have many defects or even errors. Of course, This project has met my basic requirements.

## Project Struction

```
GTest-CMake-example$ tree
.
├── CMakeLists.txt
├── build
├── include
│   ├── 1.7.0
│   │   └── gtest
│   ├── 1.10.0
│   │   └── gtest
│   ├── fib.h
│   └── fac.h
├── lib
│   ├── 1.7.0
│   │   ├── clang
│   │   ├── x64
│   │   └── x86
│   └── 1.10.0
│       ├── clang
│       ├── x64
│       └── x86
│   
└── src
    ├── main.cpp
    ├── fib.cpp
    └── fac.cpp
```

## Environment

- Clang 9.0.0 (Not tested on other versions)
- MinGW-w64 8.1.0 (Not tested on other versions)
- GTest 1.7.0 and 1.10.0

## Build

I've customized three options to select `complier`, `GTest sersion`, `64bits or 32bits`.

| Option Name  | Value  |
|    ----      | ----   |
| `COMPILER`   |   `clang` `gcc`|
| `GTEST_VERSION`   |   `1.7.0` `1.10.0`|
| `GTEST_BITS`   |   `x64` `x86`|

You can use `-D<OPTION_NAME>="XXX"` to specify them. The value for options is **case insensitive**.

**Note:** 
1. I don't compile this project by other compiler.
2. `Clang` only supports `x64`.

### MinGW Makefiles

In project root (folder `CMakeList.txt` is in):

```
mkdir build
cd build
```

then run `CMake` to generate `MinGW Makefiles` ..

```
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release  -DGTEST_VERSION="1.
7.0" -DGTEST_BITS="x64" -DCOMPILER="clang" ..
```

finally just build project

```
mingw32-make
```
