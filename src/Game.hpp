#pragma once
#include "Pimpl.hpp"

class Window;
class UpdateManager;
class WorldManager;

namespace GL {
    class Shader;
}

class Game {
    PIMPL(Game);

public:
    Game();
    ~Game();

    void start();
    void close();

    UpdateManager& getUpdateManager();
    Window& getWindow();
    WorldManager& getWorldManager();
    GL::Shader& getShader(const char* name);
    u64 getNewId();
};

extern Game* game;