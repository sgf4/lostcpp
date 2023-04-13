#pragma once

#include <unordered_set>
#include "Game.hpp"

struct Update {
    virtual void update() = 0;
};

class UpdateManager {
    std::unordered_set<Update*> m_fns;
public:

    void add(Update& u) {
        m_fns.insert(&u);
    }

    void del(Update& u) {
        m_fns.erase(&u);
    }

    void update() {
        for (auto& fn : m_fns) {
            fn->update();
        }
    }
};
