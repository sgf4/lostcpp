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
class BasicComponentSystem {
    std::vector<C> m_components;

public:

    BasicComponentSystem();

    template<typename T>
    T& add(Entity& e);

    template<typename T>
    void del(Entity& e);

    template<typename T>
    T& get(Entity& e);

    void update();
};

struct Component {
    using CustomComponentSystem = void;

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
    std::unique_ptr<ComponentSystemManager> m_componentSystemManager;
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

