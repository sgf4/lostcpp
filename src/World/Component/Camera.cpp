#include "Camera.hpp"

#include <GL.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "../Entity.hpp"
#include "Window.hpp"

void Camera::init() {
    TRANSFORM.setPosition(0.0, 0.0, -1.0);
}

void Camera::update() {
    auto& t = TRANSFORM;
    m_pitch = glm::clamp(m_pitch, -89.f, 89.f);
    m_direction.x = std::cos(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
    m_direction.y = std::sin(glm::radians(m_pitch));
    m_direction.z = std::sin(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
    m_direction = glm::normalize(m_direction);
    t.model = glm::lookAt(t.position, t.position - m_direction, {0.0, 1.0, 0.0});

    // set projection
    m_proj = glm::perspective(glm::radians(m_fov), (float)WINDOW.getResolutionRatio(), 0.01f, 10000.0f);
    m_yaw = std::fmod(m_yaw, 360.f);

    for (GL::Shader* s : m_shaders) {
        updateUniforms(*s);
    }

    if (!m_control) return;

    auto dir = WINDOW.getMouseDir();
    m_yaw += dir.x;
    m_pitch += dir.y;

    float mov_x = std::cos(glm::radians(m_yaw))*WTIME.getDelta()*2.0;
    float mov_z = std::sin(glm::radians(m_yaw))*WTIME.getDelta()*2.0;

    if (WINDOW.getKey(KEY_W)) t.position += glm::vec3(mov_x, 0.f, mov_z);
    if (WINDOW.getKey(KEY_S)) t.position += glm::vec3(-mov_x, 0.f, -mov_z);
    if (WINDOW.getKey(KEY_A)) t.position += glm::vec3(mov_z, 0.f, -mov_x);
    if (WINDOW.getKey(KEY_D)) t.position += glm::vec3(-mov_z, 0.f, mov_x);
}

void Camera::addShader(GL::Shader& s) {
    m_shaders.insert(&s);
}

void Camera::delShader(GL::Shader& s) {
    m_shaders.erase(&s);
}

void Camera::updateUniforms(GL::Shader& s) {
    auto& t = TRANSFORM;
    glUseProgram(s);
    glUniformMatrix4fv(s.getUniform("uview"), 1, GL_FALSE, glm::value_ptr(t.model));
    glUniformMatrix4fv(s.getUniform("uproj"), 1, GL_FALSE, glm::value_ptr(m_proj));
    glUseProgram(0);
}