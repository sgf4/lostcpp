#pragma once
#include <GL.hpp>
#include <glm/vec3.hpp>
#include "Component.hpp"

#define TRANSFORM ENTITY.getComponent<Transform>()

class Transform : public Component {
public:
    glm::mat4 model { 1.f };
    glm::vec3 position {};
    glm::vec3 scale {1, 1, 1};
    glm::vec3 rotation {};
    bool modelNeedsUpdate { true };

    void update();
    Transform& setPosition(glm::vec3 p) { position = p; modelNeedsUpdate = true; return *this; }
    Transform& setScale(glm::vec3 s) { scale = s; modelNeedsUpdate = true; return *this; }
    Transform& setRotation(glm::vec3 r) { rotation = r; modelNeedsUpdate = true; return *this; }
};