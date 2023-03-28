#include "Updater.hpp"
#include "Window.hpp"
#include "Constructor.hpp"


void UpdateManager::update() {
    for (auto& fn : m_fns) {
        fn->update();
    }
}
