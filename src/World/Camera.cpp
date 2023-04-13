#include "Camera.hpp"
#include "../GL.hpp"
#include "Shader.hpp"
#include <glm/gtc/type_ptr.hpp>


#include "Window.hpp"
#include "World.hpp"

Camera::Camera() {
    m_shaders.reserve(32);
    World::current->addUpdate(this);
}

void Camera::update() {
    m_pitch = glm::clamp(m_pitch, -89.f, 89.f);
    m_direction.x = std::cos(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
    m_direction.y = std::sin(glm::radians(m_pitch));
    m_direction.z = std::sin(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
    m_direction = glm::normalize(m_direction);
    m_model = glm::lookAt(m_position, m_position + m_direction, {0.0, 1.0, 0.0});

    // set projection
    m_proj = glm::perspective(glm::radians(m_fov), (float)RESOLUTION_WIDTH / RESOLUTION_HEIGHT, 0.001f, 10000.0f);

    for (GL::Shader* s : m_shaders) {
        glUseProgram(*s);
        glUniformMatrix4fv(s->getUniform("uview"), 1, GL_FALSE, glm::value_ptr(m_model));
        glUniformMatrix4fv(s->getUniform("uproj"), 1, GL_FALSE, glm::value_ptr(m_proj));
        glUseProgram(0);
    }
}

Camera::~Camera() {
    World::current->delUpdate(this);
}