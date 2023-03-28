#include "Game.hpp"
#include "Window.hpp"
#include "Updater.hpp"
#include "World/World.hpp"
#include "Constructor.hpp"

Game* game;

Game::Game() {
    game = this;
    m_modules.init();

    Window& window = game->getModule<Window>();
    while (!window.shouldClose()) {
        window.update();
    }
    delete this;
}

void close() {
    Window& window = game->getModule<Window>();
    window.shouldClose();
}

Game::~Game() {

}