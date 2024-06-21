#pragma once

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "log.hpp"
#include "keycodes.hpp"
#include "mousecodes.hpp"

namespace Input
{
    void init(GLFWwindow* win);
    bool isKeyPressed(const KeyCode& keyCode);
    bool isMouseButtonPressed(const MouseCode& mouseCode);
    glm::vec2 getMousePosition();
}