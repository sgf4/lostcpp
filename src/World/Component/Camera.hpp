#pragma once 
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <unordered_map>
#include "Component.hpp"

#include "Transform.hpp"

class Camera : public Component {
public:
    bool control { false };
    glm::vec3 direction;
    glm::vec3 up {0, 1, 0};
    glm::mat4 proj;
    float fov {75.f}, yaw {0.f}, pitch {0.f};

    void init();
    void update();
    //void updateUniforms(GL::Shader&);
    Camera& setControl(bool v) { control = v; return *this; }
};