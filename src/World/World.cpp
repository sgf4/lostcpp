#include "World.hpp"



World::World() : m_id(game->getNewId()), m_camera(true) {
    current = this;
    WINDOW.hideCursor();
    m_entities.reserve(100);
}

void World::update() {
    m_time.update();
    m_camera.update();
    for (auto& entity : m_entities) {
        entity->update();
    }
}

void World::addEntity(Entity* e) {
    m_entities.insert(e);
}

void World::delEntity(Entity* e) {
    m_entities.erase(e);
}


World::~World() {
    for (Entity* e : m_entities) {
        delete e;
    }
}