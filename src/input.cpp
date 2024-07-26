#include "input.hpp"

namespace Input
{
    static GLFWwindow *window;

    void setWindow(GLFWwindow *win)
    {
        window = win;
    }

	bool isKeyPressed(const KeyCode& keyCode)
	{
		return glfwGetKey(window, static_cast<uint16_t>(keyCode)) == GLFW_PRESS;
	}

	bool isMouseButtonPressed(const MouseCode& mouseCode)
	{
		return glfwGetMouseButton(window, static_cast<uint16_t>(mouseCode)) == GLFW_PRESS;
	}

	glm::vec2 getMousePosition()
	{
		double x, y;
        glfwGetCursorPos(window, &x, &y);
        return glm::vec2(x, y);
	}
}
