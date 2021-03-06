# pp_trees

This is a library of tree-based data structures. Each subproject is independent of one another an can be compiled as a shared library to be used freely by any other program.
The project has a suite of tests grouped under the *main/* subdirectory.


## Compiling and usage
### Linux
Note that on some Linux distributions apt does not provide a recent CMake release.
This project requires CMake 3.17 or newer. Download the latest release from the official
site and extract the archive. The run the following commands in the extracted folder:

    ./configure
    make
    sudo make install


The root folder of the project is *pp_trees/*, in this directory create a new one with
`mkdir build` and move into it with `cd build`
Then run the following commands to install the software:

    cmake ..
    cmake --build .
    cmake --install .

The executable will be in pp_trees/install/bin


### Windows
The root folder of the project is pp_trees/, in this directory create a new one with
`mkdir build` and move into it with `cd build`
Then run the following commands to install the software (for MinGW gcc compiler):

    cmake -G "MinGW Makefiles" ..
    cmake --build .
    cmake --install .

The executable will be in pp_trees/install/bin


### Options
The main executable runs a series of tests designed to test the correctness and efficiency
of the two libraries. The test number can be chosen with the (mandatory) option -t. Test 0
runs all the tests.  The (optional) option -p sets the flag to produce an output file. It
requires a file name as an argument. The file will be located in the binaries directory.
