#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "HLib/stb_image.h"
#include <GL.hpp>

using namespace GL;

Texture::Texture(Embed& e) {
    int channels;
    int width;
    int height;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load_from_memory(e.data(), e.size(), &width, &height, &channels, 0);

    m_width = width;
    m_height = height;

    // Upload
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);
}

Texture::Texture() {
    glGenTextures(1, &m_id);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_id);
}