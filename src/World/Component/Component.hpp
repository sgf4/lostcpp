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
    struct Loader {
        virtual ~Loader() {}
    };

    u32 eId;

    void init() {}
    void update() {}
    void destroy() {}

    Entity& getEntity() {
        return WORLD.getEntity(eId);
    }
};

class ComponentManager {
    std::bitset<NComponents> m_loadedMask;

    template<typename T>
    using Pool = std::unique_ptr<std::vector<T>>;

    template<typename... Ts>
    using MultiPool = std::tuple<Pool<Ts>...>;

    TupleForward<ComponentList, MultiPool> m_pool;
    std::array<std::unique_ptr<Component::Loader>, NComponents> m_loaders;
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

    template<typename T>
    Entity& getEntity(u32 id);

    template<typename... Ts>
    bool isLoaded() {
        return (m_loadedMask[getId<Ts>] && ...);
    }

    void update();

    template<typename T>
    T& add(Entity&);

    template<typename T>
    void del(Entity&);

    template<typename T>
    T& get(u32 id);

};

