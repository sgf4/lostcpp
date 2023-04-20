#pragma once 
#include "Component.hpp"
#include <GL.hpp>
#include "../Entity/Entity.hpp"
#include "Transform2D.hpp"
#include "Transform.hpp"
#include <World/Camera.hpp>

class Texture {
    GL::Texture m_texture;

    void draw(GL::Shader& s);
public:
    Texture(GL::Texture texture);

    void update(Transform2D& transform);
    void update(Transform& transform, Camera& camera);
    void update(Transform& transform);
};