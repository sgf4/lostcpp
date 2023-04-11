#pragma once
#include "../Updater.hpp"
#include "../Integers.hpp"
#include "../Game.hpp"
#include "../Pimpl.hpp"
#include "../uuid.hpp"

#include <memory>
#include <unordered_map>

class World;

class WorldManager {
    std::unordered_map<uuids::uuid, std::unique_ptr<World>> m_worlds;
    World* m_currentWorld;


public:
    void loadWorldPtr(World* world) {
        m_currentWorld = world;
        m_worlds[game->getNewUUID()] = std::unique_ptr<World> (world);
    }

    template<typename T>
    void loadWorld() {
        loadWorldPtr(new T());
    }

    World& getCurrentWorld() {
        return *m_currentWorld;
    }
};

class World : public Update {
    UpdateManager m_updateManager;
    
public:

    inline static World* current;

    World() {
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

    virtual ~World() {
        game->getUpdateManager().del(this);
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
