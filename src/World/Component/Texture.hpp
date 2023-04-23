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

    enum Fit : u8 {
        SCALE,
        COVER,
        CONTAIN
    };

    Texture(const Embed& e);
    
    void draw(GL::Shader& s, Fit fit);
    void draw(Transform2D& transform, Fit fit = COVER);
    void draw(Transform& transform, Camera& camera, Fit fit = COVER);
    u32 getWidth() const { return m_width; }
    u32 getHeight() const { return m_height; }
};