#include "Texture.hpp"
#include <Game.hpp>
#include <Window.hpp>

Texture::Texture(GL::Texture& t) : m_texture(&t) {

}


void Texture::update(Transform2D& transform) {
    auto& s = game->getShader("texture");
    transform.updateUniforms(s);

    glUseProgram(s);
    glBindTexture(GL_TEXTURE_2D, *m_texture);
    glUniform2f(s.getUniform("ufit"), (float)m_texture->getWidth()/WINDOW_RX, (float)m_texture->getHeight()/WINDOW_RY);
    glUniform2f(s.getUniform("utex_offset"), 0, 0);
    glUniform2f(s.getUniform("utex_size"), 1, 1);
    glUniform4f(s.getUniform("ucolor"), 1, 1, 1, 1);
    glBindVertexArray(GL::instance->getSquareVAO());
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Texture::update(Transform& transform, Camera& camera) {
    auto& s = game->getShader("texture3d");
    transform.updateUniforms(s);
    camera.updateUniforms(s);
    
    glUseProgram(s);
    glBindTexture(GL_TEXTURE_2D, *m_texture);
    glUniform2f(s.getUniform("ufit"), (float)m_texture->getWidth()/m_texture->getHeight(), (float)1.0);
    glUniform2f(s.getUniform("utex_offset"), 0, 0);
    glUniform2f(s.getUniform("utex_size"), 1, 1);
    glUniform4f(s.getUniform("ucolor"), 1, 1, 1, 1);
    glBindVertexArray(GL::instance->getSquareVAO());
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
    glUseProgram(0);
}