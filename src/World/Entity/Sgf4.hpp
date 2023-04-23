#pragma once 
#include "Entity.hpp"
#include "World/Component/Texture.hpp"
#include "World/Component/Transform2D.hpp"


#include <Loader.hpp>
#include <GL.hpp>
#include "../World.hpp"
#include <Embed/Embed.hpp>

struct Sgf4Loader {
    Texture texture {getEmbed<"mark.png">()};
};

struct Sgf4 : Entity {
    Transform transform {{1., 1., 1.}};

    Sgf4(float x, float y, float z) {
    }

    void update() {
        auto l = getLoader<Sgf4Loader>();
        //transform.rotation.y += 100.f * WTIME.getDelta();
        transform.update();

        l->texture.draw(transform, WORLD.getCamera(), Texture::CONTAIN);
    }
};