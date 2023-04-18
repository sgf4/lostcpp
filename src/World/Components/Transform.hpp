#pragma once
#include "../Component.hpp"

#include <GL.hpp>
#include <glm/vec3.hpp>

#define TRANSFORM getComponent<Transform>()

class Transform : public Component {
    

public:
    glm::mat4 model { 1.f };
    glm::vec3 scale {1, 1, 1};
    glm::vec3 rotation {};
    glm::vec3 position {};

    void update();
    void updateUniforms(GL::Shader&);


    void setPosition(float x, float y, float z) { position = {x, y, z}; }

    virtual ~Transform() {}
};