#include "Component.hpp"
#include "../Entity.hpp"

#include "Transform.hpp"
#include "Transform2D.hpp"
#include "Physics.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Triangle.hpp"


ComponentManager::ComponentManager() {

}

void ComponentManager::update() {
    TupleForwardFn<ComponentList>([&] <typename... Ts> () {
        ([&] <typename T> () {
            if (!m_loadedMask[getId<T>()]) return;
            std::vector<T>& pool = *std::get<Pool<T>>(m_pool);
            for (T& component : pool) {
                component.update();
            }
        }.template operator()<Ts>(), ...);
    });
}

template<typename T>
void ComponentManager::load() {
    m_loadedMask.set(getId<T>());
    auto& uniq = std::get<Pool<T>>(m_pool);
    uniq = std::make_unique<std::vector<T>>();
    uniq->reserve(32);

    using ComponentLoader = typename T::Loader;
    if constexpr (!std::is_same_v<ComponentLoader, Component::Loader>) {
        std::unique_ptr<Component::Loader>& loader = m_loaders[getId<T>()];
        if (!loader.get()) loader = std::make_unique<ComponentLoader>();
    }
}

template<typename T>
void ComponentManager::unload() {
    m_loadedMask.reset(getId<T>());
    auto& uniq = std::get<Pool<T>>(m_pool);
    uniq.reset();


}

template<typename T>
T& ComponentManager::add(Entity& entity) {
    std::vector<T>& pool = *std::get<Pool<T>>(m_pool);

    auto& c = pool.emplace_back();
    c.eId = entity.id;
    entity.setComponentKey<T>(pool.size()-1);
    entity.getComponentMask().set(getId<T>());
    c.init();
    return c;
}

template<typename T>
void ComponentManager::del(Entity& entity) {
    std::vector<T>& pool = *std::get<Pool<T>>(m_pool);
    T& last = pool[pool.size()-1];
    u32 componentKey = entity.getComponentKey<T>();
    T& component = pool[componentKey];
    component.destroy();
    component = std::move(last);

    Entity& eReplaced = component.getEntity();
    eReplaced.setComponentKey<T>(componentKey);
    entity.getComponentMask().reset(getId<T>());
    pool.pop_back();
}

template<typename T>
Entity& ComponentManager::getEntity(u32 id) {
    std::vector<T>& pool = *std::get<Pool<T>>(m_pool);
    return pool[id].getEntity();
}

template<typename T>
T& ComponentManager::get(u32 id) {
    std::vector<T>& pool = *std::get<Pool<T>>(m_pool);
    return pool[id];
}

ComponentManager::~ComponentManager() {

}

template<typename C, typename R, typename... P>
void instance(R (C::*ptr) (P...)) {
    std::cout << ptr << std::endl;
}

void instanceTemplating() {
    TupleForwardFn<ComponentList>([&] <typename... Ts> () { 
        ([&] <typename T> () {
            instance(&ComponentManager::load<T>);
            instance(&ComponentManager::unload<T>);
            instance(&ComponentManager::add<T>);
            instance(&ComponentManager::del<T>);
            instance(&ComponentManager::get<T>);
            instance(&ComponentManager::getEntity<T>);
        }.template operator()<Ts>(), ...);
    });
}