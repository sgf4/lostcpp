#pragma once 
#include "World.hpp"
#include "Transform.hpp"
#include "GL.hpp"

class Entity : public Update, public Transform {
    GL::Shader* m_shader {};
public:

    Entity() {
        World::current->addUpdate(*this);
    }

    Camera& getCamera() {
        return World::current->getCamera();
    }

    void setEntityShader(GL::Shader& shader) {
        if (m_shader) getCamera().delShader(*m_shader);
        World::current->getCamera().addShader(shader);
        m_shader = &shader;
    }

    void update() {
        Transform::update();
        if (m_shader) Transform::updateUniforms(*m_shader);
    }

    ~Entity() {
        if (m_shader) getCamera().delShader(*m_shader);
        World::current->delUpdate(*this);
    }
};