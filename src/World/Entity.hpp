#pragma once 
#include "Component/Component.hpp"
#include "Entity.hpp"
#include "World.hpp"

#include <array>

#define ENTITY getEntity()

class Entity {
    std::array<u32, NComponents> m_componentKeys;
public:
    u32 id;

    void update() {}

    template<typename T>
    T& addComponent() {
        ComponentManager& cm = WORLD.getComponentManager();
        u32 id = cm.addComponent<T>();
        setKey(ComponentManager::getComponentId<T>(), id);
        return cm.getComponent<T>(id);
    }

    template<typename T>
    T& getComponent() {
        ComponentManager& cm = WORLD.getComponentManager();
        return cm.getComponent<T>(m_componentKeys[ComponentManager::getComponentId<T>()]);
    }

    void setKey(u32 k, u32 v) { m_componentKeys[k] = v; }

    auto getId() { return id; }
    operator u32() { return getId(); }
};

