# -*- coding: utf-8 -*-

import hashlib
import os.path

import system_tests

files = ("exiv2-bug1074.png", "imagemagick.png", "Reagan.tiff", "Reagan.jpg")

filenames = [system_tests.path("$data_path/" + fname) for fname in files]

icc_filenames = [
    system_tests.path("$data_path/" + os.path.splitext(fname)[0] + ".icc")
    for fname in files
]


@system_tests.DeleteFiles(*icc_filenames[0:3])
class IccProfileInApp2Segment(metaclass=system_tests.CaseMeta):

    url = "http://dev.exiv2.org/issues/1074"

    encodings = [bytes]

    commands = [
        "$exiv2 -eC " + fname for fname in filenames
    ]

    def compare_stdout(self, i, command, got_stdout, expected_stdout):
        with open(self.expand_variables(icc_filenames[i]), "br") as icc:
            dump = icc.read(-1)
            self.assertEqual(
                hashlib.md5(dump).hexdigest(), expected_stdout
            )

    stderr = [
        bytes(),
        bytes(
            """Error: Directory NikonPreview with 512 entries considered invalid; not read.
""",
            encoding='utf-8'),
        bytes(),
        bytes()
    ]
    stdout = [
        "5c02432934195866147d8cbfa49f3fcf",
        # "cf0aeee7fdc11b20ad8a19d65628488e",
        "b1a428d4b11f7298c8f047e374bb985b",
        "1d3fda2edb4a89ab60a23c5f7c7d81dd",
        "50b9125494306a6fc1b7c4f2a1a8d49d"
    ]
    retval = [0] * len(filenames)
