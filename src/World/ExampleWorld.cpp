#include "ExampleWorld.hpp"

#include <stdio.h>

ExampleWorld::ExampleWorld() {
    printf("%s\n", __PRETTY_FUNCTION__);
}

ExampleWorld::~ExampleWorld() {
    printf("%s\n", __PRETTY_FUNCTION__);
}

void ExampleWorld::update() {
    World::update();
}