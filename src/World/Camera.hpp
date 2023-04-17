#pragma once 
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <unordered_map>

#include "World/Transform.hpp"

class Camera : public Transform {
    float m_fov, m_yaw, m_pitch;
    bool m_control;
    glm::vec3 m_direction;
    glm::mat4 m_proj;
    std::unordered_map<GL::Shader*, u32> m_shaders;

public:
    Camera(bool control=false);
    ~Camera();

    void addShader(GL::Shader& shader);
    void delShader(GL::Shader& shader);

    void update();
};