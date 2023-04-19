#pragma once 
#include "Entity.hpp"
#include "World/Component/Texture2D.hpp"
#include "World/Component/Transform2D.hpp"


#include <Loader.hpp>
#include <GL.hpp>
#include "../World.hpp"

struct Sgf4 : Entity {
    LOADER(
        GL::EmbedTexture<"sgf4"> texture;
    )

    Sgf4() {
        addComponent<Transform2D>(glm::vec2(0.5, 0.5), glm::vec2(0.3, 0.3), 10);
        addComponent<Texture2D>(loader->texture);
    }

    void update() {
        Entity::update();

        TRANSFORM2D.rotation += 100.f * WTIME.getDelta();
    }
};