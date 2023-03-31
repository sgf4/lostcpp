#pragma once
#include "Updater.hpp"
#include "../Integers.hpp"
#include "../Game.hpp"

#include <memory>
#include <unordered_map>


struct World;

// namespace UUIDv4 {
//     struct UUID;
// }

//struct WorldStorage;

class WorldManager {
    World* current_world;
    //std::unique_ptr<WorldStorage> storage;
    // std::unordered_map<UUIDv4::UUID, std::unique_ptr<World>> world_storage;
public:

    template<typename T>
    void load() {
        auto world = std::make_unique<T>();

    }

    void save() {

    }

    template<typename T>
    void loadSaved() {

    }

    World& getCurrentWorld() {
        return *current_world;
    }
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
