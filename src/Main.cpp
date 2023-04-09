#include <stdio.h>
#include "Window.hpp"
#include "Game.hpp"
#include <uuid.h>

#include "World/ExampleWorld.hpp"
#include "Embed.hpp"

#include "World/World.hpp"

int main() {
    Game game;
    game.getWorldManager().loadWorld<ExampleWorld>();
    game.start();
    return 0;
}