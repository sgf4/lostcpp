/*  Copyright (C) 2023 sgf4

This file is part of lostcpp.

lostcpp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

lostcpp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with lostcpp.  If not, see <http://www.gnu.org/licenses/>. */

#include "ExampleWorld.hpp"
#include <marble/world.hpp>
#include <marble/window.hpp>
#include <marble/entity.hpp>
#include <components/triangle.hpp>
#include <marble/components/transform.hpp>
//#include "Component/Camera.hpp"

using namespace ME;

void ExampleWorld::init() {
    CM.load<Triangle>();

    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            for (int k=0; k<10; k++) {
                addEntity().addComponent<Triangle>().getComponent<Transform>().position = glm::vec3(i, j, k);
            }
        }
    }
}

void ExampleWorld::update() {
    auto& tsystem = CM.getSystem<Triangle>();
    if (tsystem.count()) {
        if (WINDOW.getKey(KEY_C)) {
            delEntity(tsystem.get(0).eId);
        }
    }

    if (WINDOW.getKey(KEY_X)) {
        Triangle& t = addEntity()
        .addComponent<Triangle>();
        auto& transform = t.getComponent<Transform>();
        transform = WCAMERA.getComponent<Transform>();
    }

    static float timer {};
    timer += WTIME.delta;
    if (timer > 5.f) {
        std::cout << tsystem.count() << std::endl;
        timer = 0.f;
    }
}
