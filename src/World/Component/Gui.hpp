#pragma once 
#include "Component.hpp"

#include "Transform2D.hpp"
#include <glm/vec2.hpp>
#include <GL.hpp>

class Gui : Transform2D {
public:

    enum Align2D : u8 {
        TOP_LEFT,
        TOP_CENTERED,
        TOP_RIGHT,

        MIDDLE_LEFT,
        MIDDLE_CENTERED,
        MIDDLE_RIGHT,

        BOTTOM_LEFT,
        BOTTOM_CENTERED,
    };

    Gui();

    void update();
    void update(GL::Shader& s);
    void updateUniforms(GL::Shader& s);
};