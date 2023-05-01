#pragma once
#include "World.hpp"
#include "Entity.hpp"
#include "Component/Component.hpp"

class ExampleWorld : public World {

public:
    void init() {
        getComponentManager().load<Triangle>();

        for (int i=0; i<100; i++) {
            Entity& e = addEntity();
            e.addComponent<Triangle>();
        }
        //delEntity(e.id);
    }

    void update() {
        
    }
};