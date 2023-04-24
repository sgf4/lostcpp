#pragma once 
#include "Component.hpp"
#include <GL.hpp>
#include "../Entity/Entity.hpp"
#include "Transform2D.hpp"
#include "Transform.hpp"
#include <World/Camera.hpp>

class Texture {
    GL::Texture m_texture;
    u32 m_width;
    u32 m_height;

public:

    // enum Fit : u8 {
    //     SCALE,
    //     COVER,
    //     CONTAIN
    // };

    enum Align2D : u8 {
        TOP_LEFT,
        TOP_CENTERED,
        TOP_RIGHT,

        MIDDLE_LEFT,
        MIDDLE_CENTERED,
        MIDDLE_RIGHT,

        BOTTOM_LEFT,
        BOTTOM_CENTERED,
    };

    Texture(const Embed& e);
    
    void draw(Transform2D& transform, Align2D align = MIDDLE_CENTERED);
    void draw(Transform& transform, Camera& camera);
    u32 getWidth() const { return m_width; }
    u32 getHeight() const { return m_height; }
};