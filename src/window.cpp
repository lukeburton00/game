#include "window.hpp"

#include "log.hpp"

Window::Window(const uint32_t& width, const uint32_t& height, const std::string& title)
{
    m_WindowProperties = WindowProperties(width, height, title);
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

bool Window::init()
{
	if (!glfwInit())
	{
		LOGCRITICAL("Failed to initialize GLFW.");
        return false;
	}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!(m_Window = glfwCreateWindow(m_WindowProperties.width, m_WindowProperties.height, m_WindowProperties.title.c_str(), nullptr, nullptr)))
	{
		LOGCRITICAL("Failed to create GLFW window.");
        glfwTerminate();
        return false;
	}

    glfwMakeContextCurrent(m_Window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	LOGINFO("OpenGL version {}", (char*)glGetString(GL_VERSION));
	LOGINFO("Graphics device: {}", (char*)glGetString(GL_RENDERER));

	glViewport(0, 0, m_WindowProperties.width, m_WindowProperties.height);

    return true;
}

void Window::clear(const glm::vec3& color) const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(color.x, color.y, color.z, 1.0f);
}

void Window::swapBuffers() const
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

GLFWwindow* Window::getNativeWindow() const
{
    return m_Window;
}