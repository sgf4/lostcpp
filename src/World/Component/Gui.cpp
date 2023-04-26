#include "Gui.hpp"

#include <glm/gtx/matrix_transform_2d.hpp>

Gui::Gui() {
}

void Gui::update() {
    Transform2D::update();
    glm::scale(model, {1.0, 1.0});
}


void Gui::update(GL::Shader& s) {
    update();
}
