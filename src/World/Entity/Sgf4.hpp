#pragma once 
#include "Entity.hpp"
#include "World/Component/Texture2D.hpp"
#include "World/Component/Transform2D.hpp"


#include <Loader.hpp>
#include <GL.hpp>
#include "../World.hpp"

struct Sgf4 : Entity {
    GL::EmbedTexture<"sgf4"> sgf4Texture;
    Transform2D transform {{}, {0.4, 0.4}};
    Texture2D texture {sgf4Texture};

    void update() {
        transform.rotation += 100.f * WTIME.getDelta();
        texture.update(transform);
    }
};