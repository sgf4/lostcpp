#pragma once 
#include <tuple>
#include "Pimpl.hpp"

template<typename... Ts>
class LoadManager {

public:
    LoadManager() {
        ([] () {
            Ts::template loader = new typename Ts::Loader();
        }, ...);
    }
};

#define LOADER() struct Loader; static Loader* loader; static void InitLoader(); static void DestroyLoader()

#define LOADER_CPP(NAME) static void InitLoader() { NAME## }