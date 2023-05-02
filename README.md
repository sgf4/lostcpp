[![GPLv3 License](https://img.shields.io/badge/License-GPL%20v3-yellow.svg)](https://opensource.org/licenses/)  

# Lostcpp

Lostcpp is a simple 3D game using OpenGL 3.3 Core. Here we don't want using or creating any game engine, because we don't really want any kind of abstractions.
We use an ECS to manage and ease all the creation of Entities its Components.

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

## How works our ECS?
Firstly uses Worlds, which contain their self ComponentManager. The ComponentManager has a group of std::unique_ptr<ComponentSystem<T>> for each Component we have. When we load a Component will instance its ComponentSystem<T>. ComponentSystem<T> is based of BasicComponentSystem<T> which has its own std::vector\<T\> of Components grouping all the same Components of its own type avoiding branching. The BasicComponentSystem<T> is compiled for each Component so when we add a new component to our entity, we don't even need to #include the component, will be only needed to include it when we want to work with that specific component such as call its functions. 
We can also use template specification to override the ComponentSystem<T> in our own component, to load specific resources when you load your Component.
https://github.com/sgf4/lostcpp

## Support

If you are interested for working in this project, join to our discord server https://discord.gg/qYDtQY62sj

## Authors

- [@sgf4](https://www.github.com/sgf4)


