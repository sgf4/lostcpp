#pragma once
#include "Updater.hpp"
#include "GL.hpp"
#include "Integers.hpp"

#define RESOLUTION_WIDTH (640)
#define RESOLUTION_HEIGHT (480)

#define ASPECT_RATIO_Y ((float) RESOLUTION_WIDTH/RESOLUTION_HEIGHT)
#define ASPECT_RATIO_X ((float) RESOLUTION_HEIGHT/RESOLUTION_WIDTH)

struct GLFWwindow;
extern "C" int glfwWindowShouldClose(GLFWwindow*);

class Window;

struct GLFWInstance {
    GLFWwindow* m_glfw;

    operator GLFWwindow*() {
        return m_glfw;
    }

    GLFWInstance(Window& w);
    ~GLFWInstance();
};

class Window : public Update {
    int m_width {640}, m_height {480}, m_offsetX {}, m_offsetY {};
    const char* m_title {"omg"};
    bool m_vsync {true}, m_fullscreen {false}, m_cursorIshiden {false};

    GLFWInstance m_glfwInstance {*this};
    GL::Instance m_glInstance;
    GL::FBO m_fbo;
    GL::Texture m_texture;

    enum KeyState : u8 {
        KEY_STATE_RELEASED,
        KEY_STATE_RELEASED_REPEAT,
        KEY_STATE_DOWN,
        KEY_STATE_DOWN_REPEAT,
    };

    #include "Keycodes.hpp"

    KeyState m_keys[512];

public:
    Window();
    void update();
    void close();
    void hideCursor();
    void unhideCursor();
    void setFullscreen(bool);
    void setVsync(bool);
    void onResize(int w, int h);
    
    bool shouldClose() { return glfwWindowShouldClose(m_glfwInstance); }
    GLFWInstance& getGlfwInstance() { return m_glfwInstance; }
    auto getWidth() const { return m_width; }
    auto getHeight() const { return m_height; }
    auto getTitle() const { return m_title; }

    void onKeyEvent(u32 key, bool pressed);
    KeyState getKeyState(Key key);
    void setKeyState(Key key, KeyState value);
    bool getKey(Key key);
    bool getKeyDown(Key key);
    bool getKeyReleased(Key key);

};