#pragma once
#include "World.hpp"
#include "Triangle.hpp"
#include "../Loader.hpp"

class ExampleWorld : public World {
    LoadManager<Triangle> m_loader;

    Triangle m_triangle;
    
public:
    ExampleWorld() {
        printf("%s\n", __PRETTY_FUNCTION__);
    }
    ~ExampleWorld() {
        printf("%s\n", __PRETTY_FUNCTION__);
    }

    void update() {
        World::update();
    }
};

