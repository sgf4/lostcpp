#pragma once
#include "Integers.hpp"
#include "Glad.hpp"

#define GL_PRIORITY 103



// void gl_task_queue_runtasks(void);
// void gl_task_queue_execute(void (*fn) (void*), void* arg);

namespace GL {

struct ID {
    u32 m_id;
    ID(u32 id = 0) : m_id(id) {}

    operator u32() {
        return m_id;
    }

    auto operator&() {
        return &m_id;
    }
};

struct VAO : ID {
    using ID::ID;

    VAO() {
        glGenVertexArrays(1, &m_id);
    }

    ~VAO() {
        glDeleteVertexArrays(1, &m_id);
    }
};

struct VBO : ID {
    using ID::ID;

    VBO() {
        glGenBuffers(1, &m_id);
    }

    ~VBO() {
        glDeleteBuffers(1, &m_id);
    }
};

struct FBO : ID {
    using ID::ID;

    FBO() {
        glGenFramebuffers(1, &m_id);
    }

    ~FBO() {
        glDeleteFramebuffers(1, &m_id);
    }
};

struct Texture : ID {
    using ID::ID;

    Texture() {
        glGenTextures(1, &m_id);
    }
    
    ~Texture() {
        glDeleteTextures(1, &m_id);
    }
};

struct Instance {
    VAO square_vao {0};
    VBO square_vbo {0};
    Instance();
    ~Instance();
};

}