#include "Camera.hpp"
#include "../GL.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


#include "Window.hpp"
#include "World.hpp"

Camera::Camera(bool control) : m_control(control) {
    m_shaders.reserve(32);
    World::current->addUpdate(*this);
    m_position = {0.0, 0.0, -1.0};
}

void Camera::update() {
    m_pitch = glm::clamp(m_pitch, -89.f, 89.f);
    m_direction.x = std::cos(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
    m_direction.y = std::sin(glm::radians(m_pitch));
    m_direction.z = std::sin(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
    m_direction = glm::normalize(m_direction);
    m_model = glm::lookAt(m_position, m_position + m_direction, {0.0, 1.0, 0.0});

    // set projection
    m_proj = glm::perspective(glm::radians(m_fov), (float)ASPECT_RATIO_Y, 0.01f, 10000.0f);

    for (auto [s, r] : m_shaders) {
        glUseProgram(*s);
        glUniformMatrix4fv(s->getUniform("uview"), 1, GL_FALSE, glm::value_ptr(m_model));
        glUniformMatrix4fv(s->getUniform("uproj"), 1, GL_FALSE, glm::value_ptr(m_proj));
    }
    glUseProgram(0);

    if (!m_control) return;

    auto dir = WINDOW.getMouseDir();
    m_yaw += dir.x;
    m_pitch -= dir.y;

    float mov_x = std::cos(glm::radians(m_yaw))*WTIME.getDelta()*2.0;
    float mov_z = std::sin(glm::radians(m_yaw))*WTIME.getDelta()*2.0;

    if (WINDOW.getKey(KEY_W)) m_position += glm::vec3{-mov_x, 0.f, -mov_z};
    if (WINDOW.getKey(KEY_S)) m_position += glm::vec3{mov_x, 0.f, mov_z};
    if (WINDOW.getKey(KEY_A)) m_position += glm::vec3{-mov_z, 0.f, mov_x};
    if (WINDOW.getKey(KEY_D)) m_position += glm::vec3{mov_z, 0.f, -mov_x};
}

Camera::~Camera() {
    World::current->delUpdate(*this);
}