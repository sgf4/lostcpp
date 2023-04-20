#include "Texture.hpp"
#include <Game.hpp>

Texture::Texture(GL::Texture t) : m_texture(std::move(t)) {
}

void Texture::draw(GL::Shader& s) {
    glUseProgram(s);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glUniform2f(s.getUniform("utex_offset"), 0, 0);
    glUniform2f(s.getUniform("utex_size"), 1, 1);
    glUniform4f(s.getUniform("ucolor"), 1, 1, 1, 1);
    glBindVertexArray(GL::instance->getSquareVAO());
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Texture::update(Transform2D& transform) {
    auto& s = game->getShader("texture");
    transform.update(s);

    draw(s);
}

void Texture::update(Transform& transform, Camera& camera) {
    auto& s = game->getShader("texture3d");
    transform.updateUniforms(s);
    camera.updateUniforms(s);
    
    draw(s);
}