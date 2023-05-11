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
#include <marble/gl/gl.hpp>
#include <marble/component.hpp>
#include <embed.hpp>

class Triangle : public Component {
public:
    void init();
    void update();
};

template<>
struct ComponentSystem<Triangle> : BasicComponentSystem<Triangle> {
    GL::VAO vao;
    GL::VBO vbo;
    GL::Shader shader { embed<"shaders/triangle.vert">.newXorInstance(), embed<"shaders/triangle.frag">.newXorInstance() };

    enum Attribs {
        APOS,
        ACOLOR
    };

    void update();
    ComponentSystem();
};
