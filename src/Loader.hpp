#pragma once 
#include <tuple>
#include "Meta.hpp"

template<typename T>
inline T* loader;

template<typename T>
T* getLoader() {
    return loader<T>;
}

template<typename... Ts>
class Loader {

public:
    Loader() {
        ([&] () {
            loader<Ts> = new Ts();
        }(), ...);
    }

    ~Loader() {
        (delete loader<Ts>, ...);
    }
};

