#include "Triangle.hpp"
#include "Shader.hpp"


struct Triangle::Loader {
    GL::VAO m_vao;
    GL::VBO m_vbo;
    Shader shader = Shader::FromEmbed<"triangle">();
    static constexpr std::initializer_list<float> m_vertices {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    Loader();
};

Triangle::Loader::Loader() {
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(float), m_vertices.begin(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(m_vao);
    glVertexAttribPointer(shader.getAttrib("a_pos"), 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, NULL);
    glBindVertexArray(0);
}

