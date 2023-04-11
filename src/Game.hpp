#pragma once
#include "Pimpl.hpp"

class Window;
class UpdateManager;
class WorldManager;

namespace GL {
    class Shader;
}

namespace uuids {
    class uuid;
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
    uuids::uuid getNewUUID();
    GL::Shader& getShader(const char* name);
};

extern Game* game;