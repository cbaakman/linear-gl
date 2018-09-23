# Linear GL, version 1.1.3
Some C++ classes and functions to do linear algebra, as used in OpenGL.
See the wiki at https://github.com/cbaakman/linear-gl/wiki for explanation of the functions and classes.

## Contents
* an include dir with headers
* a src dir with implementation
* a test dir with boost unit tests to verify the math

## Building
Requires GNU/MinGW C++ compiler 4.7 or higher.

On windows, run build.cmd.

On Unix, run 'make'

### Testing

To run the tests also, boost 1.68 has to be installed in shared library form.
(https://www.boost.org/users/download/)

On Windows, the tests run automatically as part of the build script.

On unix, run 'make test'.

## Installing

On Unix you can run 'make install'.
Or run 'make uninstall' to remove the library and headers from your system.

On windows you can add the headers, dll-file and the import library to your build path.
