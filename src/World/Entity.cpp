#include "Entity.hpp"


void Entity::updateId(u32 i) {
    id = i;
    if (auto ref = m_ref.lock()) *ref = i;
    WORLD.getComponentManager().updateIds(*this);
}

std::shared_ptr<u32> Entity::ref() {
    if (m_ref.expired()) {
        auto ref = std::make_shared<u32>(id);
        m_ref = ref;
        return ref;
    }
    return m_ref.lock();
}