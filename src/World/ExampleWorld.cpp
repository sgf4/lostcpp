#include "ExampleWorld.hpp"
#include "Entity.hpp"
#include "Component/Component.hpp"
#include "Component/Triangle.hpp"
#include "Window.hpp"
#include "glm/gtx/string_cast.hpp"
#include "Component/Camera.hpp"

void ExampleWorld::init() {
    getComponentManager().load<Triangle>();

    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            for (int k=0; k<10; k++) {
                addEntity().addComponent<Triangle>().getComponent<Transform>().position = glm::vec3(i, j, k);
            }
        }
    }
}

void ExampleWorld::update() {
    auto& components = CM.getSystem<Triangle>().components;
    if (components.size()) {
        if (WINDOW.getKey(KEY_C)) {
            delEntity(components[0].eId);
        }
    }
    
    std::cout << WCAMERAC.yaw << std::endl;

    if (WINDOW.getKey(KEY_X)) {
        std::cout << getEntityCount() << "\n";
        Triangle& t = addEntity()
        .addComponent<Triangle>();
        auto& transform = t.getComponent<Transform>();
        transform = WCAMERA.getComponent<Transform>();
        //transform.rotation.y = WCAMERAC.yaw;
    }
}