#pragma once 
#include "Integers.hpp"
#include "Embed.hpp"

namespace GL {

class Texture {
    u32 m_id;
    u16 m_width;
    u16 m_height;

public:
    Texture(Embed& e);
    Texture();
    ~Texture();

    operator u32() { return m_id; }
};


template<FixedString str>
struct EmbedTexture : Texture {
    EmbedTexture() : Texture(embed<str + ".png">.newXorInstance()) {}
};

};