#include "Window.hpp"
#include "Game.hpp"

#include "World/ExampleWorld.hpp"
#include <Embed/Embed.hpp>

int main() {
    Game game;
    game.addWorld<ExampleWorld>();
    game.update();
    return 0;
}