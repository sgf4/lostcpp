#pragma once
#include "Game.hpp"
#include "GL.hpp"
#include "Keycodes.hpp"
#include "Integers.hpp"
#include <glm/vec2.hpp>

#define WINDOW game->getWindow()
#define WINDOW_RX WINDOW.getResolution().x
#define WINDOW_RY WINDOW.getResolution().y

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

class Window {
    glm::uvec2 m_resolution {640, 480}, m_offset, m_size;

    const char* m_title {"omg"};
    bool m_vsync {true}, m_fullscreen {false}, m_cursorIshiden {false};
    
    glm::vec2 m_mouseDirection {}, m_mousePosition {};

    GLFWInstance m_glfwInstance {*this};
    GL::Instance m_glInstance;
    GL::EmbedShader<"main_fbo"> m_fboShader;
    GL::FBO m_fbo;
    GL::RBO m_depthRBO;
    GL::Texture m_texture;

    enum KeyState : u8 {
        KEY_STATE_RELEASED,
        KEY_STATE_RELEASED_REPEAT,
        KEY_STATE_DOWN,
        KEY_STATE_DOWN_REPEAT,
    };

    KeyState m_keys[512];

    void onKeyEvent(u32 key, bool pressed);
    void onMouseEvent(glm::vec2 pos);

public:
    Window();
    void update();
    void close();
    void hideCursor();
    void unhideCursor();
    void setFullscreen(bool);
    void setVsync(bool);
    void onResize(int w, int h);
    
    void updateUniforms(GL::Shader& s);
    bool shouldClose() { return glfwWindowShouldClose(m_glfwInstance); }
    GLFWInstance& getGlfwInstance() { return m_glfwInstance; }
    auto getSize() const { return m_size; }
    auto getResolution() const { return m_resolution; }
    auto getTitle() const { return m_title; }

    float getResolutionRatio() {
        return (float)m_resolution.x/m_resolution.y;
    }

    KeyState getKeyState(Key key) const;
    void setKeyState(Key key, KeyState value);
    bool getKey(Key key) const;
    bool getKeyDown(Key key);
    bool getKeyReleased(Key key);
    glm::vec2 getMouseDir();
};