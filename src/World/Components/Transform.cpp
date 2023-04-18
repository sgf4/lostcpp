#include "Transform.hpp"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static float clampRotation(float f) {
    f -= 360 * (int)(f/180);
    return f;
}

void Transform::update() {
    model = glm::mat4 { 1.f };
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(clampRotation(rotation.x)), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(clampRotation(rotation.y)), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(clampRotation(rotation.z)), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);
}

void Transform::updateUniforms(GL::Shader& s) {
    glUseProgram(s);
    auto umodel = s.getUniform("umodel");
    glUniformMatrix4fv(umodel, 1, GL_FALSE, glm::value_ptr(model));
    glUseProgram(0);
}