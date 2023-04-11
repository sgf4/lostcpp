#pragma once
#include "Integers.hpp"
#include "Glad.hpp"

// void gl_task_queue_runtasks(void);
// void gl_task_queue_execute(void (*fn) (void*), void* arg);

namespace GL {

struct ID {
    u32 m_id;
    ID(u32 id = 0) : m_id(id) {}

    operator u32() const {
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

class Instance {
    struct I { 
        I() {
            gladLoaderLoadGL();
        }
        ~I() {
            gladLoaderUnloadGL();
        }
    } m_loader;
    VAO m_squareVAO;
    VBO m_squareVBO;

public:

    u32 getSquareVAO() const {
        return m_squareVAO;
    }

    Instance();
    ~Instance();
};

inline Instance* instance;

}