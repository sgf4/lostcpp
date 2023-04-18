#pragma once 
#include "../Integers.hpp"
#include "../Meta.hpp"

class Entity;
struct Component {
    Entity* m_entity;
    virtual void update() = 0;
    virtual ~Component() {}
};
