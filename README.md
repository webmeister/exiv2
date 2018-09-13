| Travis        | AppVeyor      | GitLab| Codecov|
|:-------------:|:-------------:|:-----:|:------:|
| [![Build Status](https://travis-ci.org/Exiv2/exiv2.svg?branch=master)](https://travis-ci.org/Exiv2/exiv2) | [![Build status](https://ci.appveyor.com/api/projects/status/d6vxf2n0cp3v88al/branch/master?svg=true)](https://ci.appveyor.com/project/piponazo/exiv2-wutfp/branch/master) | [![pipeline status](https://gitlab.com/D4N/exiv2/badges/master/pipeline.svg)](https://gitlab.com/D4N/exiv2/commits/master) | [![codecov](https://codecov.io/gh/Exiv2/exiv2/branch/master/graph/badge.svg)](https://codecov.io/gh/Exiv2/exiv2) |


<pre><code>
    @@@Marco@@@@@b                   ;mm                       /##Gilles###\
    j@@@#Robin",                     Brad                     /@@@Thomas@@@@Q
     @@@#       \                     ##                     @@@b     |@@@b
     @@@#          .;;;;,     ,;;;, ,;;;;  ,;;;p      .;;;   7@@      ]Alan
     @@@#           j@@@@,   ]@@#/  '@@@#  j@@@#      ]@@^           ;@@@"
     @@@Andreas@C     "@@@p @@@"     @@@b   j@@@p     @@b           @@@#/
     @@@#^7"7%#\       ^@@@@@#~      Benb    1@@@    {@#          s@@@#
     @@@#                Niels       @@@b     @@@Q  ]@#         ;@@@#/
     @@@#              ,@@##@@m      @@@b      @@@p @@C        #@@#C
     @@@#       ,/    s@@#  @@@@     @@@b       Volker       @Tuan@
    ]@@@Abhinav@@\   /@@@\    \@@@Q  @@@Q       %@@@#      /@@@@Mahesh@@#
   /@@Raphael@@@@@\ /@@@@@\     C++  Metadata  Library    /@Sridhar@@@v0.26\
</code></pre>

# Exiv2

Welcome to Exiv2, a C++ library and a command line utility to read and
write Exif, IPTC and XMP image metadata. The homepage of Exiv2 is:

    http://www.exiv2.org/

See [doc/ChangeLog](https://github.com/Exiv2/exiv2/blob/master/doc/ChangeLog)
for a list of recent changes to Exiv2.

Exiv2 API and tag reference documentation is at http://www.exiv2.org/doc
or you can build it and point your browser to `doc/index.html`.

For more information on XMP support in Exiv2, see [doc/README-XMP](https://github.com/Exiv2/exiv2/blob/master/doc/README-XMP).

## Building and Installing

The project is configured with CMake and it should be possible to compile on the main operative
systems and with most of the C++98 compilers. In [README-CMAKE.md](https://github.com/Exiv2/exiv2/blob/master/README-CMAKE.md)
you will find more details about it.

The default install locations are `/usr/local/lib` for the library, `/usr/local/bin` for the
`exiv2` utility and `/usr/local/include/exiv2` for the header files. Use the cmake option
`CMAKE_INSTALL_PREFIX` to change the default.

We also provie a `uninstall` target in CMake to uninstall the project:

```bash
$ make uninstall
```

## Dependencies

The following **exiv2lib** features are enabled by default and they require external libraries.
They can be controlled through some CMake options:

```
    Feature                     Package   CMake options
    --------------------------  --------  ----------------------------
    PNG image support           zlib      EXIV2_ENABLE_PNG
    Native language support     gettext   EXIV2_ENABLE_NLS
    Characterset conversions    libiconv  [Automatic detection]
    XMP support                 expat     EXIV2_ENABLE_XMP
                                          EXIV2_ENABLE_EXTERNAL_XMP
    HTTO I/O					libcurl   EXIV2_ENABLE_CURL
    SSH I/O                     libssh    EXIV2_ENABLE_SSH
```

Some systems have gettext and iconv in libc. The CMake configuration step should detect this.

On Linux, it is usually best to install the dependencies through the package management system
of the distribution together with the corresponding development packages (for the header files
and static libraries).

To generate the documentation (`make doc`), you will further need
`doxygen`, `graphviz`, `python` and `xsltproc`.

	pkg-config   http://pkg-config.freedesktop.org/wiki/
	doxygen      http://www.doxygen.org/
	graphviz     http://www.graphviz.org/
	python       http://www.python.org/
	xsltproc     http://xmlsoft.org/XSLT/
	md5sum       http://www.microbrew.org/tools/md5sha1sum/

## Support

All project resources are accessible from the project website at
http://dev.exiv2.org/projects/exiv2/wiki

Please send feedback or queries to the Exiv2 forum. For new bug reports
and feature requests, please open an issue in Github.

## Consuming exiv2 in your own code

A pkg-config .pc file is installed together with the library.
Application developers can use `pkg-config(1)` to obtain correct
compile and link time flags for the Exiv2 library.

Exiv2 can be also consumed easily with CMake. See  [README-CMAKE.md](https://github.com/Exiv2/exiv2/blob/master/README-CMAKE.md) for more details.

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