#include "input.hpp"
#include "game.hpp"

namespace Input
{
	bool isKeyPressed(const KeyCode& keyCode)
	{
		auto* window = static_cast<GLFWwindow*>(Game::get().getWindow().getNativeWindow());
		return glfwGetKey(window, static_cast<uint16_t>(keyCode)) == GLFW_PRESS;
	}

	bool isMouseButtonPressed(const MouseCode& mouseCode)
	{
		auto* window = static_cast<GLFWwindow*>(Game::get().getWindow().getNativeWindow());
		return glfwGetMouseButton(window, static_cast<uint16_t>(mouseCode)) == GLFW_PRESS;
	}

	glm::vec2 getMousePosition()
	{
		auto* window = static_cast<GLFWwindow*>(Game::get().getWindow().getNativeWindow());
		double x, y;
        glfwGetCursorPos(window, &x, &y);
        return glm::vec2(x, y);
	}
}
