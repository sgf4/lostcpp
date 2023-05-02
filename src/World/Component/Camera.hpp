#pragma once 
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <unordered_map>
#include "Component.hpp"

#include "Transform.hpp"

class Camera : public Component {
    float m_fov {90.f}, m_yaw {-90.f}, m_pitch {0.f};
    bool m_control { false };
    glm::vec3 m_direction;
    glm::mat4 m_proj;

public:

    void init();
    void update();
    //void updateUniforms(GL::Shader&);
    Camera& setControl(bool v) { m_control = v; return *this; }
};