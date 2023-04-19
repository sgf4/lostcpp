#pragma once 
#include "../Component/Component.hpp"
#include "../Component/ComponentList.hpp"

#include <Meta.hpp>

#define ENTITY (*Entity::current)

class Entity {
    std::array<std::unique_ptr<Component>, NComponents> m_components;
public:

    inline static Entity* current;
    
    Entity() {
    }

    template<typename T>
    static consteval u8 getComponentIndex() {
        return TupleGetIndex<T, ComponentList>;
    }

    template<typename T, typename... Ts>
    T& addComponent(Ts&&... args) {
        static_assert(IsComplete<T>, "You must include the component");
        auto& component = m_components[getComponentIndex<T>()];
        component = std::make_unique<T>(*this, std::forward<Ts>(args)...);
        return static_cast<T&>(*component);
    }

    template<typename T>
    T& getComponent() {
        return static_cast<T&>(*m_components[getComponentIndex<T>()]);
    }

    template<typename T>
    bool hasComponent() const {
        return m_components[getComponentIndex<T>()].get();
    }

    template<typename... Ts>
    bool hasComponents() const {
        return ((hasComponent<Ts>()) && ...);
    }

    template<typename... Ts>
    bool hasAnyComponents() const {
        return ((m_components[getComponentIndex<Ts>()].get()) || ...);
    }

    template<typename T>
    void requiredComponent() {
        if (!hasComponent<T>()) throw std::string("Required component: ") + __PRETTY_FUNCTION__;
    }

    template<typename... Ts>
    void requiredComponents() {
        (requiredComponent<Ts>(), ...);
    }

    virtual void update() {
        for (auto& component : m_components) {
            if (component.get()) component->update(*this);
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
