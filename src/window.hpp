#pragma once

#include <memory>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "event_bus.hpp"

struct WindowProperties
{
    uint32_t width, height;
    std::string title;
};

class Window
{
public:
    Window() = default;
    Window(const WindowProperties& properties);
    ~Window();

    bool init(std::shared_ptr<EventBus> eventBus);
    void clear(const glm::vec3& color) const;
    void swapBuffers() const;

    void setFullScreen(bool shouldEnable);
    void setVSync(bool shouldEnable);

    uint32_t getWidth() const;
    uint32_t getHeight() const;
    GLFWwindow* getNativeWindow() const;

private:
    void setWindowHints();
    void setEventCallbacks();

private:
    bool m_isFullScreen;
    bool m_isVSync;

    GLFWwindow* m_Window = nullptr;
    WindowProperties m_WindowProperties;
    std::shared_ptr<EventBus> m_EventBus;
};
