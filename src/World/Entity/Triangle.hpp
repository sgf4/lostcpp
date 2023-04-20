#pragma once
#include "GL.hpp"
#include "Entity.hpp"
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

struct Triangle : Entity {
    Transform transform;

    Triangle(float x, float y, float z);
    void update();
};

