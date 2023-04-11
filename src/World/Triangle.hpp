#pragma once
#include <initializer_list>
#include "GL.hpp"
#include "Shader.hpp"
#include "Entity.hpp"
#include "../Loader.hpp"

struct Triangle : Entity {
    struct Loader {
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
    };

    void update() {
        auto l = loader<Triangle>;

        glBindVertexArray(l->m_vao);
        glUseProgram(l->m_shader);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);
        glUseProgram(0);
    }
};

