#pragma once
#include "World.hpp"
#include "Entity/Triangle.hpp"
#include "../Loader.hpp"
#include "Entity/Sgf4.hpp"

class ExampleWorld : public World, public Loader<
    TriangleLoader,
    Sgf4Loader
> {

public:
    ExampleWorld() {
        addEntity<Sgf4>(1, 0, 0);
    }

    void update() {
        World::update();
    }
};