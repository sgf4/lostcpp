#pragma once 
#include "Component/Component.hpp"
#include "Entity.hpp"
#include "World.hpp"

#include <array>
#include <bitset>

#define ENTITY getEntity()

class Entity {
    std::array<u32, NComponents> m_componentKeys;
    std::bitset<NComponents> m_componentMask;
public:
    u32 id;

    template<typename T>
    static consteval u32 getComponentId() {
        return ComponentManager::getId<T>();
    }

    template<typename T>
    T& addComponent() {
        return WORLD.getComponentManager().add<T>(*this);
    }

    template<typename T>
    void delComponent() {
        WORLD.getComponentManager().del<T>(*this);
    }

    template<typename... Ts>
    bool hasComponent() {
        return (m_componentMask[getComponentId<Ts>()] && ...);
    }

    template<typename T>
    T& getComponent() {
        ComponentManager& cm = WORLD.getComponentManager();
        return cm.get<T>(*this);
    }

    std::bitset<NComponents>& getComponentMask() { 
        return m_componentMask;
    }

    template<typename T>
    void setComponentKey(u32 v) { 
        m_componentKeys[getComponentId<T>()] = v; 
    }

    template<typename T>
    u32 getComponentKey() { 
        return m_componentKeys[getComponentId<T>()]; 
    }

    auto getId() { return id; }
    operator u32() { return getId(); }

    void destroy() {
        WORLD.getComponentManager().delAll(*this);
    }

    void updateId(u32 i) {
        id = i;
        WORLD.getComponentManager().updateIds(*this);
    }
};

