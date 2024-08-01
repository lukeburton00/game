#pragma once

#include <memory>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "event.hpp"

struct WindowProperties
{
    uint32_t width, height;
    std::string title;
    EventCallback eventCallback;
};

class Window
{
public:
    Window() = default;
    Window(const WindowProperties& properties);
    ~Window();

    bool init();
    void clear(const glm::vec3& color) const;
    void swapBuffers() const;

    void setFullScreen(bool shouldEnable);
    void setVSync(bool shouldEnable);

    uint32_t getWidth() const;
    uint32_t getHeight() const;
    GLFWwindow* getNativeWindow() const;
    void setEventCallback(EventCallback callback);

private:
    void setGLFWCallbacks();
    void setWindowHints();

private:
    bool m_isFullScreen;
    bool m_isVSync;

    GLFWwindow* m_Window = nullptr;
    WindowProperties m_properties;
};
