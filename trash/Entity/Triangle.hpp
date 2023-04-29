#pragma once
#include "GL.hpp"
#include <ECS/Entity.hpp>
#include "../Component/Transform.hpp"

struct TriangleLoader {
    GL::VAO vao;
    GL::VBO vbo;
    GL::EmbedShader<"triangle"> shader;

    enum Attribs {
        APOS,
        ACOLOR
    };
    
    TriangleLoader();
};

struct Triangle {
    Triangle(float x, float y, float z);
    void update();
};

