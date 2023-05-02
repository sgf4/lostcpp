#pragma once
#include <Integers.hpp>
#include <Time.hpp>
#include <GL.hpp>
#include <unordered_set>
#include "../Game.hpp"

#define WORLD (*World::current)
#define WCAMERA (WORLD.getCamera())
#define WCAMERAC (WORLD.getCamera().getComponent<Camera>())
#define WTIME WORLD.time
#define CM WORLD.getComponentManager()

class ComponentManager;

class Entity;
class World {
    std::unique_ptr<ComponentManager> m_componentManager;
    std::vector<Entity> m_entities;
    std::shared_ptr<u32> m_camera;
public:

    u64 id;
    Time time;
    
    inline static World* current;

    World();
    virtual ~World();

    Entity& addEntity();
    u32 getEntityCount();
    Entity& getEntity(u32 id);
    void delEntity(u32 id);
    Entity& getCamera() { return getEntity(*m_camera); }

    virtual void init() {}
    virtual void update() {}

    void updateWorld();
    void updateUniforms(GL::Shader& s);
    ComponentManager& getComponentManager() { return *m_componentManager; }
};
