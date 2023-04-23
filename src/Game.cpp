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
        loadShaderFromEmbed<"box">();
        loadShaderFromEmbed<"texture">();
        loadShaderFromEmbed<"texture3d", "texture">();
    }

    template<FixedString str1, FixedString str2 = str1, FixedString name = str1>
    GL::Shader& loadShaderFromEmbed() {
        return m_shaderStorage.emplace(std::string(name), GL::EmbedShader<str1, str2>()).first->second;
    }

    GL::Shader& getShader(const char* name) {
        return m_shaderStorage.at(name);
    }

    void forEachShader(const std::function<void(GL::Shader&)>& fn) {
        for (auto& [name, shader] : m_shaderStorage) {
            fn(shader);
        }
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

void Game::forEachShader(const std::function<void(GL::Shader&)>& fn) {
    m_pimpl->forEachShader(fn);
}

Game::~Game() {
}