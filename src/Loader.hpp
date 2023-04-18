#pragma once 
#include <tuple>
#include "Meta.hpp"

#define LOADER(...) inline static struct Loader : ::Loader { __VA_ARGS__ }* loader;

template<typename... Ts>
class EntityLoader {

public:
    EntityLoader() {
        ([] () {
            Ts::loader = new typename Ts::Loader();
        }(), ...);
    }

    virtual void update() {
        (Ts::loader->update(), ...);
    }

    ~EntityLoader() {
        (delete Ts::loader, ...);
    }
};

struct Loader {
    virtual void update() {}
    virtual ~Loader() {}
};

