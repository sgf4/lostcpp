#pragma once 
#include "Component.hpp"
#include "ComponentList.hpp"

class Entity {
    std::array<std::unique_ptr<Component>, NComponents> m_components;
public:
    
    Entity() {
    }

    template<typename T>
    static consteval u8 getComponentIndex() {
        return TupleGetIndex<T, ComponentList>;
    }

    template<typename T, typename... Ts>
    void addComponent(Ts&&... args) {
        m_components[getComponentIndex<T>()] = std::make_unique<T>(std::forward<Ts>(args)...);
    }

    template<typename T>
    T& getComponent() {
        return static_cast<T&>(*m_components[getComponentIndex<T>()]);
    }

    template<typename... Ts>
    bool hasComponents() const {
        return ((m_components[getComponentIndex<Ts>()].get() > 0) && ...);
    }

    virtual void update() {
        for (auto& component : m_components) {
            if (component.get()) component->update();
        }
    }

    virtual ~Entity() {
    }
};

template<typename... C>
struct EntityWithComponents : Entity {
    EntityWithComponents() {
        (addComponent<C>(), ...);
    }

    virtual ~EntityWithComponents() {

    }
};
