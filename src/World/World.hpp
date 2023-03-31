#pragma once
#include "Updater.hpp"
#include "../Integers.hpp"
#include "../Game.hpp"

class WorldManager {
    class WorldManagerImpl; WorldManagerImpl* m_pimpl;
public:

    WorldManager();
    ~WorldManager();
};

struct World : Update {
    UpdateManager m_updateManager;

    void addUpdate(Update* u) {
        m_updateManager.add(u);
    }

    void delUpdate(Update* u) {
        m_updateManager.del(u);
    }

    virtual ~World();

};


struct WorldUpdate : Update {
    World& world;

    WorldUpdate(World& world) : world(world) {
        world.addUpdate(this);
    }

    ~WorldUpdate() {
        world.delUpdate(this);
    }
};
