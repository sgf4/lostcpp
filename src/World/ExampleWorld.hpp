#pragma once
#include "World.hpp"
#include "Triangle.hpp"
#include "../Loader.hpp"

class ExampleWorld : public World {
    EntityLoader<Triangle> m_loader;

public:
    ExampleWorld() {
        for (int x=0; x<10; x++) {
            for (int y=0; y<10; y++) {
                for (int z=0; z<10; z++) {
                    addEntity<Triangle>(x, y, z);
                }
            }
        }
    }

    void update() {
        m_loader.update();
        World::update();
    }
};