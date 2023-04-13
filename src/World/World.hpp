#pragma once
#include "../Updater.hpp"
#include "../Integers.hpp"
#include "../Game.hpp"
#include "../Pimpl.hpp"
#include "Camera.hpp"

#include <unordered_map>

class World;
inline World* current_world;

class World : public Update {
    UpdateManager m_updateManager;
    struct AddCurrent { AddCurrent(World* ptr) { current = ptr; } } m_addPtr {this};
    Camera m_camera;
    u64 m_id;
public:

    inline static World* current;

    World() {
        m_id = game->getNewId();
        game->getUpdateManager().add(this);
    }

    void update() {
        m_updateManager.update();
    }

    void addUpdate(Update* u) {
        m_updateManager.add(u);
    }

    void delUpdate(Update* u) {
        m_updateManager.del(u);
    }

    auto getId() const {
        return m_id;
    }

    auto& getCamera() {
        return m_camera;
    }

    virtual ~World() {
        game->getUpdateManager().del(this);
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

struct WorldUpdate : Update {
    WorldUpdate() {
        current_world->addUpdate(this);
    }

    ~WorldUpdate() {
        current_world->delUpdate(this);
    }
};
