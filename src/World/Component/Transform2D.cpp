#include "Transform2D.hpp"
#include "Shader.hpp"

#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/type_ptr.hpp>


Transform2D::Transform2D(Entity& e, glm::vec2 position, glm::vec2 scale, float rotation) 
: position(position),
  scale(scale),
  rotation(rotation) {

}

static float clampRotation(float f) {
    f -= 360 * (int)(f/180);
    return f;
}

void Transform2D::update(Entity& e) {
    model = glm::mat3 { 1.f };
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(clampRotation(rotation)));
    model = glm::scale(model, scale);

    if (e.hasComponent<Shader>()) {
        Shader& s = e.getComponent<Shader>();
        updateUniforms(s.getShader());
    }
}

void Transform2D::updateUniforms(GL::Shader& s) {
    glUseProgram(s);        
    glUniformMatrix3fv(s.getUniform("umodel"), 1, GL_FALSE, glm::value_ptr(model));
    glUseProgram(0);
}