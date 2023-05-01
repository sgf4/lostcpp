#include "World.hpp"
#include "Entity.hpp"
#include "Component/Component.hpp"

World::World() {
    m_componentManager = std::make_unique<ComponentManager>();
    m_entities.reserve(100);

    current = this;
    // Basic components
    m_componentManager->load<Transform>();
    m_componentManager->load<Transform2D>();
    m_componentManager->load<Camera>();

    camera = &addEntity();
    camera->addComponent<Camera>();
}


void World::updateWorld() {
    current = this;
    m_componentManager->update();
    time.update();
}

Entity& World::addEntity() {
    Entity& e = m_entities.emplace_back();
    e.id = m_entities.size()-1;
    return e;
}

Entity& World::getEntity(u32 id) {
    return m_entities[id];
}

void World::delEntity(u32 id) {
    Entity& e = m_entities[id];
    e.destroy();
    e = std::move(*--m_entities.end());
    m_entities.pop_back();

    if (id != m_entities.size()) e.updateId(id);
}

void World::updateUniforms(GL::Shader& s) {
    glUseProgram(s);
    glUniform1f(s.getUniform("utime"), time.elapsed);
    glUseProgram(0);
}


World::~World() {
    
}