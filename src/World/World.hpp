#pragma once
#include "../Updater.hpp"
#include "../Integers.hpp"
#include "../Game.hpp"
#include "../Pimpl.hpp"
#include "Camera.hpp"
#include "../Window.hpp"
#include "../Time.hpp"

#include <unordered_map>

#define WORLD (*World::current)
#define WTIME WORLD.getTime()

class World;
inline World* current_world;

class World : public Update {
    u64 m_id {game->getNewId()};
    UpdateManager m_updateManager;
    struct AddCurrent { AddCurrent(World* ptr) { current = ptr; } } m_addPtr {this};
    Time m_time;
    Camera m_camera {true};
public:

    inline static World* current;

    World() {
        game->getUpdateManager().add(*this);
        m_updateManager.add(m_time);
        WINDOW.hideCursor();
    }

    void update() {
        m_updateManager.update();
    }

    void addUpdate(Update& u) {
        m_updateManager.add(u);
    }

    void delUpdate(Update& u) {
        m_updateManager.del(u);
    }

    auto getId() const {
        return m_id;
    }

    auto& getCamera() {
        return m_camera;
    }

    Time& getTime() {
        return m_time;
    }

    virtual ~World() {
        game->getUpdateManager().del(*this);
    }
};

class WorldManager {
    std::unordered_map<uint64_t, std::unique_ptr<World>> m_worlds;
    World* m_currentWorld;


public:
    void loadWorldPtr(World* world) {
        m_currentWorld = world;
        m_worlds[world->getId()] = std::unique_ptr<World> (world);
    }

    template<typename T>
    void loadWorld() {
        loadWorldPtr(new T());
    }

    World& getCurrentWorld() {
        return *m_currentWorld;
    }
};

