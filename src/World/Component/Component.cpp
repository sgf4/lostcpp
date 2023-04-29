#include "Component.hpp"
#include "Transform.hpp"
#include "Transform2D.hpp"
#include "Physics.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Triangle.hpp"


ComponentManager::ComponentManager() {

}

void ComponentManager::update() {
    TupleForwardFn<ComponentList>([&] <typename... Ts> () {
        ([&] <typename T> () {
            std::vector<T>& pool = *std::get<Pool<T>>(m_componentPool);
            for (T& component : pool) {
                component.update();
            }
        }.template operator()<Ts>(), ...);
    });
}

ComponentManager::~ComponentManager() {

}