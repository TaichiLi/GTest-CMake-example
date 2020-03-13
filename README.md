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
├── factorial
│   ├── CMakeLists.txt
│   ├── include
│   │   └── fac.h
│   └── src
│       └── fac.cpp
├── fibonacci
│   ├── CMakeLists.txt
│   ├── include
│   │   └── fib.h
│   └── src
│       └── fib.cpp
└── test
    ├── CMakeLists.txt
    ├── include
    │   ├── 1.7.0
    │   │   └── gtest
    │   └── 1.10.0
    │       └── gtest
    ├── lib
    │   ├── 1.7.0
    │   │   ├── clang
    │   │   ├── x64
    │   │   └── x86
    │   └── 1.10.0
    │       ├── clang
    │       ├── x64
    │       └── x86
    └── src
        └── main.cpp

```

## Environment

- Clang 9.0.0 (Not tested on other versions)
- MinGW-w64 8.1.0 (Not tested on other versions)
- GTest 1.7.0 and 1.10.0

## Build

I've customized three options to select `GTest version`, `64bits or 32bits`.

| Option Name  | Value  |
|    ----      | ----   |
| `GTEST_VERSION`   |   `1.7.0` `1.10.0`|
| `GTEST_BITS`   |   `x64` `x86`|

You can use `-D<OPTION_NAME>="Value"` to specify them. The value for options is **case insensitive**.

**Note:** 
1. I don't compile this project by other compiler.
2. `Clang` only supports `x64`.
3. If you use `MSVC`, you should compile the static link library yourself.

### MinGW Makefiles

In project root (folder `CMakeList.txt` is in):

```
mkdir build
cd build
```

then run `CMake` to generate `MinGW Makefiles` ..

```
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="../install" -DGTEST_VERSION="1.7.0" -DGTEST_BITS="x64" ..
```

after that just build project

```
mingw32-make
```

finally you can install the project

```
mingw-32-make install
```

## Notes

1. If you want to change the compilation options, first clear the files generated by the last `CMake` run (or only clear `CMakeCache.txt` ). 
2. If your compiler's exception handling model isn't `sjlj`, you should change clang's compile option `-fsjlj-excetions`,
    - `seh` to use `-fseh-excetions`
    - `dwarf` to use `-fdwarf-excetions`
3. `GTest-1.10.0` may not support colorful output for `Windows PowerShell` and `cmd`.
4. The older binary releases of MinGW-w64 have an incompatibility with Clang 8.0+'s float.h. To fix this, copy [this specific revision of float.h](https://github.com/mirror/mingw-w64/raw/82b169c5734a6198d3b4c51a48f82e7b7104f143/mingw-w64-headers/crt/float.h) into the correct location and use it. (from [StackOverflow](https://stackoverflow.com/questions/57166340/how-do-i-compile-code-using-clang-with-the-mingw-c-c-library-particular-issu))