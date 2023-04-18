#pragma once
#include "World.hpp"
#include "Triangle.hpp"
#include "../Loader.hpp"

class ExampleWorld : public World {
    EntityLoader<Triangle> m_loader;

public:
    ExampleWorld() {
        addEntity<Triangle>();
    }

    void update() {
        m_loader.update();
        World::update();
    }
};