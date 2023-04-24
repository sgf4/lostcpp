#pragma once 
#include "Component.hpp"

#include "Transform2D.hpp"
#include <glm/vec2.hpp>
#include <GL.hpp>

class Gui {
    Transform2D transform;
public:

    Gui();

    void update();
    void update(GL::Shader& s);
    void updateUniforms(GL::Shader& s);
};