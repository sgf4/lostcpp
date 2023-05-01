#include "Triangle.hpp"
#include "../Entity.hpp"

void Triangle::init() {
    addComponent<Transform2D>();
}

void Triangle::update() {
    auto& l = getSystem<Triangle>();
    glBindVertexArray(l.vao);
    glUseProgram(l.shader);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
    glUseProgram(0);
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

    BasicComponentSystem<Triangle>::update();
}