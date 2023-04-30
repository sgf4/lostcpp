#pragma once 
#include <Integers.hpp>
#include <Meta.hpp>

#include "../World.hpp"

using ComponentList = std::tuple<
    class Transform,
    class Transform2D,
    class Physics,
    class Shader,
    class Texture,
    class Triangle
>;

constexpr u32 NComponents = std::tuple_size_v<ComponentList>;

class Entity;

template<typename C>
class ComponentSystem {
    std::vector<C> m_components;

public:

    ComponentSystem();

    C& add(Entity& e);
    void del(Entity& e);
    C& get(Entity& e);

    void update();
};

struct Component {

    u32 eId;

    void init() {}
    void update() {}
    void destroy() {}

    Entity& getEntity() {
        return WORLD.getEntity(eId);
    }
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

    template<typename T>
    T& add(Entity&);

    template<typename T>
    void del(Entity&);

    template<typename T>
    T& get(Entity& e);

};

