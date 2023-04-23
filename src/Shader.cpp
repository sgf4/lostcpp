#include "Shader.hpp"
#include "GL.hpp"

using namespace GL;

Shader::Shader() {}
Shader::Shader(const Embed& vsource, const Embed& fsource) {
    m_program = glCreateProgram();
    u32 m_vs = glCreateShader(GL_VERTEX_SHADER);
    u32 m_fs = glCreateShader(GL_FRAGMENT_SHADER);
    
    const char* arrvsource[] { (const char*)vsource.data() };
    int arrvsourcesize[] { (int) vsource.size() };
    const char* arrfsource[] { (const char*)fsource.data() };
    int arrfsourcesize[] { (int) fsource.size() };
    glShaderSource(m_vs, 1, arrvsource, arrvsourcesize);
    glShaderSource(m_fs, 1, arrfsource, arrfsourcesize);
    glCompileShader(m_vs);
    glCompileShader(m_fs);

    // Check errors
    int success;
    char infoLog[512];
    glGetShaderiv(m_vs, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(m_vs, 512, 0, infoLog);
        fprintf(stderr, "Error compiling vertex shader: %s\n", infoLog);
    }

    glGetShaderiv(m_fs, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(m_fs, 512, 0, infoLog);
        fprintf(stderr, "Error compiling fragment shader %s\n", infoLog);
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

Shader& Shader::operator=(Shader&& other) {
    m_program = other.m_program;
    m_attributes = std::move(other.m_attributes);
    m_uniforms = std::move(other.m_uniforms);
    other.m_program = 0;
    return *this;
}

Shader::~Shader() {
    glDeleteProgram(m_program);
}
