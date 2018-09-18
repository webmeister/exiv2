![Exiv2](http://www.exiv2.org/include/exiv2-logo-big.png)

# Building Exiv2 with CMake

CMake is a cross-platform build system, to control the
compilation process using platform/compiler independent configuration files.

STATUS:

* CMake scripts are used to build Exiv2 on MacOS-X, MinGW/msys2, Linux and Visual Studio (8, 10, 12, 13, 15 and 17)

Latest update: 2018-09-18

## 1 CMake resources

You must install [cmake](http://www.cmake.org/) on your target system. The minimum version required is 3.3.2.

There are some global CMake options that you can use in Exiv2 :

- `CMAKE_INSTALL_PREFIX` : decide where the program will be install on your computer.
- `CMAKE_BUILD_TYPE` : decide which type of build you want.
- `BUILD_SHARED_LIBS` : To control whether you want to build exiv2lib as shared or static.

More information about Exiv2 CMake options in CMakeLists.txt

## 2 Building and Installing on UNIX-like systems (MacOS-X, Linux, Cygwin and MinGW/msys2)

Run the following commands from the top directory (containing this
file) to configure, build and install the Exiv2 library and sample programs:

    $ mkdir build
    $ cd build
    $ cmake .. -G "Unix Makefiles"
    $ make
    $ (sudo) make install   (*)

*) sudo is not required on Cygwin and MinGW/msys2

To uninstall Exiv2, run:

    $ (sudo) make uninstall

## 3 Building and installing for Visual Studio Users

We recommend that users of Visual Studio use conan to build Exiv2.

[README-CONAN.md](http://exiv2.dyndns.org/0.27.0.1/README-CONAN.md)

## 5 Using conan to obtain project dependencies

[README-CONAN.md](http://exiv2.dyndns.org/0.27.0.1/README-CONAN.md)

In README-CONAN.md we give explanations about how to use conan to get all Exiv2 dependencies.
Basically, all you need to do is to have conan installed on your system and run the command
`conan install` before calling CMake:

    $ mkdir build
    $ cd build
    $ conan install ..
    $ cmake .. -G "Unix Makefiles"
    $ cmake --build .

## 6 Consuming Exiv2 with CMake

When installing exiv2 by running the **install** target we get some files under the folder
`${CMAKE_INSTALL_PREFIX}/share/exiv2/cmake/`.

In the example project https://github.com/piponazo/exiv2Consumer you could see how to consume
exiv2 via CMake by using these files.

## 7 Using CPack in Exiv2

CPack is a tool that comes with CMake that is used to generate package installers or tarballs.

### Packaging the binaries

Once you have created a build folder, and configured and compiled the project, you just need to run a
command to generate a package:

```bash
# Previous steps: create build directory, configure and compile the project
$ cd exiv2
$ mkdir build
$ cd build
$ cmake .. -G "Unix Makefiles"
$ cmake --build . --config Release

# How to generate a package with cpack (.tar.gz)
$ cpack -G TGZ .
CPack: Create package using TGZ
CPack: Install projects
CPack: - Run preinstall target for: exiv2
CPack: - Install project: exiv2
CPack: Create package
CPack: - package: /path/to/exiv2/build/exiv2-0.27.1-Linux.tar.gz generated.
```
You can obtain a complete list of the different generators by running `cpack -h`.

### Packaging the sources

CPack is also convenient for generating a tarball with the sources of the project. Since we included CPack in
our CMake code, a new target `package_source` is provided which creates such tarball automatically:

```bash
$ make package_source
Run CPack packaging tool for source...
CPack: Create package using TBZ2
CPack: Install projects
CPack: - Install directory: /media/linuxDev/programming/exiv2
CPack: Create package
CPack: - package: /media/linuxDev/programming/exiv2/build/exiv2-0.27.0-Source.tar.bz2 generated.
```

Note that you can also run `cmake --build . --config Release --target package_source` in case you are not using
the "UNIX Makefiles" Generator.