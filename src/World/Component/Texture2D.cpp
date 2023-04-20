#include "Texture2D.hpp"
#include "World/Component/Transform2D.hpp"
#include <GL.hpp>
#include <Game.hpp>
#include <glm/gtc/type_ptr.hpp>

Texture2D::Texture2D(GL::Texture& texture) : m_texture(&texture) {
}

void Texture2D::update(Transform2D& transform) {
    auto& s = game->getShader("texture");
    transform.update(s);

    glUseProgram(s);
    glBindTexture(GL_TEXTURE_2D, *m_texture);
    glBindVertexArray(GL::instance->getSquareVAO());
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
    glUseProgram(0);
}