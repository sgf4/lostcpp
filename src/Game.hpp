#pragma once
#include "Pimpl.hpp"

class Window;
class UpdateManager;
class WorldManager;

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
};

extern Game* game;