#include "window.hpp"

#include <GLFW/glfw3.h>

#include "event.hpp"
#include "log.hpp"

static void glfwErrorCallback(int error, const char* message)
{
    LOGCRITICAL("GLFW Error: {} - {}", error, message);
}

Window::Window(const WindowProperties& properties)
: m_properties(properties)
{
    m_isFullScreen = false;
    m_isVSync = true;    
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

    setWindowHints();

	if (!(m_Window = glfwCreateWindow(m_properties.width, m_properties.height, m_properties.title.c_str(), nullptr, nullptr)))
	{
		LOGCRITICAL("Failed to create GLFW window.");
        glfwTerminate();
        return false;
	}

    glfwMakeContextCurrent(m_Window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    setGLFWCallbacks();

	LOGINFO("OpenGL version {}", (char*)glGetString(GL_VERSION));
	LOGINFO("Graphics device: {}", (char*)glGetString(GL_RENDERER));

	glViewport(0, 0, m_properties.width, m_properties.height);
    glfwSwapInterval(1);

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

uint32_t Window::getWidth() const
{
    return m_properties.width;
}

uint32_t Window::getHeight() const
{
    return m_properties.height;
}

void Window::setFullScreen(bool shouldEnable)
{
    if (m_isFullScreen && shouldEnable)
    {
        LOGERROR("setFullScreen: Fullscreen already enabled.");
        return;
    }

    if (!m_isFullScreen && !shouldEnable)
    {
        LOGERROR("setFullScreen: Fullscreen already disabled.");
        return;
    }

    static int windowedWidth, windowedHeight, windowedPosX, windowedPosY;
    
    if (shouldEnable)
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwGetWindowSize(m_Window, &windowedWidth, &windowedHeight);
        glfwGetWindowPos(m_Window, &windowedPosX, &windowedPosY);
        glfwSetWindowMonitor(m_Window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

        m_properties.eventCallback(std::make_shared<WindowMaximizedEvent>());
    }

    else
    {
        glfwSetWindowMonitor(m_Window, nullptr, windowedPosX, windowedPosY, windowedWidth, windowedHeight, 0);
    }

    m_isFullScreen = shouldEnable;
}

void Window::setVSync(bool shouldEnable)
{
    if (m_isVSync && shouldEnable)
    {
        LOGERROR("setVSync: VSync already enabled.");
        return;
    }

    if (!m_isVSync && !shouldEnable)
    {
        LOGERROR("setVSync: VSync already disabled.");
        return;
    }

    glfwSwapInterval(shouldEnable);
    m_isVSync = shouldEnable;
}

GLFWwindow* Window::getNativeWindow() const
{
    return m_Window;
}

void Window::setEventCallback(EventCallback callback)
{
    m_properties.eventCallback = callback;
}

void Window::setGLFWCallbacks()
{
    glfwSetErrorCallback(glfwErrorCallback);
    glfwSetWindowUserPointer(m_Window, this);

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
    {
        auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (width == 0 && height == 0)
        {
            LOGINFO("Window minimized", width, height);
            win->m_properties.eventCallback(std::make_shared<WindowMinimizedEvent>());
        }

        else
        {
            LOGINFO("Window resized to {} x {}", width, height);
            win->m_properties.eventCallback(std::make_shared<WindowResizeEvent>(width, height));
        }

        win->m_properties.width = width;
        win->m_properties.height = height;
        glViewport(0, 0, width, height);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
    {
        auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        LOGINFO("Window closed");
        win->m_properties.eventCallback(std::make_shared<WindowCloseEvent>());
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
		auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		switch (action)
		{
		    case GLFW_PRESS:
			{
    			LOGINFO("Key {} pressed with mods {}", key, mods);
                win->m_properties.eventCallback(std::make_shared<KeyPressedEvent>(key, mods));
                break;
			}

			case GLFW_RELEASE:
			{
    			LOGINFO("Key {} released with mods {}", key, mods);
    			win->m_properties.eventCallback(std::make_shared<KeyReleasedEvent>(key, mods));
                break;
			}

			case GLFW_REPEAT:
			{
    		    LOGINFO("Key {} repeated with mods {}", key, mods);
    			win->m_properties.eventCallback(std::make_shared<KeyRepeatedEvent>(key, mods));
                break;
			}

			default:
                break;
		}
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
    {
        auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		switch (action)
		{
		    case GLFW_PRESS:
			{
    			LOGINFO("Mouse button {} pressed with mods {}", button, mods);
                win->m_properties.eventCallback(std::make_shared<MouseButtonPressedEvent>(button, mods));
                break;
			}

			case GLFW_RELEASE:
			{
    			LOGINFO("Mouse button {} released with mods {}", button, mods);
                win->m_properties.eventCallback(std::make_shared<MouseButtonReleasedEvent>(button, mods));
                break;
			}

			case GLFW_REPEAT:
			{
    		    LOGINFO("Mouse button {} repeated with mods {}", button, mods);
                win->m_properties.eventCallback(std::make_shared<MouseButtonRepeatedEvent>(button, mods));
                break;
			}

			default: 
                break;
		}
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
    {
        auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        LOGINFO("Mouse scroll X: {} Y: {}", xoffset, yoffset);
        win->m_properties.eventCallback(std::make_shared<MouseWheelEvent>(xoffset, yoffset));
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
    {
        auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        LOGINFO("Mouse moved to {}, {}", xpos, ypos);

    });
}

void Window::setWindowHints()
{
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
}