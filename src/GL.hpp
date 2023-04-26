#pragma once
#include "Integers.hpp"
#include "Glad.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

// void gl_task_queue_runtasks(void);
// void gl_task_queue_execute(void (*fn) (void*), void* arg);

namespace GL {

struct ID {
    u32 id;
    ID(u32 id = 0) : id(id) {}

    operator u32() const {
        return id;
    }

    auto operator&() {
        return &id;
    }
};

struct VAO : ID {
    using ID::ID;

    VAO() {
        glGenVertexArrays(1, &id);
    }

    ~VAO() {
        glDeleteVertexArrays(1, &id);
    }
};

struct VBO : ID {
    using ID::ID;

    VBO() {
        glGenBuffers(1, &id);
    }

    ~VBO() {
        glDeleteBuffers(1, &id);
    }
};

struct FBO : ID {
    using ID::ID;

    FBO() {
        glGenFramebuffers(1, &id);
    }

    ~FBO() {
        glDeleteFramebuffers(1, &id);
    }
};

struct RBO : ID {
    using ID::ID;

    RBO() {
        glGenRenderbuffers(1, &id);
    }

    ~RBO() {
        glDeleteRenderbuffers(1, &id);
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