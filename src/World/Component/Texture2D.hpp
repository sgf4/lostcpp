#pragma once 
#include "Component.hpp"
#include <GL.hpp>
#include "../Entity/Entity.hpp"

class Texture2D : public Component {
    GL::Texture* m_texture;
public:
    Texture2D(Entity& e, GL::Texture& texture);

    void update(Entity& e);
};