#pragma once 
#include "Entity.hpp"
#include "Window.hpp"
#include "World/Component/Texture.hpp"
#include "World/Component/Transform2D.hpp"


#include <Loader.hpp>
#include <GL.hpp>
#include "../World.hpp"
#include "glm/gtx/string_cast.hpp"
#include <Embed/Embed.hpp>

struct Sgf4Loader {
    GL::Texture texture_cat {getEmbed<"cat.jpg">()};
    GL::Texture texture_sgf4 {getEmbed<"sgf4.png">()};
};

struct Sgf4 : Entity, Transform, Texture {

    Sgf4(float x, float y, float z) : Texture(getLoader<Sgf4Loader>().texture_cat) {
        scale = {1, 1, 1};
    }

    void update() {
        Texture::update(*this);
    }
};