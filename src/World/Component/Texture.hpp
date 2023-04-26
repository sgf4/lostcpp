#pragma once 
#include "Component.hpp"
#include <GL.hpp>
#include "../Entity/Entity.hpp"
#include "Transform2D.hpp"
#include "Transform.hpp"
#include <World/Camera.hpp>
#include "../World.hpp"

class Texture {
    GL::Texture* m_texture;
public:

    // enum Fit : u8 {
    //     SCALE,
    //     COVER,
    //     CONTAIN
    // };

    Texture(GL::Texture& t);
    
    void update(Transform2D& transform);
    void update(Transform& transform, Camera& camera = WORLD.getCamera());
};