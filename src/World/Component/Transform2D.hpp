#pragma once 
#include "Component.hpp"

#include <glm/vec2.hpp>
#include <GL.hpp>

#define TRANSFORM2D getComponent<Transform2D>()

class Transform2D : public Component {
public:
    Transform2D(Entity& e, glm::vec2 position = {0, 0}, glm::vec2 scale = {1, 1}, float rotation = 0);

    glm::mat3 model { 1.f };
    glm::vec2 position;
    glm::vec2 scale; 
    float rotation;
    void update(Entity& e);
    void updateUniforms(GL::Shader& s);
};