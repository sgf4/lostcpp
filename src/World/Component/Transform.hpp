#pragma once
#include <GL.hpp>
#include <glm/vec3.hpp>
#include "Component.hpp"

#define TRANSFORM ENTITY.getComponent<Transform>()

class Transform : public Component {
public:
    glm::mat4 model { 1.f };
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;

    void update();
    void update(GL::Shader& s);
    void updateUniforms(GL::Shader& s);

    Transform(glm::vec3 position = {0, 0, 0}, glm::vec3 scale = {1, 1, 1}, glm::vec3 rotation = {0, 0, 0});
    void setPosition(float x, float y, float z) { position = {x, y, z}; }
};