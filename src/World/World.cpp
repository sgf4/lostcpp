#include "World.hpp"
#include "../Constructor.hpp"

#include <uuid.h>
#include <memory>
#include <unordered_map>

class WorldManager::WorldManagerImpl {
    std::unordered_map<uuids::uuid, std::unique_ptr<World>> m_worlds;
    uuids::uuid m_currentWorld;

public:

    void loadWorld(World* world) {
        m_worlds[game->getNewUUID()] = std::unique_ptr<World> (world);
    }

    World& getCurrentWorld() {
        return *m_worlds[m_currentWorld];
    }
};

WorldManager::WorldManager() {}

void WorldManager::loadWorldPtr(World* world) {
    m_pimpl->loadWorld(world);
}

World& WorldManager::getCurrentWorld() {
    return m_pimpl->getCurrentWorld();
}

WorldManager::~WorldManager() {}