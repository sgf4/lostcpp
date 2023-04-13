#pragma once
#include "GL.hpp"
#include "Entity.hpp"
#include "Camera.hpp"
#include "../Loader.hpp"
#include "Window.hpp"

struct Triangle : Entity {
    inline static struct Loader {
        GL::VAO m_vao;
        GL::VBO m_vbo;
        GL::EmbedShader<"triangle"> m_shader;
        static constexpr std::initializer_list<float> m_vertices {
           -0.5f,-0.5f,    1.f, 1.f, 0.f,
            0.5f, -0.5f,   0.f, 1.f, 1.f,
            0.0f,  0.5f,   1.f, 0.f, 1.f
        };
        enum Attribs {
            APOS,
            ACOLOR
        };
        
        Loader() {
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(float), m_vertices.begin(), GL_DYNAMIC_DRAW);
            
            glBindVertexArray(m_vao);
            glVertexAttribPointer(APOS, 2, GL_FLOAT, GL_FALSE, sizeof(float)*5, NULL);
            glEnableVertexAttribArray(APOS);
            glVertexAttribPointer(ACOLOR, 3, GL_FLOAT, GL_FALSE, sizeof(float)*5, (void*)(2*sizeof(float)));
            glEnableVertexAttribArray(ACOLOR);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
    }* loader;

    Triangle() {
        setEntityShader(loader->m_shader);
    }

    void update() {
        Entity::update();

        glBindVertexArray(loader->m_vao);
        glUseProgram(loader->m_shader);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);
        glUseProgram(0);

        if (WINDOW.getKey(KEY_RIGHT)) m_rotation.z += 0.5;
        if (WINDOW.getKey(KEY_LEFT)) m_rotation.z -= 0.5;
    }
};

