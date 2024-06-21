#include "input.hpp"

namespace Input 
{
    static GLFWwindow *window;

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
			LOGINFO("Key {} pressed with mods {}", scancode, mods);
		if (action == GLFW_RELEASE)
			LOGINFO("Key {} released with mods {}", scancode, mods);
		if (action == GLFW_REPEAT)
		    LOGINFO("Key {} repeated with mods {}", scancode, mods);
	}

	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS)
			LOGINFO("Mouse button {} pressed with mods {}", button, mods);
		if (action == GLFW_RELEASE)
			LOGINFO("Mouse button {} released with mods {}", button, mods);
		if (action == GLFW_REPEAT)
		    LOGINFO("Mouse button {} repeated with mods {}", button, mods);
	}

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		LOGINFO("Mouse scroll X: {} Y: {}", xoffset, yoffset);
	}

    void init(GLFWwindow *win)
    {
        window = win;
        glfwSetKeyCallback(window, key_callback);
	    glfwSetMouseButtonCallback(window, mouse_button_callback);
	    glfwSetScrollCallback(window, scroll_callback);
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