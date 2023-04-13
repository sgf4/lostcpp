#pragma once 
#include <tuple>
#include "Pimpl.hpp"

template<typename... Ts>
class LoadManager {

public:
    LoadManager() {
        ([] () {
            Ts::loader = new typename Ts::Loader();
        }(), ...);
    }

    ~LoadManager() {
        (delete Ts::loader, ...);
    }
};

