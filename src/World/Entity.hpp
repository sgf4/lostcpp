#pragma once 
#include "World.hpp"
#include "Transform.hpp"

class Entity : public Update, public Transform {
public:
    Entity() {
        World::current->addUpdate(this);
    }

    void update() {
        Transform::update();
    }

    ~Entity() {
        World::current->delUpdate(this);
    }
};