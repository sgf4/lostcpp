#include "World.hpp"
#include "Entity.hpp"
#include "Component/Component.hpp"

World::World() {
    m_componentManager = std::make_unique<ComponentManager>();
    m_entities.reserve(100);
}


void World::updateWorld() {
    current = this;
    m_time.update();
}

Entity& World::addEntity() {
    return m_entities.emplace_back();
}

Entity& World::getEntity(u32 id) {
    return m_entities[id];
}

void World::updateUniforms(GL::Shader& s) {
    glUseProgram(s);
    glUniform1f(s.getUniform("utime"), m_time.getElapsed());
    glUseProgram(0);
}


World::~World() {
    
}