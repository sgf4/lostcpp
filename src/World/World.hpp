#pragma once
#include "../Integers.hpp"
#include "../Game.hpp"
#include "../Pimpl.hpp"
#include "Camera.hpp"
#include "../Window.hpp"
#include "../Time.hpp"
#include "Entity.hpp"
#include "Loader.hpp"

#include <unordered_set>

#define WORLD (*World::current)
#define CAMERA WORLD.getCamera()
#define WTIME WORLD.getTime()

class World;

class World {
    u64 m_id;
    Time m_time;
    Camera m_camera;
    std::unordered_set<Entity*> m_entities;
public:

    inline static World* current;

    World();
    virtual ~World();

    void addEntity(Entity* e);
    void delEntity(Entity* e);

    void update();
    auto getId() const { return m_id; }
    auto& getCamera() { return m_camera; }
    Time& getTime() { return m_time; }
};

