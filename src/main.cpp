#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "log.hpp"
#include "input.hpp"

GLFWwindow *window;

int main(int argc, char** argv)
{
	const int WIDTH = 640;
	const int HEIGHT = 480;
	const std::string TITLE = "OpenGL";
	const glm::vec3 COLOR = glm::vec3(1.f, 0.f, 1.f);

	if (!glfwInit())
	{
		LOGCRITICAL("Failed to initialize GLFW.");
        return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!(window = glfwCreateWindow(WIDTH, HEIGHT, TITLE.c_str(), nullptr, nullptr)))
	{
		LOGCRITICAL("Failed to create GLFW window.");
        glfwTerminate();
        return -1;
	}

	Input::init(window);

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	LOGINFO("OpenGL version {}", (char*)glGetString(GL_VERSION));
	LOGINFO("Graphics device: {}", (char*)glGetString(GL_RENDERER));

	glViewport(0, 0, WIDTH, HEIGHT);

	while(!glfwWindowShouldClose(window))
	{
		if (Input::isKeyPressed(Input::KeyCode::Escape))
		{
			glfwSetWindowShouldClose(window, true);
		}

		// update here 

		glClearColor(COLOR.r, COLOR.g, COLOR.b, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

		// render here

		glfwSwapBuffers(window);
        glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}