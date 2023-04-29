#pragma once 
#include <ECS/Entity.hpp>
#include "Window.hpp"
#include "World/Component/Texture.hpp"
#include "World/Component/Transform2D.hpp"


#include <Loader.hpp>
#include <GL.hpp>
#include "../World.hpp"
#include "glm/gtx/string_cast.hpp"
#include <Embed/Embed.hpp>

struct CatLoader {
    GL::Texture texture_cat {getEmbed<"cat.jpg">()};
};

struct Cat : Entity, Transform, Texture {

    Cat(float x, float y, float z)
     : Texture(getLoader<CatLoader>().texture_cat) {
        scale = {1, 1, 1};
    }

    void update() {
        Texture::update(*this);
    }
};