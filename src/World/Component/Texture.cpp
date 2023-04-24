#include "Texture.hpp"
#include <Game.hpp>
#include <HLib/stb_image.hpp>
#include <Window.hpp>

Texture::Texture(const Embed& e) {
    int c;
    int w;
    int h;

    stbi_set_flip_vertically_on_load(true);
    
    unsigned char* data = stbi_load_from_memory(e.data(), e.size(), &w, &h, &c, 0);

    m_width = w;
    m_height = h;

    // Upload
    glBindTexture(GL_TEXTURE_2D, m_texture);
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


void Texture::draw(Transform2D& transform, Align2D align) {
    auto& s = game->getShader("texture");
    transform.updateUniforms(s);

    // switch (align) {
    //     case TOP_LEFT:era& camera);
    //         break;

    //     default:
    //         break;
    // }

    glUseProgram(s);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glUniform2f(s.getUniform("ufit"), (float)m_width/WINDOW_RX, (float)m_height/WINDOW_RY);
    glUniform2f(s.getUniform("utex_offset"), 0, 0);
    glUniform2f(s.getUniform("utex_size"), 1, 1);
    glUniform4f(s.getUniform("ucolor"), 1, 1, 1, 1);
    glBindVertexArray(GL::instance->getSquareVAO());
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Texture::draw(Transform& transform, Camera& camera) {
    auto& s = game->getShader("texture3d");
    transform.updateUniforms(s);
    camera.updateUniforms(s);
    
    glUseProgram(s);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glUniform2f(s.getUniform("ufit"), (float)m_width/m_height, (float)1.0);
    glUniform2f(s.getUniform("utex_offset"), 0, 0);
    glUniform2f(s.getUniform("utex_size"), 1, 1);
    glUniform4f(s.getUniform("ucolor"), 1, 1, 1, 1);
    glBindVertexArray(GL::instance->getSquareVAO());
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
    glUseProgram(0);
}