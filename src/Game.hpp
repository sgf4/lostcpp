#pragma once
#include "Pimpl.hpp"
#include "Integers.hpp"

class Window;
class World;

namespace GL {
    class Shader;
}

class Game {
    PIMPL(Game);

public:
    Game();
    ~Game();

    void update();
    void close();
    
    void addWorld(World* world);
    void delWorld(World* world);

    Window& getWindow();
    GL::Shader& getShader(const char* name);
    u64 getNewId();
};

extern Game* game;