#pragma once
#include <Integers.hpp>
#include <Time.hpp>
#include <GL.hpp>
#include <unordered_set>
#include "../Game.hpp"

#define WORLD (*World::current)
#define CAMERA (WORLD.getCamera())
#define WTIME WORLD.time
#define CM WORLD.getComponentManager()

class ComponentManager;

class Entity;
class World {
    std::unique_ptr<ComponentManager> m_componentManager;
    std::vector<Entity> m_entities;
    std::shared_ptr<Entity*> m_camera;
public:

    u64 id;
    Time time;
    

    inline static World* current;

    World();
    virtual ~World();

    Entity& addEntity();
    Entity& getEntity(u32 id);
    void delEntity(u32 id);
    Entity& getCamera() { return **m_camera.get(); }

    virtual void init() {}
    virtual void update() {}

    void updateWorld();
    void updateUniforms(GL::Shader& s);
    ComponentManager& getComponentManager() { return *m_componentManager; }
};
