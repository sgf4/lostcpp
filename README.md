[![GPLv3 License](https://img.shields.io/badge/License-GPL%20v3-yellow.svg)](https://opensource.org/licenses/)  

# Lostcpp

Lostcpp is a simple 3D game using OpenGL 3.3 Core. Here we don't want using or creating any game engine, because we don't really want any kind of abstractions.

## Build

Build lostcpp using the following commands

```bash
  git clone https://github.com/sgf4/lostcpp
  cd lostcpp
  git submodule update --init --recursive --depth 1
  mkdir build 
  cd build
  cmake .. -DCMAKE_BUILD_TYPE=Release
  make -j 4
```

For cross compiling you will need using MSYS2 or Arch Linux using `x86_64-w64-mingw32-cmake` instead cmake

## Support

If you are interested for working in this project, join to our discord server https://discord.gg/qYDtQY62sj

## Authors

- [@sgf4](https://www.github.com/sgf4)


