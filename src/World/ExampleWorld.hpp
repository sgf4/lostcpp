#pragma once
#include "World.hpp"
#include "Entity.hpp"
#include "Component/Component.hpp"

class ExampleWorld : public World {

public:
    void init() {
        getComponentManager().load<Triangle>();
        Entity& e = addEntity();
        e.addComponent<Triangle>();
    }

    void update() {
        World::update();
    }
};