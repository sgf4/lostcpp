#include "World.hpp"
#include "../Constructor.hpp"
#include "../UUID.hpp"

#include <unordered_map>

class WorldManager::WorldManagerImpl {
    std::unordered_map<UUIDv4::UUID, std::unique_ptr<World>> world_storage;
};

WorldManager::WorldManager() {
    m_pimpl = new WorldManagerImpl();
}

WorldManager::~WorldManager() {
    delete m_pimpl;
}