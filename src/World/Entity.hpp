#pragma once 
#include "Transform.hpp"
#include "Component.hpp"
#include "ComponentList.hpp"

class Entity {
    std::array<std::unique_ptr<Component>, 64> m_components;
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

    template<typename... Ts>
    bool hasComponents() const {
        return ((m_components[getComponentIndex<Ts>()].get() > 0) && ...);
    }

    virtual void update() {
        for (auto& component : m_components) {
            component->update();
        }
    }

    virtual ~Entity() {
    }
};

