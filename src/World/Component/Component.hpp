#pragma once 
#include <Integers.hpp>
#include <Meta.hpp>

#include "../World.hpp"

using ComponentList = std::tuple<
    class Transform,
    class Transform2D,
    class Camera,
    class Physics,
    class Shader,
    class Texture,
    class Triangle
>;

constexpr u32 NComponents = std::tuple_size_v<ComponentList>;

class Entity;

template<typename C>
class BasicComponentSystem {
    std::vector<C> m_components;

public:
    BasicComponentSystem() {
        m_components.reserve(32);
    }

    C& add(Entity& e);
    void del(Entity& e);
    C& get(Entity& e);

    void update();

    ~BasicComponentSystem() {}
};

template<typename C>
class ComponentSystem : public BasicComponentSystem<C> {
};

class ComponentSystemManager; 

class ComponentManager {
    std::bitset<NComponents> m_loadedMask;

    template<typename T>
    using SystemUniq = std::unique_ptr<ComponentSystem<T>>;

    template<typename... Ts>
    using SystemGroup = std::tuple<SystemUniq<Ts>...>;

    TupleForward<ComponentList, SystemGroup> m_systems;

public:

    ComponentManager();
    ~ComponentManager();
    
    template<typename T>
    static consteval u32 getId() {
        return TupleGetIndex<T, ComponentList>;
    }

    template<typename T>
    void load();

    template<typename T>
    void unload();

    void update();

    void updateIds(Entity& e);

    template<typename T>
    T& add(Entity& e) {
        return std::get<SystemUniq<T>>(m_systems)->add(e);
    }

    template<typename T>
    void del(Entity& e) {
        std::get<SystemUniq<T>>(m_systems)->del(e);
    }

    void delAll(Entity& e);

    template<typename T>
    T& get(Entity& e) {
        return std::get<SystemUniq<T>>(m_systems)->get(e);
    }

    template<typename T>
    ComponentSystem<T>& getSystem() {
        return *std::get<SystemUniq<T>>(m_systems);
    }

};

struct Component {

    u32 eId;

    void init() {}
    void update() {}
    void destroy() {}

    Entity& getEntity() {
        return WORLD.getEntity(eId);
    }

    template<typename T>
    T& addComponent() {
        return WORLD.getComponentManager().add<T>(getEntity());
    }

    template<typename T>
    T& getComponent() {
        return WORLD.getComponentManager().get<T>(getEntity());
    }

    template<typename T>
    ComponentSystem<T>& getSystem() {
        return WORLD.getComponentManager().getSystem<T>();
    }
};