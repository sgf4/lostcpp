#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Constructor.hpp"
#include "Window.hpp"
//#include "font.hpp"
#include "GL.hpp"
//#include "updater.hpp"
#include <GLFW/glfw3.h>

//#include "time.hpp"
//#include "text.hpp"

static void show_fps() {
    // text_push_alignment()
    // text_push_color()
    // text_push_size()

    // text_align(TEXT_UPPER_LEFT)

    // text_size(0.25)

    // text_color_rgb(0, 255, 0)
    // text_render_shadow_fmt(TEXT(main, fps), c_time->fps)
    
    // text_pop_size()
    // text_pop_color()
    // text_pop_alignment()
}

GLFWInstance::GLFWInstance(Window& w) {
    assert(glfwInit());

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_glfw = glfwCreateWindow(w.getWidth(), w.getHeight(), w.getTitle(), NULL, NULL);
    assert(m_glfw);

    glfwMakeContextCurrent(m_glfw);
    
}

GLFWInstance::~GLFWInstance() {
    glfwDestroyWindow(m_glfw);
    glfwTerminate();
}

Window::Window() {
    
    glfwSetWindowUserPointer(m_glfwInstance, (void*) this);

    glfwSetWindowSizeCallback(m_glfwInstance, [] (GLFWwindow* wnd, int w, int h) {
        static_cast<Window*>(glfwGetWindowUserPointer(wnd))->onResize(w, h);
    });

    //window_hide_cursor();

    // Init window fbo
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Default 
    glfwSwapInterval(0);


    // Input
    glfwSetKeyCallback(m_glfwInstance, [] (GLFWwindow *window, int key, int scancode, int action, int mods) {
        if (action == 2) return;
        static_cast<Window*>(glfwGetWindowUserPointer(window))->onKeyEvent(key, action);
    });

    // glfwSetMouseButtonCallback(m_glfwInstance, mouse_button_callback);
}

void Window::onResize(int w, int h) {
    m_width = w;
    m_height = h;
    
    m_offsetX = 0;
    m_offsetY = 0;

    if ((float)w / h > ASPECT_RATIO_Y) {
        m_width = h*ASPECT_RATIO_Y;
        m_height = h;
        m_offsetX = (w-m_width)/2;
    } else {
        m_width = w;
        m_height = w*ASPECT_RATIO_X;
        m_offsetY = (h-m_height)/2;
    }
}


void Window::setFullscreen(bool v) {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    static int lastpos[] = {0, 0};
    static int lastsize[] = {0, 0};
    if (v) {
        glfwGetWindowPos(m_glfwInstance, &lastpos[0], &lastpos[1]);
        glfwGetWindowSize(m_glfwInstance, &lastsize[0], &lastsize[1]);
        glfwSetWindowMonitor(m_glfwInstance, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    } else {
        glfwSetWindowMonitor(m_glfwInstance, NULL, lastpos[0], lastpos[1], lastsize[0], lastsize[1], mode->refreshRate);
    }
    m_fullscreen = v;
}

void Window::setVsync(bool v) {
    glfwSwapInterval(v);
    m_vsync = v;
}


void Window::update() {
    /* Render here */
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glViewport(0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //glViewport(0, 0, window_width, window_height);
    if (getKeyDown(KEY_F11)) {
        setFullscreen(!m_fullscreen);
    }
    
    show_fps();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(m_offsetX, m_offsetY, m_width, m_height);
    
    //glClearColor(1.0, 1.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // glBindVertexArray(square_vao);
    // glBindTexture(GL_TEXTURE_2D, texture);
    // glUseProgram(PROGRAM(ui_image));
    // glUniform4f(UNIFORM(ui_image, ucolor), 1, 1, 1, 1);
    // glUniform2f(UNIFORM(ui_image, uoffset), 0, 0);
    // glUniform2f(UNIFORM(ui_image, usize), 1, -1);
    // glUniform2f(UNIFORM(ui_image, utex_offset), 0, 0);
    // glUniform2f(UNIFORM(ui_image, utex_size), 1, 1);
    // glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    // glBindTexture(GL_TEXTURE_2D, 0);
    // glBindVertexArray(0);

    /* Swap front and back buffers */
    glfwSwapBuffers(m_glfwInstance);

    /* Poll for and process events */
    glfwPollEvents();


//    glfwTerminate();
}

void Window::hideCursor() {
    glfwSetInputMode(m_glfwInstance, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glfwSetCursorPos(window_glfw, window_width/2.f, window_height/2.f);
    m_cursorIshiden = true;   
}

void Window::unhideCursor() {
    glfwSetInputMode(m_glfwInstance, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    m_cursorIshiden = false;
}

void Window::close() {
    glfwSetWindowShouldClose(m_glfwInstance, 1);
}

// Input
void Window::onKeyEvent(u32 key, bool pressed) {
    if (key >= sizeof(m_keys)) return;
    setKeyState(static_cast<Key>(key), pressed ? KEY_STATE_DOWN : KEY_STATE_RELEASED);
}

u8 Window::getKeyState(Key key) {
    return m_keys[key];
}

void Window::setKeyState(Key key, KeyState state) {
    m_keys[key] = state;
}

bool Window::getKey(Key key) {
    auto state = getKeyState(key);
    return state == KEY_STATE_DOWN || state == KEY_STATE_DOWN_REPEAT;
}

bool Window::getKeyDown(Key key) {
    auto state = getKeyState(key);
    bool pressed = state == KEY_STATE_DOWN;
    if (pressed) setKeyState(key, KEY_STATE_DOWN_REPEAT);
    return pressed;
}

bool Window::getKeyReleased(Key key) {
    auto state = getKeyState(key);
    bool released = state == KEY_STATE_RELEASED;
    if (released) setKeyState(key, KEY_STATE_RELEASED_REPEAT);
    return released;
}
