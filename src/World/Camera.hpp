#pragma once 
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <unordered_map>

#include "Entity/Entity.hpp"
#include "Component/Transform.hpp"

class Camera : Entity {
    Transform transform;
    float m_fov, m_yaw, m_pitch;
    bool m_control;
    glm::vec3 m_direction;
    glm::mat4 m_proj;
    std::unordered_set<GL::Shader*> m_shaders;

public:
    Camera(bool control=false);
    ~Camera();

    void update();
    //void updateUniforms(GL::Shader&);
    void addShader(GL::Shader&);
    void delShader(GL::Shader&);
};