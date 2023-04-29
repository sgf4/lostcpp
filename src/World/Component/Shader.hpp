#pragma once 
#include "Component.hpp"
#include <GL.hpp>

class Shader : public Component {
    
public:
    void update() {}
//     GL::Shader* m_shader;
// public:
//     void setShader(GL::Shader& s) { m_shader = &s; }
//     GL::Shader& getShader() { return *m_shader; }

//     Shader(Entity& e, GL::Shader& s) : m_shader(&s) {}
//     Shader() {}

//     void use() {
//         glUseProgram(*m_shader);
//     }

//     void use(const auto& fn) {
//         glUseProgram(*m_shader);
//         fn();
//         glUseProgram(0);
//     }

//     auto getAttrib(const char* a) {
//         return m_shader->getAttrib(a);
//     }

//     auto getUniform(const char* u) {
//         return m_shader->getUniform(u);
//     }

//     void unuse() {
//         glUseProgram(0);
//     }
};