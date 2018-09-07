# Linear GL
Some C++ classes and functions to do linear algebra, as used in OpenGL.

## Installing
Simply include the headers from the include directory in your project.

## Testing
### Requirements
Requires a C++ compiler.

Requires boost 1.68 installed in shared library form. (https://www.boost.org/users/download/)
The C++ compiler needs to know where to find boost.

### Running the tests

On windows, run test.cmd

On unix-like systems, run the Makefile

### Description of the tests

The compile test is to make sure that the headers can be imported into two
different modules without problems.

The vec, mat and quat tests make sure that the code is mathematically correct.
