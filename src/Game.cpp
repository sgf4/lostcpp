#include "Game.hpp"
#include "Window.hpp"
#include "Updater.hpp"
#include "World/World.hpp"
#include "Constructor.hpp"

class Game::GameImpl {
    friend Game;
    UpdateManager updateManager;
    Window window;
    WorldManager worldManager;

public:
    GameImpl() {
        updateManager.add(&window);
    }

    void start() {
        while (!window.shouldClose()) {
            updateManager.update();
        }
    }

    void close() {
        window.shouldClose();
    }
};

Game::Game() {
    m_pimpl = new GameImpl();
}

void Game::start() {
    m_pimpl->start();
}

void Game::close() {
    m_pimpl->close();
}


UpdateManager& Game::getUpdateManager() {
    return m_pimpl->updateManager;
}

Window& Game::getWindow() {
    return m_pimpl->window;
}

WorldManager& Game::getWorldManager() {
    return m_pimpl->worldManager;
}

Game::~Game() {
    delete m_pimpl;
}