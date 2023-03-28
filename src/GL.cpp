#define GLAD_GL_IMPLEMENTATION
#include "GL.hpp"
#include "Constructor.hpp"
#include <pthread.h>

using namespace GL;

static const float square_vertices[] = {
    -0.5, -0.5,
     0.5, -0.5,
     0.5,  0.5,
    -0.5,  0.5
};

Instance::Instance() {
    gladLoaderLoadGL();
    
    glGenBuffers(1, &square_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, square_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &square_vao);
    glBindVertexArray(square_vao);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


Instance::~Instance() {
    gladLoaderUnloadGL();
}

// GLTask gl_task_queue[GL_TASKS_MAX_QTY]; 
// unsigned char gl_task_queue_qty;
// pthread_mutex_t gl_task_mutex = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t gl_task_cond = PTHREAD_COND_INITIALIZER;


// void gl_task_queue_runtasks() {
//     pthread_mutex_lock(&gl_task_mutex);
//     for (unsigned char i=0; i<gl_task_queue_qty; i++) {
//         GLTask* task = &gl_task_queue[i];
//         task->fn(task->arg);
//     }
//     if (gl_task_queue_qty) {
//         gl_task_queue_qty = 0;
//         pthread_cond_broadcast(&gl_task_cond); 
//     }
//     pthread_mutex_unlock(&gl_task_mutex);
// }

// void gl_task_queue_execute(void (*fn) (void*), void* arg) {
//     if (pthread_self() == main_thread) {
//         fn(arg);
//         return;
//     }
//     pthread_mutex_lock(&gl_task_mutex);
//     gl_task_queue[gl_task_queue_qty++] = (GLTask) { fn, arg };
//     pthread_cond_wait(&gl_task_cond, &gl_task_mutex);
//     pthread_mutex_unlock(&gl_task_mutex);
// }