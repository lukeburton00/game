#include "window.hpp"

#include <GLFW/glfw3.h>

#include "event.hpp"
#include "log.hpp"

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

bool Window::init(std::shared_ptr<EventBus> eventBus)
{
    m_EventBus = eventBus;

    m_EventBus->subscribe(EventType::WindowResize, [=](const std::shared_ptr<Event>& event)
        {
            auto e = std::static_pointer_cast<WindowResizeEvent>(event);
            m_WindowProperties.width = e->width;
            m_WindowProperties.height = e->height;
            glViewport(0, 0, e->width, e->height);
        });

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

    glfwSetErrorCallback(glfwErrorCallback);
    glfwSetWindowUserPointer(m_Window, this);

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
    {
        LOGINFO("Window resized to {} x {}", width, height);
        auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (width == 0 && height == 0)
        {
            LOGINFO("Window minimized", width, height);
            win->m_EventBus->pushEvent(std::make_shared<WindowMinimizedEvent>());
        }

        else
        {
            LOGINFO("Window resized to {} x {}", width, height);
            win->m_EventBus->pushEvent(std::make_shared<WindowResizeEvent>(width, height));
        }
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
    {
        auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        LOGINFO("Window closed");
        win->m_EventBus->pushEvent(std::make_shared<WindowCloseEvent>());
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
		auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		switch (action)
		{
		    case GLFW_PRESS:
			{
    			LOGINFO("Key {} pressed with mods {}", key, mods);
                win->m_EventBus->pushEvent(std::make_shared<KeyPressedEvent>(key, mods));
                break;
			}

			case GLFW_RELEASE:
			{
    			LOGINFO("Key {} released with mods {}", key, mods);
    			win->m_EventBus->pushEvent(std::make_shared<KeyReleasedEvent>(key, mods));
                break;
			}

			case GLFW_REPEAT:
			{
    		    LOGINFO("Key {} repeated with mods {}", key, mods);
    			win->m_EventBus->pushEvent(std::make_shared<KeyRepeatedEvent>(key, mods));
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
                win->m_EventBus->pushEvent(std::make_shared<MouseButtonPressedEvent>(button, mods));
                break;
			}

			case GLFW_RELEASE:
			{
    			LOGINFO("Mouse button {} released with mods {}", button, mods);
                win->m_EventBus->pushEvent(std::make_shared<MouseButtonReleasedEvent>(button, mods));
                break;
			}

			case GLFW_REPEAT:
			{
    		    LOGINFO("Mouse button {} repeated with mods {}", button, mods);
                win->m_EventBus->pushEvent(std::make_shared<MouseButtonRepeatedEvent>(button, mods));
			}

			default:
			    break;
		}
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
    {
        auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        LOGINFO("Mouse scroll X: {} Y: {}", xoffset, yoffset);
        win->m_EventBus->pushEvent(std::make_shared<MouseWheelEvent>(xoffset, yoffset));
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

int Window::getWidth() const
{
    return m_WindowProperties.width;
}

int Window::getHeight() const
{
    return m_WindowProperties.height;
}

GLFWwindow* Window::getNativeWindow() const
{
    return m_Window;
}
