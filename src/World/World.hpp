#pragma once
#include "Updater.hpp"
#include "../Integers.hpp"
#include "../Game.hpp"
#include "Pimpl.hpp"

class World;

class WorldManager {
    PIMPL(WorldManager);

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

    World() {
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
