#pragma once 
#include <Integers.hpp>

class Entity;
struct Component {
    Component(Entity& e) {}
    Component() {}
    virtual void update(Entity& e) {}
    virtual ~Component() {}
};

template<typename... Ts>
struct ComponentRefs {
    std::tuple<Ts&...> refs;

    template<typename T>
    ComponentRefs(T& t) {
        ([&] () {
            std::get<Ts>(refs) = static_cast<Ts&>(t);
        }(), ...);
    }

    template<typename T>
    void get() {
        return std::get<T>(refs);
    }
};

#include "../Entity/Entity.hpp"
