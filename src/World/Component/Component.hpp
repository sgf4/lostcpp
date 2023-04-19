#pragma once 
#include <Integers.hpp>

class Entity;
struct Component {
    Component(Entity& e) {}
    Component() {}
    virtual void update(Entity& e) {}
    virtual ~Component() {}
};

#include "../Entity/Entity.hpp"
