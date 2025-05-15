
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
```sh
make # or make VERBOSE=1
```

Rund tests
```sh
make test
# or
ctest --verbose
# or
./tests/test_linked_list
```

## nvim LSP support.

after building there should be a file `compile_commands.json` in the build directory.
Just copy it to the main directory or do a symlik.


```sh
cd ~/Documents/azkaban-core
cp build/compile_commands.json .
# or
ln -sf build/compile_commands.json .
```

