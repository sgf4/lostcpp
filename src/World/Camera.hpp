#pragma once 
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <unordered_map>

#include "../Updater.hpp"
#include "World/Transform.hpp"

class Camera : public Transform, public Update {
    float m_fov {90.f}, m_yaw {90.f}, m_pitch {};
    bool m_control;
    glm::vec3 m_direction;
    glm::mat4 m_proj;
    std::unordered_map<GL::Shader*, u32> m_shaders;

public:
    Camera(bool control=false);
    ~Camera();

    void addShader(GL::Shader& shader) {
        auto it = m_shaders.find(&shader);
        if (it != m_shaders.end()) it->second++;
        else m_shaders.insert({&shader, 1});
    }

    void delShader(GL::Shader& shader) {
        auto it = m_shaders.find(&shader);
        if (it != m_shaders.end()) {
            if (--it->second) m_shaders.erase(&shader);
        }
    }

    void update();
};