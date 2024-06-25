#include "window.hpp"

#include "log.hpp"
#include "game.hpp"

static void glfwErrorCallback(int error, const char* message)
{
    LOGCRITICAL("GLFW Error: {} - {}", error, message);
}

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

    /* Select highest supported OpenGL version if on Mac OS,
    otherwise select the most recent version */
    #if defined(__APPLE__) || defined(__MACH__)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #else
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    #endif
    
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!(m_Window = glfwCreateWindow(m_WindowProperties.width, m_WindowProperties.height, m_WindowProperties.title.c_str(), nullptr, nullptr)))
	{
		LOGCRITICAL("Failed to create GLFW window.");
        glfwTerminate();
        return false;
	}

    glfwMakeContextCurrent(m_Window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    Game::get().getEventDispatcher().subscribe<WindowResizeEvent>([&](const WindowResizeEvent& event)
    {
        m_WindowProperties.width = event.width;
        m_WindowProperties.height = event.height;
    });

    glfwSetWindowUserPointer(m_Window, this);
    glfwSetErrorCallback(glfwErrorCallback);
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
    {
        LOGINFO("Window resized to {} x {}", width, height);
        Game::get().getEventDispatcher().dispatch<WindowResizeEvent>(WindowResizeEvent(width, height));
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
    {
        LOGINFO("Window closed");
        Game::get().getEventDispatcher().dispatch<WindowCloseEvent>(WindowCloseEvent());
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
		if (action == GLFW_PRESS)
			LOGINFO("Key {} pressed with mods {}", key, mods);
            Game::get().getEventDispatcher().dispatch<KeyPressedEvent>(KeyPressedEvent(key, mods));

		if (action == GLFW_RELEASE)
			LOGINFO("Key {} released with mods {}", key, mods);
            Game::get().getEventDispatcher().dispatch<KeyReleasedEvent>(KeyReleasedEvent(key, mods));

		if (action == GLFW_REPEAT)
		    LOGINFO("Key {} repeated with mods {}", key, mods);
            Game::get().getEventDispatcher().dispatch<KeyRepeatedEvent>(KeyRepeatedEvent(key, mods));
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
    {
		if (action == GLFW_PRESS)
			LOGINFO("Mouse button {} pressed with mods {}", button, mods);
            Game::get().getEventDispatcher().dispatch<MouseButtonPressedEvent>(MouseButtonPressedEvent(button, mods));

		if (action == GLFW_RELEASE)
			LOGINFO("Mouse button {} released with mods {}", button, mods);
            Game::get().getEventDispatcher().dispatch<MouseButtonReleasedEvent>(MouseButtonReleasedEvent(button, mods));

		if (action == GLFW_REPEAT)
		    LOGINFO("Mouse button {} repeated with mods {}", button, mods);
            Game::get().getEventDispatcher().dispatch<MouseButtonRepeatedEvent>(MouseButtonRepeatedEvent(button, mods));
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
    {
        LOGINFO("Mouse scroll X: {} Y: {}", xoffset, yoffset);
        Game::get().getEventDispatcher().dispatch<MouseWheelEvent>(MouseWheelEvent(xoffset, yoffset));
    });


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