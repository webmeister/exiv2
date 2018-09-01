# -*- coding: utf-8 -*-

import system_tests


class TestFirstPoC(metaclass=system_tests.CaseMeta):
    """
    Regression test for the first bug described in:
    https://github.com/Exiv2/exiv2/issues/246
    """
    url = "https://github.com/Exiv2/exiv2/issues/246"

    filename = system_tests.path("$data_path/1-string-format.jpg")
    commands = ["$exiv2 -pa $filename"]
    stdout = [
        """Exif.Image.ExifTag                           Long        1  26
Exif.Photo.Flash                             SRational   1  No flash
"""
    ]

    stderr = [""]
    retval = [0]

    compare_stderr = system_tests.check_no_ASAN_UBSAN_errors
