#pragma once 
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <unordered_set>

#include "../Updater.hpp"
#include "World/Transform.hpp"

class Camera : public Transform, public Update {
    float m_fov, m_yaw, m_pitch;
    glm::vec3 m_direction;
    glm::mat4 m_proj { 1.f };
    std::unordered_set<GL::Shader*> m_shaders;

public:
    Camera();
    ~Camera();

    void addShader(GL::Shader* shader) {
        m_shaders.insert(shader);
    }

    void delShader(GL::Shader* shader) {
        m_shaders.erase(shader);
    }

    void update();
};