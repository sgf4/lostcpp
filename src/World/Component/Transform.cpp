#include "Transform.hpp"
#include "Shader.hpp"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static float clampRotation(float f) {
    f -= 360 * (int)(f/180);
    return f;
}

Transform::Transform(Entity& e, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) 
: position(position), 
  scale(scale),
  rotation(rotation) {
}

void Transform::update(Entity& e) {
    model = glm::mat4 { 1.f };
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(clampRotation(rotation.x)), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(clampRotation(rotation.y)), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(clampRotation(rotation.z)), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);

    if (e.hasComponent<Shader>()) {
        Shader& s = e.getComponent<Shader>();
        updateUniforms(s.getShader());
    }
}


void Transform::updateUniforms(GL::Shader& s) {
    glUseProgram(s);
    glUniformMatrix4fv(s.getUniform("umodel"), 1, GL_FALSE, glm::value_ptr(model));
    glUseProgram(0);
}