#include "Shader.hpp"
#include "GL.hpp"
#include <cstdio>
#include <unordered_map>
#include <string>

class ShaderInfo {
    std::unordered_map<std::string, u32> attribute;
    std::unordered_map<std::string, u32> uniforms;
};

Shader::Shader(const char* vsource, const char* fsource) : m_vSource(vsource), m_fSource(fsource)  {
    m_program = glCreateProgram();

    u32 m_vs = glCreateShader(GL_VERTEX_SHADER);
    u32 m_fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_vs, 1, &m_vSource, 0);
    glShaderSource(m_fs, 1, &m_fSource, 0);
    glCompileShader(m_vs);
    glCompileShader(m_fs);

    // Check errors
    int success;
    char infoLog[512];
    glGetShaderiv(m_vs, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(m_vs, 512, 0, infoLog);
        fprintf(stderr, "Compiling vertex shader: %s\n", infoLog);
    }

    glGetShaderiv(m_fs, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(m_fs, 512, 0, infoLog);
        fprintf(stderr, "Compiling fragment shader %s\n", infoLog);
    }

    // Link shaders
    glAttachShader(m_program, m_vs);
    glAttachShader(m_program, m_fs);
    glLinkProgram(m_program);

    glDeleteShader(m_vs);
    glDeleteShader(m_fs);

    // Info
    m_shaderInfo = std::make_unique<ShaderInfo>();
}

Shader::~Shader() {
    glDeleteProgram(m_program);
}


