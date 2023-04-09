#include "Game.hpp"
#include "Window.hpp"
#include "Updater.hpp"
#include "World/World.hpp"
#include "Constructor.hpp"

#define UUID_SYSTEM_GENERATOR
#include <uuid.h>

Game* game;

class Game::GameImpl {
    friend Game;
    UpdateManager m_updateManager;
    Window m_window;
    WorldManager m_worldManager;
    uuids::uuid_system_generator m_uuidGenerator;

public:
    GameImpl() {
        m_updateManager.add(&m_window);
    }

    void start() {
        while (!m_window.shouldClose()) {
            m_updateManager.update();
        }
    }

    void close() {
        m_window.shouldClose();
    }

    uuids::uuid getNewUUID() {
        return m_uuidGenerator();
    }
};

Game::Game() {
    game = this;
}

void Game::start() {
    m_pimpl->start();
}

void Game::close() {
    m_pimpl->close();
}

uuids::uuid Game::getNewUUID() {
    return m_pimpl->getNewUUID();
}

UpdateManager& Game::getUpdateManager() {
    return m_pimpl->m_updateManager;
}

Window& Game::getWindow() {
    return m_pimpl->m_window;
}

WorldManager& Game::getWorldManager() {
    return m_pimpl->m_worldManager;
}

Game::~Game() {
}