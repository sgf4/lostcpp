#include "Texture2D.hpp"
#include "World/Component/Transform2D.hpp"
#include <GL.hpp>
#include <Game.hpp>
#include <glm/gtc/type_ptr.hpp>

Texture2D::Texture2D(Entity& e, GL::Texture& texture) : m_texture(&texture) {
    e.requiredComponents<Transform2D>();
}

void Texture2D::update(Entity& e) {
    auto& t = e.getComponent<Transform2D>();
    auto& s = game->getShader("texture");
    t.updateUniforms(s);

    glUseProgram(s);
    glBindTexture(GL_TEXTURE_2D, *m_texture);
    glBindVertexArray(GL::instance->getSquareVAO());
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
    glUseProgram(0);
}