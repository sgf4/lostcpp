#pragma once
#include "GL.hpp"
#include "Transform.hpp"

struct TriangleLoader {
    GL::VAO vao;
    GL::VBO vbo;
    GL::EmbedShader<"triangle"> shader;

    enum Attribs {
        APOS,
        ACOLOR
    };
    
    TriangleLoader() {}
};

class Triangle : public Component {
public:

    void update() {}
};

