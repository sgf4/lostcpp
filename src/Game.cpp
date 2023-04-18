#include "Game.hpp"
#include "GL.hpp"
#include "Window.hpp"
#include "World/World.hpp"
#include "Constructor.hpp"

#include <memory>
#include <unordered_set>

Game* game;

class Game::GameImpl {
    friend Game;
    Window m_window;
    Time m_time;
    std::unordered_map<std::string, GL::Shader> m_shaderStorage;
    std::unordered_set<World*> m_worlds; 

public:
    GameImpl() {
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

    void update() {
        while (!m_window.shouldClose()) {
            m_window.update();
            m_time.update();
            
            // Update worlds
            for (World* world : m_worlds) {
                World::current = world;
                world->update();
            }
        }
    }

    void addWorld(World* world) {
        m_worlds.insert(world);
    }

    void delWorld(World* world) {
        m_worlds.erase(world);
        delete world;
    }

    void close() {
        m_window.shouldClose();
    }

    u64 getNewId() {
        static u64 id {};
        return id++;
    }

    ~GameImpl() {
        for (World* world : m_worlds) {
            delete world;
        }
    }
};

Game::Game() : m_pimpl(std::make_unique<GameImpl>()) {
    game = this;
}

void Game::update() {
    m_pimpl->update();
}

void Game::close() {
    m_pimpl->close();
}

u64 Game::getNewId() {
    return m_pimpl->getNewId();
}

Window& Game::getWindow() {
    return m_pimpl->m_window;
}

World& Game::addWorld(World* world) {
    m_pimpl->addWorld(world);
    return *world;
}

void Game::delWorld(World* world) {
    m_pimpl->delWorld(world);
}

GL::Shader& Game::getShader(const char* name) {
    return m_pimpl->getShader(name);
}

Game::~Game() {
}