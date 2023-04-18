#pragma once
#include "GL.hpp"
#include "Entity.hpp"
#include "Camera.hpp"
#include "World.hpp"
#include "../Loader.hpp"
#include "Window.hpp"
#include "Components/Transform.hpp"

struct Triangle : EntityWithComponents<Transform> {
    LOADER(
        GL::VAO vao;
        GL::VBO vbo;
        GL::EmbedShader<"triangle"> shader;
        static constexpr std::initializer_list<float> vertices {
           -0.5f,-0.5f,    1.f, 1.f, 0.f,
            0.5f, -0.5f,   0.f, 1.f, 1.f,
            0.0f,  0.5f,   1.f, 0.f, 1.f
        };
        enum Attribs {
            APOS,
            ACOLOR
        };
        
        Loader() {
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.begin(), GL_DYNAMIC_DRAW);
            
            glBindVertexArray(vao);
            glVertexAttribPointer(APOS, 2, GL_FLOAT, GL_FALSE, sizeof(float)*5, NULL);
            glEnableVertexAttribArray(APOS);
            glVertexAttribPointer(ACOLOR, 3, GL_FLOAT, GL_FALSE, sizeof(float)*5, (void*)(2*sizeof(float)));
            glEnableVertexAttribArray(ACOLOR);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void update() {
            CAMERA.updateUniforms(shader);
        }
    )

    void update() {
        Entity::update();
        TRANSFORM.updateUniforms(loader->shader);

        glBindVertexArray(loader->vao);
        glUseProgram(loader->shader);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);
        glUseProgram(0);

        if (WINDOW.getKey(KEY_RIGHT)) TRANSFORM.rotation.z += 0.5;
        if (WINDOW.getKey(KEY_LEFT)) TRANSFORM.rotation.z -= 0.5;
    }
};

