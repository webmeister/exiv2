# CMake in Exiv2

CMake is a cross-platform build system, to control the compilation process using platform/compiler
independent configuration files.

STATUS:

* CMake scripts are functional and used to perform the daily build on the CI jobs
  for MacOS-X, Linux (gcc and clang) and Visual Studio (2008, 10, 12, 13, 15 and 17)

* Team Exiv2 no longer provide support for MinGW. This is discussed in TODO-CMAKE

Latest update: 2018-09-13

## 1 CMake resources

You have to install [cmake](http://www.cmake.org/) on your target system. The minimum version required is 3.3.2.

There are some global CMake options that you can use in Exiv2 :

- `CMAKE_INSTALL_PREFIX` : decide where the program will be install on your computer.
- `CMAKE_BUILD_TYPE` : decide which type of build you want.
- `BUILD_SHARED_LIBS` : To control whether you want to build exiv2lib as shared or static.

More information about Exiv2 CMake options in CMakeLists.txt

## 2 Building and Installing on UNIX-like systems

This process covers MacOS-X, Linux and Cygwin.

Run the following commands from the top directory (containing this
file) to configure, build and install the library and utilities:

```bash
    $ mkdir build && cd build
    $ cmake .. or cmake-gui ..
    $ make -j
    $ (sudo) make install
```

Note that the CMake generator used by default on Unix is : 'Makefiles'. However you can chose others like 'Ninja'

To uninstall Exiv2, run:

    $ (sudo) make uninstall

## 3 Building and installing for Visual Studio Users

  From Exiv2 0.26.0 to 0.26.1 the CMake code of the project was rewritten and now it is possible to
  configure project from the command line as we do in the Unix sytems. As in the UNIX case, we can
  run the following commands from the top directory to configure, build and install the library and
  utilities:

```bash
    $ mkdir build && cd build
    $ cmake .. or cmake-gui ..
    $ cmake --build . --config Release
    $ cmake --build . --config Release --target install
```

  However there are some particularities on Windows that might cause the CMake command does not find
  the compiler correctly.

  Previous versions of Visual Studio were creating an environment variable (VSCOMNTOOLS140, for
  example) that points at the compiler and other resources relevant to that version of the compiler.
  However from Visual Studio 2017, they do not do that anymore.

  We recommend to call the `vcvarsall.bat` Visual Studio configuration script before running CMake.
  This script will setup some environment variables that will enable CMake to find the compiler,
  include directories, libraries, etc. For example, with Visual Studio 2017 installed on your system,
  you will need to run:

```bash
  c:\exiv2dir> call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
```

  It is also important to note that the default CMake configuration assumes the existence of some libraries
  in your system. If they are not available, the configuration will fail. It is possible to disable some
  features, or provide the paths to the INCLUDE folders, or libraries, at the moment of calling CMake the
  first time.

  In this example, we disable the NLS and PNG support, and we specify the path where we have the EXPAT library:
  ```bash
  c:\exiv2dir> cmake -DEXIV2_ENABLE_NLS=OFF -DEXIV2_ENABLE_PNG=OFF -DCMAKE_PREFIX_PATH="C:\pathToExpat\ ../
  ```

### CMake Generators

  It is also important to note that the default CMake generator is 'Visual Studio' (The version will
  depend on the vcvarsall.bat script called before running CMake).

  If you are not a big fan of Visual Studio you can use other generators like: 'Ninja'. In order to
  use them you just need to pass the option -GNinja at the moment of calling CMake for the first time:

```bash
  $ cmake -GNinja -DEXIV2_ENABLE_NLS=OFF -DEXIV2_ENABLE_PNG=OFF -DCMAKE_PREFIX_PATH="C:\pathToExpat\ ../
```

  Note: For using the Ninja generator you will need to have the ninja build system executable in your
  $PATH. More info at https://ninja-build.org/.

## 4 Using conan to get the exiv2 project dependencies

In [README-CONAN.md](https://github.com/Exiv2/exiv2/blob/master/README-CONAN.md) we give details
about how to use conan to get all the Exiv2 dependencies. Basically, all you need to do is to
have conan installed on your system and run the command `conan install` before calling CMake:

    $ mkdir build && cd build
    $ conan install ..
    $ cmake .. or cmake-gui ..

## 5 Consuming Exiv2 with CMake

When installing exiv2 by running the **install** target we get some files under the folder
`${CMAKE_INSTALL_PREFIX}/share/exiv2/cmake/`.

In the example project https://github.com/piponazo/exiv2Consumer you could see how to consume
exiv2 via CMake by using these files.

## 6 Using CPack in Exiv2

CPack is a tool that comes with CMake that is used to generate package installers or tarballs.

### Packaging the binaries

Once you have created a build folder, and configured and compiled the project, you just need to run a
command to generate a package:

```bash
# Previous steps: create build directory, configure and compile the project
$ cd exiv2
$ mkdir build && cd build
$ cmake ..
$ cmake --build . --config Release

# How to generate a package with cpack (With tarbz2)
$ cpack -G TBZ2 .
CPack: Create package using TBZ2
CPack: Install projects
CPack: - Run preinstall target for: exiv2
CPack: - Install project: exiv2
CPack: Create package
CPack: - package: /path/to/exiv2/build/exiv2-0.27.0-Linux.tar.bz2 generated.
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