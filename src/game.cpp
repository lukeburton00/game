#include "game.hpp"

#include <memory>

#include "log.hpp"
#include "input.hpp"
#include "filesystem.hpp"

Game* Game::m_instance = nullptr;

Game::Game() : m_EventBus(std::make_shared<EventBus>())
{
    m_instance = this;
    m_isRunning = false;
}

bool Game::initPaths()
{
    auto exec_path = FileSystem::getExecPath();
    if (!exec_path.has_value())
    {
        LOGCRITICAL("Could not find executable path.");
        return false;
    }

    LOGINFO("Executable path: {}", exec_path.value().string());

    auto assets_path = FileSystem::findDirUp(exec_path.value(), "assets", 2);
    if (!assets_path.has_value())
    {
        LOGCRITICAL("Could not find assets path.");
        return false;
    }

    LOGINFO("Assets path: {}", assets_path.value().string());
    FileSystem::setCurrentPath(assets_path.value());

    return true;
}

bool Game::start()
{
    if (!initPaths())
    {
        LOGCRITICAL("Failed to initialize paths.");
        return false;
    }

    const int WIDTH = 640;
	const int HEIGHT = 480;
	const std::string TITLE = "OpenGL";

    WindowProperties props;
    props.width = WIDTH;
    props.height = HEIGHT;
    props.title = TITLE;

    m_window = Window(props);

    if (!m_window.init())
	{
		LOGCRITICAL("Failed to create window.");
		return false;
	}

    m_window.setEventCallback([this](const std::shared_ptr<Event>& event)
    {
        this->onEvent(event);  
    });

    renderer.init(m_EventBus);

    camera = Camera(glm::vec2(0, 0), m_window.getWidth(), m_window.getHeight());

    run();

    return true;
}

Game& Game::get()
{
    return *m_instance;
}

void Game::run()
{
    m_isRunning = true;
    m_EventBus->subscribe(EventType::WindowClose, [=](const std::shared_ptr<Event>& event)
        {
            m_isRunning = false;
        });

    m_EventBus->subscribe(EventType::KeyPressed, [=](const std::shared_ptr<Event>& event)
        {
            auto e = std::static_pointer_cast<KeyPressedEvent>(event);
            switch ((Input::KeyCode)e->key)
            {
            case Input::KeyCode::Escape:
                m_isRunning = false;
                break;

            case Input::KeyCode::F8:
                m_window.setVSync(true);
                break;

            case Input::KeyCode::F9:
                m_window.setVSync(false);
                break;

            case Input::KeyCode::F10:
                m_window.setFullScreen(true);
                break;

            case Input::KeyCode::F11:
                m_window.setFullScreen(false);
                break;

            default:
                break;
            }
        });

    while(m_isRunning)
	{
		update();
        render();
	    processEvents();
    }
}

void Game::processEvents()
{
    m_EventBus->processEventQueue();
}

void Game::update()
{
    if (Input::isKeyPressed(Input::KeyCode::W))
    {
        camera.position.y += 1;
    }    
    
    if (Input::isKeyPressed(Input::KeyCode::A))
    {
        camera.position.x -= 1;
    }    
    
    if (Input::isKeyPressed(Input::KeyCode::S))
    {
        camera.position.y -= 1;
    }    
    
    if (Input::isKeyPressed(Input::KeyCode::D))
    {
        camera.position.x += 1;
    }

    camera.Update();
}

void Game::render()
{
    m_window.clear(glm::vec3(0.5f, 0.5f, 0.5f));

    renderer.beginBatch(camera);
    
    // Render a batched set of i * j textured quads
    for (int i = 0; i < 250; i++)
    {
        for (int j = 0; j < 250; j++)
        {
            bool isInCameraBounds = (i * 50.f < camera.position.x + m_window.getWidth() || j * 50.f < camera.position.y + m_window.getHeight());
            
            if (isInCameraBounds)
                renderer.pushQuad(glm::vec2(0.f + (i * 50.f), 0.f + (j * 50.f)), glm::vec2(50, 50), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(0, 0), glm::vec2(100, 100));
        }
    }

    renderer.flush();

    m_window.swapBuffers();
}

void Game::onEvent(const std::shared_ptr<Event>& event)
{
    m_EventBus->pushEvent(event);
}
