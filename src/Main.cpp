#include "Window.hpp"
#include "Game.hpp"

#include "World/ExampleWorld.hpp"
#include "Embed.hpp"

#include "World/World.hpp"
#include "Embed.hpp"

int main() {
    Game game;
    game.addWorld<ExampleWorld>();
    game.update();
    return 0;
}