#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Window.hpp"
//#include "font.hpp"
//#include "updater.hpp"
#include <GLFW/glfw3.h>
#include <algorithm>

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
    int result = glfwInit();
    assert(result);
    ((void) result);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_glfw = glfwCreateWindow(w.getResolution().x, w.getResolution().y, w.getTitle(), NULL, NULL);
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

    glfwSetCursorPosCallback(m_glfwInstance, [] (GLFWwindow* wnd, double x, double y) {
        static_cast<Window*>(glfwGetWindowUserPointer(wnd))->onMouseEvent({x, y});
    });

    //window_hide_cursor();

    // Init window fbo
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_resolution.x, m_resolution.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    glBindRenderbuffer(GL_RENDERBUFFER, m_depthRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_resolution.x, m_resolution.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Default 
    glfwSwapInterval(1);

    // Input
    glfwSetKeyCallback(m_glfwInstance, [] (GLFWwindow *window, int key, int scancode, int action, int mods) {
        if (action == 2) return;
        static_cast<Window*>(glfwGetWindowUserPointer(window))->onKeyEvent(key, action);
    });

    std::fill_n(m_keys, sizeof(m_keys), KEY_STATE_RELEASED_REPEAT);
    // glfwSetMouseButtonCallback(m_glfwInstance, mouse_button_callback);
}

void Window::updateUniforms(GL::Shader& s) {
    glUseProgram(s);
    glUniform2f(s.getUniform("uwsize"), m_resolution.x, m_resolution.y);
    glUseProgram(0);
}

void Window::onResize(int w, int h) {
    m_size.x = w;
    m_size.y = h;
    
    m_offset.x = 0;
    m_offset.y = 0;

    if ((float)w / h > (float)m_resolution.x/m_resolution.y) {
        m_size.x = h*m_resolution.x/m_resolution.y;
        m_size.y = h;
        m_offset.x = (w-m_size.x)/2;
    } else {
        m_size.x = w;
        m_size.y = w*m_resolution.y/m_resolution.x;
        m_offset.y = (h-m_size.y)/2;
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
    glDisable(GL_DEPTH_TEST);

    if (getKeyDown(KEY_F11)) {
        setFullscreen(!m_fullscreen);
    }
    
    show_fps();
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //glViewport(0, 0, m_width, m_height);
    glViewport(m_offset.x, m_offset.y, m_size.x, m_size.y);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(m_glInstance.getSquareVAO());
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glUseProgram(m_fboShader);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
    glBindVertexArray(0);

    /* Swap front and back buffers */
    glfwSwapBuffers(m_glfwInstance);

    /* Poll for and process events */
    glfwPollEvents();

    glEnable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glViewport(0, 0, m_resolution.x, m_resolution.y);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);
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

Window::KeyState Window::getKeyState(Key key) const {
    return m_keys[key];
}

void Window::setKeyState(Key key, KeyState state) {
    m_keys[key] = state;
}

bool Window::getKey(Key key) const {
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

void Window::onMouseEvent(glm::vec2 pos) {
    m_mouseDirection = pos-m_mousePosition;
    m_mousePosition = pos;
}

glm::vec2 Window::getMouseDir() {
    auto dir = m_mouseDirection;
    m_mouseDirection = {0, 0};
    return dir;
}