#include "Texture.hpp"
#include <HLib/stb_image.hpp>
#include <GL.hpp>

using namespace GL;

Texture::Texture() {
    glGenTextures(1, &m_id);
}

Texture::Texture(Embed& e) : Texture() {
    int c;
    int w;
    int h;

    stbi_set_flip_vertically_on_load(true);
    
    unsigned char* data = stbi_load_from_memory(e.data(), e.size(), &w, &h, &c, 0);

    m_width = w;
    m_height = h;

    // Upload
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    int format = GL_RGBA;
    switch (c) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
    }
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);
}


Texture::~Texture() {
    glDeleteTextures(1, &m_id);
}