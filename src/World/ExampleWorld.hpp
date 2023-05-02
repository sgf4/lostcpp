#pragma once
#include "World.hpp"
#include "Entity.hpp"
#include "Component/Component.hpp"
#include "Component/Triangle.hpp"

class ExampleWorld : public World {

public:
    void init() {
        getComponentManager().load<Triangle>();

        for (int i=0; i<10; i++) {
            for (int j=0; j<10; j++) {
                for (int k=0; k<10; k++) {
                    addEntity().addComponent<Triangle>().getComponent<Transform>().position = glm::vec3(i, j, k);
                }
            }
        }
    }

    void update() {
        
    }
};