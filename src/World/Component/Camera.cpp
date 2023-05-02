#include "Camera.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Shader.hpp"
#include "../Entity.hpp"
#include "Window.hpp"

void Camera::init() {
    addComponent<Transform>();
    TRANSFORM.setPosition({0.0, 0.0, -1.0});

}

void Camera::update() {
    auto& t = TRANSFORM;
    pitch = glm::clamp(pitch, -89.f, 89.f);
    direction.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    direction.y = std::sin(glm::radians(pitch));
    direction.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    direction = glm::normalize(direction);
    t.model = glm::lookAt(t.position, t.position - direction, up);

    // set projection
    proj = glm::perspective(glm::radians(fov), (float)WINDOW.getResolutionRatio(), 0.01f, 10000.0f);
    yaw = std::fmod(yaw, 360.f);

    if (!control) return;

    auto dir = WINDOW.getMouseDir();
    yaw += dir.x;
    pitch += dir.y;

    glm::vec3 mov = {
        std::cos(glm::radians(yaw))*WTIME.delta*2.0, 
        0.0, 
        std::sin(glm::radians(yaw))*WTIME.delta*2.0
    };

    if (WINDOW.getKey(KEY_W)) t.position += mov;
    if (WINDOW.getKey(KEY_S)) t.position -= mov;
    if (WINDOW.getKey(KEY_D)) t.position += glm::cross(mov, up);
    if (WINDOW.getKey(KEY_A)) t.position -= glm::cross(mov, up);

    // Update uniforms
    for (GL::Shader* s : GL::Shader::shaders) {
        try {
            glUseProgram(*s);
            glUniformMatrix4fv(s->getUniform("uview"), 1, GL_FALSE, glm::value_ptr(t.model));
            glUniformMatrix4fv(s->getUniform("uproj"), 1, GL_FALSE, glm::value_ptr(proj));
        } catch (const std::out_of_range& e) {}
    }
    glUseProgram(0);

}

