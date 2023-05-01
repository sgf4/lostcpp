#pragma once
#include <GL.hpp>
#include "Transform.hpp"

class Triangle : public Component {
public:
    void init();
    void update();
};

template<>
struct ComponentSystem<Triangle> : BasicComponentSystem<Triangle> {
    GL::VAO vao;
    GL::VBO vbo;
    GL::EmbedShader<"triangle"> shader;

    enum Attribs {
        APOS,
        ACOLOR
    };
    
    void update();
    ComponentSystem();
};