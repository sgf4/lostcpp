#pragma once

class Window;
class UpdateManager;
class WorldManager;

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
    
};
