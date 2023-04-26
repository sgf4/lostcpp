#pragma once 
#include "Integers.hpp"
#include "Embed/Embed.hpp"

namespace GL {

class Texture {
    u32 m_id, m_width, m_height;

public:
    Texture();
    Texture(Embed& e);
    ~Texture();

    operator u32() { 
        return m_id; 
    }

    u32 getWidth() {
        return m_width;
    }

    u32 getHeight() {
        return m_height;
    }
};

};