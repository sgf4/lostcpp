#pragma once 
#include <tuple>
#include "Pimpl.hpp"

template<typename T>
inline typename T::Loader* loader;

template<typename... Ts>
class LoadManager {

public:
    LoadManager() {
        ([] () {
            loader<Ts> = new typename Ts::Loader();
        }(), ...);
    }

    ~LoadManager() {
        (delete loader<Ts>, ...);
    }
};

