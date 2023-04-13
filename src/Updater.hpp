#pragma once

#include <list>
#include "Game.hpp"

struct Update {
    std::list<Update*>::iterator m_it;
    virtual void update() = 0;
};

class UpdateManager {
    std::list<Update*> m_fns;
public:

    void add(Update* u) {
        m_fns.push_back(u);
        u->m_it = std::prev(m_fns.end());
    }

    void del(Update* u) {
        m_fns.erase(u->m_it);
    }

    void update() {
        for (auto& fn : m_fns) {
            fn->update();
        }
    }
};
