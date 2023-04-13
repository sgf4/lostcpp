#pragma once
#include "World.hpp"
#include "Triangle.hpp"
#include "../Loader.hpp"

class ExampleWorld : public World {
    LoadManager<Triangle> m_loader;

    Triangle m_triangle;
    
public:
    void update() {
        World::update();
    }
};