#pragma once
#include "Updater.hpp"
#include "../Integers.hpp"
#include "../Game.hpp"

class World;

class WorldManager {
    class WorldManagerImpl; WorldManagerImpl* m_pimpl;

    void loadWorldPtr(World* world);
public:

    WorldManager();
    ~WorldManager();

    template<typename T>
    void loadWorld() {
        loadWorldPtr(new T());
    }

    World& getCurrentWorld();
};

class World : public Update {
    UpdateManager m_updateManager;

public:
    void addUpdate(Update* u) {
        m_updateManager.add(u);
    }

    void delUpdate(Update* u) {
        m_updateManager.del(u);
    }

    virtual ~World();

};


struct WorldUpdate : Update {
    WorldUpdate() {
        game->getWorldManager().getCurrentWorld().addUpdate(this);
    }

    ~WorldUpdate() {
        game->getWorldManager().getCurrentWorld().delUpdate(this);
    }
};
