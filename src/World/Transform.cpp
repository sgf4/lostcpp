#include "Transform.hpp"
#include <glm/gtx/transform.hpp>

static void clampRotation(float& f) {
    f -= 360 * (int)(f/180);
}

void Transform::update() {
    m_model = glm::mat4 { 1.f };
    m_model = glm::translate(m_model, m_position);

    clampRotation(m_rotation.x);
    clampRotation(m_rotation.y);
    clampRotation(m_rotation.z);

    m_model = glm::rotate(m_model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_model = glm::rotate(m_model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_model = glm::rotate(m_model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    
    m_model = glm::scale(m_model, m_scale);
}