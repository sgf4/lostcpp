#pragma once 
#include "Component.hpp"
#include <GL.hpp>
#include "../Entity/Entity.hpp"
#include "Transform2D.hpp"

class Texture2D {
    GL::Texture* m_texture;
public:
    Texture2D(GL::Texture& texture);

    void update(Transform2D& transform);
};