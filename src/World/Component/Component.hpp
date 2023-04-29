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
struct Component {
    u32 id;

    Component(u32 eId) : id(eId) {}

    Entity& getEntity() {
        return WORLD.getEntity(id);
    }
};


class ComponentManager {
    std::bitset<NComponents> m_loadedMask;

    template<typename T>
    using Pool = std::unique_ptr<std::vector<T>>;

    template<typename... Ts>
    using MultiPool = std::tuple<Pool<Ts>...>;

    TupleForward<ComponentList, MultiPool> m_componentPool;
public:

    ComponentManager();
    ~ComponentManager();
    
    template<typename T>
    static consteval u32 getComponentId() {
        return TupleGetIndex<T, ComponentList>;
    }

    template<typename T>
    void loadComponent() {
        m_loadedMask.set(getComponentId<T>());
        
        auto& uniq = std::get<Pool<T>>(m_componentPool);
        uniq = std::make_unique<std::vector<T>>();
        uniq->reserve(32);
    }

    void update();

    template<typename T, typename... Ts>
    u32 addComponent(Ts&&... args) {
        std::vector<T>& pool = *std::get<Pool<T>>(m_componentPool);
        pool.emplace_back(std::forward<Ts>(args)...);
        return pool.size();
    }

    template<typename T>
    T& getComponent(u32 id) {
        std::vector<T>& pool = *std::get<Pool<T>>(m_componentPool);
        return pool[id];
    }

    template<typename T>
    void delComponent(u32 id) {
        std::vector<T>& pool = *std::get<Pool<T>>(m_componentPool);
        T& last = pool[pool.size()-1];
        T& replaced = pool[id];
        replaced = std::move(last);
        replaced.id = id;
        pool.pop_back();
    }
};

