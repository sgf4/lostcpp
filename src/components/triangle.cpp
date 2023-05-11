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

#include "triangle.hpp"
#include "marble/keycodes.hpp"
//#include "Shader.hpp"
#include <marble/window.hpp>
#include <marble/world.hpp>
#include <marble/components/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace ME;

void Triangle::init() {
    getEntity().addComponent<Transform>();
    // addComponent<Shader>()
        // .setShader(getSystem<Triangle>().shader);
}

void Triangle::update() {
    auto& l = CM.getSystem<Triangle>();
    glUniformMatrix4fv(l.shader.getUniform("umodel"), 1, GL_FALSE, glm::value_ptr(TRANSFORM.model));
    glDrawArrays(GL_TRIANGLES, 0, 3);

    auto& t = getComponent<Transform>();
    if (WINDOW.getKey(KEY_LEFT)) t.addRotation(glm::vec3{0.0, 100.0, 0.0} * WTIME.delta);
    if (WINDOW.getKey(KEY_RIGHT)) t.addRotation(glm::vec3{0.0, -100.0, 0.0} * WTIME.delta);
    if (WINDOW.getKey(KEY_UP)) t.addRotation(glm::vec3{0.0, 0.0, 100.0} * WTIME.delta);
    if (WINDOW.getKey(KEY_DOWN)) t.addRotation(glm::vec3{0.0, 0.0, 100.0} * WTIME.delta);
}

static constexpr std::initializer_list<float> vertices {
    -0.5f,-0.5f,    1.f, 1.f, 0.f,
    0.5f, -0.5f,   0.f, 1.f, 1.f,
    0.0f,  0.5f,   1.f, 0.f, 1.f
};

ComponentSystem<Triangle>::ComponentSystem() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.begin(), GL_STATIC_DRAW);

    glBindVertexArray(vao);
    glVertexAttribPointer(APOS, 2, GL_FLOAT, GL_FALSE, sizeof(float)*5, NULL);
    glEnableVertexAttribArray(APOS);
    glVertexAttribPointer(ACOLOR, 3, GL_FLOAT, GL_FALSE, sizeof(float)*5, (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(ACOLOR);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //CAMERA.getComponent<Camera>().addShader(shader);
}

void ComponentSystem<Triangle>::update() {
    glBindVertexArray(vao);
    glUseProgram(shader);
    BasicComponentSystem<Triangle>::update();
    glUseProgram(0);
    glBindVertexArray(0);
}
