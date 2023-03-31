#pragma once
#include <tuple>
#include <memory>
#include "Meta.hpp"

class Window;
class UpdateManager;
class WorldManager;

class Game {
    class GameImpl; std::unique_ptr<GameImpl> m_pimpl;

public:
    Game();
    ~Game();

    void start();
    void close();

    UpdateManager& getUpdateManager();
    Window& getWindow();
    WorldManager& getWorldManager();
    
};
