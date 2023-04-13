#pragma once 
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Transform {

protected:
    glm::vec3 m_scale {1, 1, 1};
    glm::vec3 m_rotation {};
    glm::vec3 m_position {};
    glm::mat4 m_model;

    void update();

public:
    glm::vec3 getScale() {
        return m_scale;
    }

    glm::vec3 getRotation() {
        return m_rotation;
    }

    glm::vec3 getPosition() {
        return m_position;
    }

    glm::mat4 getModel() {
        return m_model;
    }

    operator glm::mat4() const {
        return m_model;
    }
};