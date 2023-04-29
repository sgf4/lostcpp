#pragma once
#include <Integers.hpp>
#include <Time.hpp>
#include <GL.hpp>
#include <unordered_set>

#define WORLD (*World::current)
#define CAMERA WORLD.getCamera()
#define WTIME WORLD.getTime()

struct ComponentManager;
class Entity;
class World {
    u64 m_id;
    Time m_time;

    std::unique_ptr<ComponentManager> m_componentManager;
    std::vector<Entity> m_entities;
    
public:

    inline static World* current;

    World();
    virtual ~World();

    Entity& addEntity();
    
    Entity& getEntity(u32 id);

    virtual void init() {}
    virtual void update() {}

    void updateEntities();
    void updateUniforms(GL::Shader& s);
    ComponentManager& getComponentManager() { return *m_componentManager; }
    
    auto getId() const { return m_id; }
    //auto& getCamera() { return m_camera; }
    Time& getTime() { return m_time; }
};
