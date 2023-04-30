#include "Component.hpp"
#include "../Entity.hpp"

#include "Transform.hpp"
#include "Transform2D.hpp"
#include "Physics.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Triangle.hpp"

template<typename C>
ComponentSystem<C>::ComponentSystem() {
    m_components.reserve(32);
}

template<typename C>
C& ComponentSystem<C>::add(Entity& e) {
    C& c = m_components.emplace_back();
    c.eId = e.id;
    e.setComponentKey<C>(m_components.size()-1);
    e.getComponentMask().set(ComponentManager::getId<C>());
    c.init();
    return c;
}

template<typename C>
void ComponentSystem<C>::del(Entity& e) {
    C& last = m_components[m_components.size()-1];
    u32 componentKey = e.getComponentKey<C>();
    C& component = m_components[componentKey];
    component.destroy();
    component = std::move(last);

    Entity& eReplaced = component.getEntity();
    eReplaced.setComponentKey<C>(componentKey);
    e.getComponentMask().reset(ComponentManager::getId<C>());
    m_components.pop_back();
}

template<typename C>
C& ComponentSystem<C>::get(Entity& e) {
    return m_components[e.getComponentKey<C>()];
}


template<typename C>
void ComponentSystem<C>::update() {
    for (C& component : m_components) {
        component.update();
    }
}

ComponentManager::ComponentManager() {

}

void ComponentManager::update() {
    TupleForwardFn<ComponentList>([&] <typename... Ts> () {
        ([&] <typename T> () {
            if (!m_loadedMask[ComponentManager::getId<T>()]) return;
            std::get<SystemUniq<T>>(m_systems)->update();
        }.template operator()<Ts>(), ...);
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

template<typename T>
T& ComponentManager::add(Entity& entity) {
    return std::get<SystemUniq<T>>(m_systems)->add(entity);
}

template<typename T>
void ComponentManager::del(Entity& entity) {
    std::get<SystemUniq<T>>(m_systems)->del(entity);
}

template<typename T>
T& ComponentManager::get(Entity& entity) {
    return std::get<SystemUniq<T>>(m_systems)->get(entity);
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
            instance(&ComponentManager::add<T>);
            instance(&ComponentManager::del<T>);
            instance(&ComponentManager::get<T>);
        }.template operator()<Ts>(), ...);
    });
}