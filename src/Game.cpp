#include "Game.hpp"
#include "Shader.hpp"
#include "Window.hpp"
#include "Updater.hpp"
#include "World/World.hpp"
#include "Constructor.hpp"

Game* game;

class Game::GameImpl {
    friend Game;
    UpdateManager m_updateManager;
    Window m_window;
    WorldManager m_worldManager;
    std::unordered_map<std::string, GL::Shader> m_shaderStorage;

public:
    GameImpl() {
        m_updateManager.add(&m_window);

        // Global shaders
        loadShaderFromEmbed<"ui_box">();
        loadShaderFromEmbed<"ui_image">();
    }

    template<FixedString str>
    GL::Shader& loadShaderFromEmbed() {
        return m_shaderStorage.emplace(std::string(str), GL::EmbedShader<str>()).first->second;
    }

    GL::Shader& getShader(const char* name) {
        return m_shaderStorage.at(name);
    }

    void start() {
        while (!m_window.shouldClose()) {
            m_updateManager.update();
        }
    }

    void close() {
        m_window.shouldClose();
    }

    u64 getNewId() {
        static u64 id {};
        return id++;
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

u64 Game::getNewId() {
    return m_pimpl->getNewId();
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

GL::Shader& Game::getShader(const char* name) {
    return m_pimpl->getShader(name);
}

Game::~Game() {
}