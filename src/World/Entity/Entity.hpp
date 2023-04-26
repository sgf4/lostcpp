#pragma once 
#include "../Component/Component.hpp"

#define ENTITY (*Entity::current)

class Entity {
public:
    virtual void update() {}
    virtual ~Entity() {}
};

template<typename... C>
struct EntityWithComponents : Entity, C... {
    void update() {
        (C::update(*this), ...);
    }
};