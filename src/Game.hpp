#pragma once
#include "Integers.hpp"
#include <functional>
#include <memory>

class Window;
class World;

namespace GL {
    class Shader;
}

class Game;
extern Game* game;

class Game {
    struct AssignPtr { AssignPtr(Game* g) { game = g; } } assignPtr { this };
    class GameImpl; std::unique_ptr<GameImpl> m_pimpl;

public:
    Game();
    ~Game();

    void update();
    void close();
    
    World& addWorld(World* world);

    template<typename T, typename... Ts>
    World& addWorld(Ts&&... args) {
        return addWorld(new T(std::forward<Ts>(args)...));
    }

    void delWorld(World* world);

    Window& getWindow();
    GL::Shader& getShader(const char* name);
    void forEachShader(const std::function<void(GL::Shader&)>&);
    u64 getNewId();
};
