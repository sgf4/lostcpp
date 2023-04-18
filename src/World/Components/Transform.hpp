#pragma once
#include "../Component.hpp"

#include <GL.hpp>
#include <glm/vec3.hpp>

#define TRANSFORM getComponent<Transform>()

class Transform : public Component {
    

public:
    glm::mat4 model { 1.f };
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    void update();
    void updateUniforms(GL::Shader&);

    Transform(glm::vec3 position = {0, 0, 0}, glm::vec3 rotation = {0, 0, 0}, glm::vec3 scale = {1, 1, 1});


    void setPosition(float x, float y, float z) { position = {x, y, z}; }

    virtual ~Transform() {}
};