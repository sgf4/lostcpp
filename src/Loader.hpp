#pragma once 
#include <tuple>
#include "Pimpl.hpp"

template<typename... Ts>
class Loader {

public:
    Loader() {
        ([] () {
            Ts::loader = new typename Ts::Loader();
        }(), ...);
    }

    ~Loader() {
        (delete Ts::loader, ...);
    }
};

