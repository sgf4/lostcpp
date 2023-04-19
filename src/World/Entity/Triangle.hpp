#pragma once
#include "GL.hpp"
#include "Entity.hpp"
#include <Loader.hpp>

struct Triangle : Entity {
    LOADER(
        GL::VAO vao;
        GL::VBO vbo;
        GL::EmbedShader<"triangle"> shader;

        enum Attribs {
            APOS,
            ACOLOR
        };
        
        Loader();
        void update();
    )

    Triangle(float x, float y, float z);
    void update();
};

