#include "Shader.hpp"
#include "GL.hpp"

using namespace GL;

Shader::Shader() {}
Shader::Shader(const char* vsource, const char* fsource) : m_vSource(vsource), m_fSource(fsource) {
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

    // Get attribs
    
    int nAttribs;
    glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTES, &nAttribs);
    for (int i=0; i<nAttribs; i++) {
        GLchar name[32];
        GLsizei length;
        GLint size;
        GLenum type;
        glGetActiveAttrib(m_program, i, sizeof(name), &length, &size, &type, name);
        m_attributes[name] = glGetAttribLocation(m_program, name);
    }

    int nUniforms;
    glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &nUniforms);
    for (int i = 0; i < nUniforms; i++) {
        GLchar name[32];
        GLsizei length;
        GLint size;
        GLenum type;
        glGetActiveUniform(m_program, i, sizeof(name), &length, &size, &type, name);
        m_uniforms[name] = glGetUniformLocation(m_program, name);
    }
}

Shader::~Shader() {
    glDeleteProgram(m_program);
}
