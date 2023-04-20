#pragma once 
#include "Entity.hpp"
#include "World/Component/Texture.hpp"
#include "World/Component/Transform2D.hpp"


#include <Loader.hpp>
#include <GL.hpp>
#include "../World.hpp"

struct Sgf4 : Entity {
    Transform transform {{-2, 2, 2}};
    Texture texture {GL::EmbedTexture<"sgf4">()};

    void update() {
        transform.rotation.y += 100.f * WTIME.getDelta();
        transform.update();

        texture.update(transform, WORLD.getCamera());
    }
};