/*  Copyright (C) 2023 sgf4

This file is part of lostcpp.

lostcpp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

lostcpp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with lostcpp.  If not, see <http://www.gnu.org/licenses/>. */

#pragma once
#include <marble/component.hpp>
#include <embed.hpp>

struct Cube : ME::Component {

    void init();
    void update();
};

#define cube_fbx embed<"cube.fbx">
LOADER(Cube,
    GL::Model model { cube_fbx.newXorInstance(), static_cast<u32>(cube_fbx.size) };
);


