#pragma once
#include "../Updater.hpp"
#include "../Integers.hpp"
#include "../Game.hpp"
#include "../Pimpl.hpp"

#include "StdAfx.hpp"

class World;

class World : public Update {
    UpdateManager m_updateManager;
    u64 m_id;
public:

    inline static World* current;

    World() {
        m_id = game->getNewId();
        current = this;
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
        game->getWorldManager().getCurrentWorld().addUpdate(this);
    }

    ~WorldUpdate() {
        game->getWorldManager().getCurrentWorld().delUpdate(this);
    }
};
