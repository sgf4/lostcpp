#include "Component.hpp"
#include "../Entity.hpp"

#include "Transform.hpp"
#include "Transform2D.hpp"
#include "Physics.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Triangle.hpp"

template<typename T>
BasicComponentSystem<T>::BasicComponentSystem() {
    m_components.reserve(32);
}

template<typename C>
template<typename T>
T& BasicComponentSystem<C>::add(Entity& e) {
    T& c = m_components.emplace_back();
    c.eId = e.id;
    e.setComponentKey<T>(m_components.size()-1);
    e.getComponentMask().set(ComponentManager::getId<T>());
    c.init();
    return c;
}

template<typename C>
template<typename T>
void BasicComponentSystem<C>::del(Entity& e) {
    T& last = m_components[m_components.size()-1];
    u32 componentKey = e.getComponentKey<T>();
    T& component = m_components[componentKey];
    component.destroy();
    component = std::move(last);

    Entity& eReplaced = component.getEntity();
    eReplaced.setComponentKey<T>(componentKey);
    e.getComponentMask().reset(ComponentManager::getId<T>());
    m_components.pop_back();
}

template<typename C>
template<typename T>
T& BasicComponentSystem<C>::get(Entity& e) {
    return m_components[e.getComponentKey<T>()];
}


template<typename C>
void BasicComponentSystem<C>::update() {
    for (C& component : m_components) {
        component.update();
    }
}


class ComponentSystemManager {
    std::bitset<NComponents> m_loadedMask;

    template<typename T>
    using System = std::conditional_t<std::is_same_v<typename T::CustomComponentSystem, void>, 
        BasicComponentSystem<T>,
        typename T::CustomComponentSystem
    >;

    template<typename T>
    using SystemUniq = std::unique_ptr<System<T>>;

    template<typename... Ts>
    using SystemGroup = std::tuple<SystemUniq<Ts>...>;

    TupleForward<ComponentList, SystemGroup> m_systems;


public:

    ComponentSystemManager() {

    }

    void update() {
        TupleForwardFn<ComponentList>([&] <typename... Ts> () {
            ([&] <typename T> () {
                if (!m_loadedMask[ComponentManager::getId<T>()]) return;
                std::get<SystemUniq<T>>(m_systems)->update();
            }.template operator()<Ts>(), ...);
        });
    }

    template<typename T>
    void load() {
        m_loadedMask.set(ComponentManager::getId<T>());
        auto& uniq = std::get<SystemUniq<T>>(m_systems);
        uniq = std::make_unique<System<T>>();
    }

    template<typename T>
    void unload() {
        m_loadedMask.reset(ComponentManager::getId<T>());
        auto& uniq = std::get<SystemUniq<T>>(m_systems);
        uniq.reset();
    }

    template<typename T>
    System<T>& get() {
        return *std::get<SystemUniq<T>>(m_systems);
    }
};

ComponentManager::ComponentManager() : m_componentSystemManager(std::make_unique<ComponentSystemManager>()) {

}

void ComponentManager::update() {

}

template<typename T>
void ComponentManager::load() {
    m_componentSystemManager->load<T>();
}

template<typename T>
void ComponentManager::unload() {
    m_componentSystemManager->unload<T>();
}

template<typename T>
T& ComponentManager::add(Entity& entity) {
    return m_componentSystemManager->get<T>().template add<T>(entity);
}

template<typename T>
void ComponentManager::del(Entity& entity) {
    m_componentSystemManager->get<T>().template del<T>(entity);
}

template<typename T>
T& ComponentManager::get(Entity& entity) {
    return m_componentSystemManager->get<T>().template get<T>(entity);
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