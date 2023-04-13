#include "Window.hpp"
#include "Game.hpp"

#include "World/ExampleWorld.hpp"
#include "Embed.hpp"

#include "World/World.hpp"
#include "Embed.hpp"

int main() {
    Game game;
    game.getWorldManager().loadWorld<ExampleWorld>();
    game.start();
    return 0;
}