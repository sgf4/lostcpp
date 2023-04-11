#pragma once 
#include "World/World.hpp"

class Entity : public Update {
public:
    Entity() {
        World::current->addUpdate(this);
    }

    ~Entity() {
        World::current->delUpdate(this);
    }
};