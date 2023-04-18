#pragma once
#include "Integers.hpp"

class Window;
class World;

namespace GL {
    class Shader;
}

class Game {
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
    u64 getNewId();
};

extern Game* game;