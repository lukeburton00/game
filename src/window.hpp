#pragma once

#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

struct WindowProperties
{
    WindowProperties() = default;
    WindowProperties(const uint32_t& width, const uint32_t& height, const std::string& title)
        : width(width), height(height), title(title){}

    uint32_t width, height;
    std::string title;
};

class Window
{
public:
    Window() = default;
    Window(const uint32_t& width, const uint32_t& height, const std::string& title);
    ~Window();

    bool init();
    void clear(const glm::vec3& color) const;
    void swapBuffers() const;

    int getWidth();
    int getHeight();
    GLFWwindow* getNativeWindow() const;

private:

private:
    GLFWwindow* m_Window = nullptr;
    WindowProperties m_WindowProperties;
};
