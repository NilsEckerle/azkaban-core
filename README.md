Discontinued!!!

Lerning for next time:

- use CMake or premake
- add third party library into repositorry, not symlinked
- dont use git submodules. project is to small for it to be worth.

azkaban main project gets discontinued too.


This is the core module of my passwordmanager. Pleas look at [azkaban](https://github.com/N1lsE/azkaban)

# How to build

## Link third party librarys

## 1. Install them
I use `brew` to install them, because i mainly use a mac and on linux i can simply install brew too.

example - `brew install sqlcipher`

list of all dependencies:
- `sqlcipher` - database which can be encrypted. It is based on sqlite.

## 2. link them
I create symlinks to a directory in my project. use the following structure: \
`azkaban/third/<library name>/include` \
`azkaban/third/<library name>/lib`

You can create one with:

sdl2\_ttf lib example: \
`ln -sf /home/linuxbrew/.linuxbrew/Cellar/sqlcipher/4.6.1/lib/ /home/nils/Documents/projects/azkaban-core/third/sqlcipher/lib`

make sure to change the version to your installed one.

to se a image how it should look, go to the [azkaban](https://github.com/N1lsE/azkaban) repo.

## Building

`cd` into the root `azkaban-core` directory.
Execute `make` and pray.

when errors appear fix them and repeat.

Make sure to pray every recursion.

## nvim LSP support.

I had to search so i tell you how.

0. have clangd installed
0. install *bear*
0. run `bear -- make`

Bear - a tool to generate compilation database for Clang tooling.\
check `man bear` to see more




