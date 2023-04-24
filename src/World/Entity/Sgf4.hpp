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
    Texture texture_cat {getEmbed<"cat.jpg">()};
    Texture texture_sgf4 {getEmbed<"sgf4.png">()};
};

struct Sgf4 : Entity {
    Transform transform;
    Transform2D transform2d;

    Sgf4(float x, float y, float z) {
        transform2d.scale = {0.3, 0.3};
        transform2d.position = {1-(599.f/WINDOW_RX*0.3), 1-(599.f/WINDOW_RY*0.3)};
    }

    void update() {
        auto l = getLoader<Sgf4Loader>();
        transform.update();
        transform2d.update();
        l->texture_cat.draw(transform, WORLD.getCamera());
        l->texture_sgf4.draw(transform2d);
    }
};