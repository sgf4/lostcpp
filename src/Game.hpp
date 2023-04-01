#pragma once

class Window;
class UpdateManager;
class WorldManager;

namespace uuids {
    class uuid;
}

class Game {
    class GameImpl; GameImpl* m_pimpl;

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