#pragma once

#include <glm/glm.hpp>

#include "keycodes.hpp"
#include "mousecodes.hpp"

namespace Input
{
    bool isKeyPressed(const KeyCode& keyCode);
    bool isMouseButtonPressed(const MouseCode& mouseCode);
    glm::vec2 getMousePosition();
}
