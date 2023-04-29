#pragma once
#include "../Loader.hpp"
#include "World.hpp"
#include "Entity.hpp"
#include "Component/Triangle.hpp"

class ExampleWorld : public World {

public:
    void init() {
        getComponentManager().loadComponent<Triangle>();
        Entity& e = addEntity();
        e.addComponent<Triangle>();
    }

    void update() {
        World::update();
    }
};