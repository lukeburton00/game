#include <iostream>
#include <stdint.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "spdlog/spdlog.h"

#include "keycodes.hpp"
#include "mousecodes.hpp"

#ifndef NDEBUG
	#define LOGINFO(...) spdlog::info(__VA_ARGS__)
#else
	#define LOGINFO(...)
#endif

GLFWwindow *window;

namespace Input
{
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
		LOGINFO("Mouse scroll {} {}", xoffset, yoffset);
	}

}

int main(int argc, char** argv)
{
	const int WIDTH = 640;
	const int HEIGHT = 480;
	const std::string TITLE = "OpenGL";
	const glm::vec3 COLOR = glm::vec3(1.f, 0.f, 1.f);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGHT, TITLE.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	spdlog::info("OpenGL version {}", (char*)glGetString(GL_VERSION));
	spdlog::info("Graphics device: {}", (char*)glGetString(GL_RENDERER));

	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetKeyCallback(window, Input::key_callback);
	glfwSetMouseButtonCallback(window, Input::mouse_button_callback);
	glfwSetScrollCallback(window, Input::scroll_callback);

	while(!glfwWindowShouldClose(window))
	{
		if (Input::isKeyPressed(Input::KeyCode::Escape))
		{
			glfwSetWindowShouldClose(window, true);
		}

		glClearColor(COLOR.r, COLOR.g, COLOR.b, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
        glfwPollEvents();
	}

    return 0;
}