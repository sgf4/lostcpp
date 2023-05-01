#pragma once
#include <Integers.hpp>
#include <Time.hpp>
#include <GL.hpp>
#include <unordered_set>

#define WORLD (*World::current)
#define CAMERA (*WORLD.camera)
#define WTIME WORLD.time

class ComponentManager;

class Entity;
class World {
    std::unique_ptr<ComponentManager> m_componentManager;
    std::vector<Entity> m_entities;
public:

    u64 id;
    Time time;
    Entity* camera;

    inline static World* current;

    World();
    virtual ~World();

    Entity& addEntity();
    Entity& getEntity(u32 id);
    void delEntity(u32 id);

    virtual void init() {}
    virtual void update() {}

    void updateWorld();
    void updateUniforms(GL::Shader& s);
    ComponentManager& getComponentManager() { return *m_componentManager; }
};
