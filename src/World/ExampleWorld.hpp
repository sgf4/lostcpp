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
        // for (int x=0; x<10; x++) {
        //     for (int y=0; y<10; y++) {
        //         for (int z=0; z<10; z++) {
        //             addEntity<Sgf4>(x, y, z);
        //         }
        //     }
        // }
        addEntity<Sgf4>(-2, 2, 2);
    }

    void update() {
        World::update();
    }
};