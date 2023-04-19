#include "World.hpp"

World::World() : m_id(game->getNewId()), m_camera(true) {
    current = this;
    WINDOW.hideCursor();
    m_entities.reserve(100);
}

void World::update() {
    m_time.update();
    m_camera.update();
    for (Entity* entity : m_entities) {
        Entity::current = entity;
        try {
            entity->update();
        } catch(std::string err) {
            std::cerr << "ERROR: " << err << std::endl;
        }
    }
}

void World::updateUniforms(GL::Shader& s) {
    glUseProgram(s);
    glUniform1f(s.getUniform("utime"), m_time.getElapsed());
    glUseProgram(0);
}

Entity& World::addEntity(Entity* e) {
    m_entities.insert(e);
    return *e;
}

void World::delEntity(Entity* e) {
    m_entities.erase(e);
}

World::~World() {
    for (Entity* e : m_entities) {
        delete e;
    }
}