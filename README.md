
This is the core module of my passwordmanager. Pleas look at [azkaban](https://github.com/N1lsE/azkaban)

# How to build

## Building

`cd` into the root `azkaban-core` directory.

Prepare build with CMake
```
mkdir build
cd build
cmake ..
```

Build
```
make # or make VERBOSE=1
```

Rund tests
```
make test
# or
ctest --verbose
# or
./tests/test_linked_list
```

## nvim LSP support.

I had to search so i tell you how.

0. have clangd installed
0. install *bear*
0. run `bear -- make`

Bear - is a tool to generate compilation database for Clang tooling.\
check `man bear` to see more




