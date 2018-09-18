| Travis        | AppVeyor      | GitLab| Codecov|
|:-------------:|:-------------:|:-----:|:------:|
| [![Build Status](https://travis-ci.org/Exiv2/exiv2.svg?branch=master)](https://travis-ci.org/Exiv2/exiv2) | [![Build status](https://ci.appveyor.com/api/projects/status/d6vxf2n0cp3v88al/branch/master?svg=true)](https://ci.appveyor.com/project/piponazo/exiv2-wutfp/branch/master) | [![pipeline status](https://gitlab.com/D4N/exiv2/badges/master/pipeline.svg)](https://gitlab.com/D4N/exiv2/commits/master) | [![codecov](https://codecov.io/gh/Exiv2/exiv2/branch/master/graph/badge.svg)](https://codecov.io/gh/Exiv2/exiv2) |

![Exiv2](http://www.exiv2.org/include/exiv2-logo-big.png)

Welcome to Exiv2, a C++ library and a command line utility to read and
write Exif, IPTC and XMP image metadata. The homepage of Exiv2 is: https://github.com/Exiv2/exiv2

## Source Code

Download the source code [Source](http://exiv2.dyndns.org/0.27.0.1/bundles/exiv2-0.27.0.1-Source.tar.gz)


## Documentation
Exiv2 API and tag reference documentation is at [Docs](http://exiv2.dyndns.org/0.27.0.1/doc/index.html)

## Building and Installing

Please read [README-CMAKE](http://exiv2.dyndns.org/0.27.0.1/README-CMAKE.md) for more information about how to build Exiv2.

### To install Exiv2 from a UNIX-like system, run:

    $ cd build
    $ sudo make install

### The default install locations are:

| Location       | Purpose           |
|:-------------  |:------------- |
| /usr/local/lib | for the library |
| /usr/local/bin | for the `exiv2` utility |
| /usr/local/include/exiv2 | for header files |

### To uninstall Exiv2 from a UNIX-like system, run:

    $ sudo make uninstall

## Dependencies

You can choose to use dependent libraries using your platform's package installer.

We also support conan which is especially useful for users of Visual Studio.
See [README-CONAN](http://exiv2.dyndns.org/0.27.0.1/README-CONAN.md) for more information

The following libexiv2 features are enabled by default and may
require external libraries. You can disable the dependency with CMake options

| Feature                    | Package  |  cmake option                | Availability |
|:-------------------------- |:-------- |:---------------------------- |:----------- |
|PNG image support           | zlib      | `-DEXIV2_ENABLE_PNG=Off`     | http://www.gnu.org/software/gettext/ |
|Native language support     | gettext   | `-DEXIV2_ENABLE_NLS=Off`     | http://zlib.net/ |
|XMP support                 | expat     | `-DEXIV2_ENABLE_XMP=Off`     | http://expat.sourceforge.net/ |

On Linux, it is usually best to install the dependencies through the
package management system of the distribution together with the
corresponding development packages (for the header files and static
libraries).

## Building Exiv2 Documentation

To generate the documentation (`make doc`), you will further need:
	`$ cmake ..options.. -DEXIV2_BUILD_DOC=On`

To build the documentation, you will need the following products:

| Product                    | Availability |
|:-------------------------- |:----------- |
| doxygen        |     http://www.doxygen.org/ |
|	graphviz     |    http://www.graphviz.org/ |
|	python       |   http://www.python.org/    |
|	xsltproc     |  http://xmlsoft.org/XSLT/   |
|	md5sum       | http://www.microbrew.org/tools/md5sha1sum/ |
|	pkg-config   | http://pkg-config.freedesktop.org/wiki/ |

## Support

All project resources are accessible from the project website.
    https://github.com/Exiv2/exiv2

For new bug reports and feature requests, please open an issue in Github.

## Download built libraries and linking your own code with Exiv2

You can download pre-built 'bundles' which include documentation.

[[Linux](http://exiv2.dyndns.org/0.27.0.1/bundles/exiv2-0.27.0.1-Linux.tar.gz)]
[[MacOSX](http://exiv2.dyndns.org/0.27.0.1/bundles/exiv2-0.27.0.1-Darwin.tar.gz)]
[[Cygwin](http://exiv2.dyndns.org/0.27.0.1/bundles/exiv2-0.27.0.1-CYGWIN.tar.gz)]
[[MinGW](http://exiv2.dyndns.org/0.27.0.1/bundles/exiv2-0.27.0.1-MinGW.tar.gz)]
[[MSVC](http://exiv2.dyndns.org/0.27.0.1/bundles/exiv2-0.27.0.1-msvc.zip)]

The file "ReadMe.txt" in a bundle describes how to install/link code with libraries for their respective platform.
The file "license.txt" in a bundle describes is a copy of GPLv2 License



## License

Copyright (C) 2004-2018 Exiv2 authors

Exiv2 is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2 of the License, or (at your
option) any later version.

Exiv2 is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, 5th Floor, Boston,
MA 02110-1301 USA.

## Platform Notes
These are rough notes, to be polished.

### MinGW msys/2 64

https://www.msys2.org
Download:  http://repo.msys2.org/distrib/x86_64/msys2-x86_64-20180531.exe

#### msys64.bat

```
554 rmills@rmillsmm-w7:/c/Users/rmills/com $ cat msys64.bat
setlocal
set "PATH=c:\msys64\usr\bin;c:\msys64\usr\local\bin;c:\msys64\mingw64\bin;"
set "PS1=\! \u@\h:\w \$ "
bash.exe -norc
555 rmills@rmillsmm-w7:/c/Users/rmills/com $
```

#### Install MinGW Dependencies

```
$ for i in mingw-w64-x86_64-gcc mingw-w64-x86_64-gdb mingw-w64-x86_64-make mingw-w64-x86_64-pkg-config mingw-w64-x86_64-cmake; do (echo y|pacman -S $i); done
```

#### Download exiv2 from github

```
$ mkdir -p ~/gnu/github/exiv2
$ git clone https://github.com/exiv2/exiv2
$ cd exiv2
$ mkdir build ; cd build ;
$ cmake .. -G "Unix Makefiles"
$ make
```

### Cygwin

Download: https://cygwin.com/install.html and run setup-x86_64.exe

You need:
cmake, gcc, pkg-config, dos2unix, zlib-devel, libexpat-devel, make, git, python3-interpreter, libiconv, libxml2-utils

To build cmake (from 3.11.2), you need libncurses

### Linux


```
sudo apt-get update
sudo apt-get install build-essential

gcc,  	libxml2-utils
```
