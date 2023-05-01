#include "Component.hpp"
#include "../Entity.hpp"

#include "Transform.hpp"
#include "Transform2D.hpp"
#include "Camera.hpp"
#include "Physics.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Triangle.hpp"

template<typename C>
C& BasicComponentSystem<C>::add(Entity& e) {
    C& c = m_components.emplace_back();
    c.eId = e.id;
    e.setComponentKey<C>(m_components.size()-1);
    e.getComponentMask().set(ComponentManager::getId<C>());
    c.init();
    return c;
}

template<typename C>
void BasicComponentSystem<C>::del(Entity& e) {
    u32 componentKey = e.getComponentKey<C>();
    C& component = m_components[componentKey];
    component.destroy();
    component = std::move(*--m_components.end());
    e.getComponentMask().reset(ComponentManager::getId<C>());
    m_components.pop_back();

    if (m_components.size() == componentKey) return;

    Entity& entityFromMovedComponent = component.getEntity();
    entityFromMovedComponent.setComponentKey<C>(componentKey);
}

template<typename C>
C& BasicComponentSystem<C>::get(Entity& e) {
    return m_components[e.getComponentKey<C>()];
}


template<typename C>
void BasicComponentSystem<C>::update() {
    for (C& component : m_components) {
        component.update();
    }
}

ComponentManager::ComponentManager() {

}

void ComponentManager::update() {
    ForEachTupleType<ComponentList>([&] <typename T> () {
        if (!m_loadedMask[ComponentManager::getId<T>()]) return;
        std::get<SystemUniq<T>>(m_systems)->update();
    });
}

void ComponentManager::updateIds(Entity& e) {
    ForEachTupleType<ComponentList>([&] <typename T> () {
        if (!e.hasComponent<T>()) return;
        e.getComponent<T>().eId = e.id;
    });
}

template<typename T>
void ComponentManager::load() {
    m_loadedMask.set(ComponentManager::getId<T>());
    auto& uniq = std::get<SystemUniq<T>>(m_systems);
    uniq = std::make_unique<ComponentSystem<T>>();
}

template<typename T>
void ComponentManager::unload() {
    m_loadedMask.reset(ComponentManager::getId<T>());
    auto& uniq = std::get<SystemUniq<T>>(m_systems);
    uniq.reset();
}

void ComponentManager::delAll(Entity& e) {
    ForEachTupleType<ComponentList>([&] <typename T> () {
        if (e.hasComponent<T>()) {
            e.delComponent<T>();
        }
    });
}

ComponentManager::~ComponentManager() {

}

template<typename C, typename R, typename... P>
void instance(R (C::*ptr) (P...)) {
    std::cout << ptr << std::endl;
}

void instanceTemplating() {
    TupleForwardFn<ComponentList>([&] <typename... Ts> () { 
        ([&] <typename T> () {
            instance(&ComponentManager::load<T>);
            instance(&ComponentManager::unload<T>);
            instance(&BasicComponentSystem<T>::get);
            instance(&BasicComponentSystem<T>::add);
            instance(&BasicComponentSystem<T>::del);
            instance(&BasicComponentSystem<T>::update);
        }.template operator()<Ts>(), ...);
    });
}