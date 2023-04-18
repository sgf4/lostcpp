#pragma once 
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <unordered_map>

#include "Entity.hpp"
#include "Components/Transform.hpp"

class Camera : EntityWithComponents<Transform> {
    float m_fov, m_yaw, m_pitch;
    bool m_control;
    glm::vec3 m_direction;
    glm::mat4 m_proj;

public:
    Camera(bool control=false);
    ~Camera();

    void update();
    void updateUniforms(GL::Shader&);
};