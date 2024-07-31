#include "game.hpp"

#include <memory>

#include "log.hpp"
#include "input.hpp"
#include "event.hpp"
#include "event_bus.hpp"
#include "filesystem.hpp"

Game* Game::m_instance = nullptr;

Game::Game() : m_EventBus(std::make_shared<EventBus>())
{
    m_instance = this;
    m_isRunning = false;
}

Game::~Game()
{

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

    m_window = Window(WIDTH, HEIGHT, TITLE);
    if (!m_window.init(m_EventBus))
	{
		LOGCRITICAL("Failed to create window.");
		return false;
	}

	Input::setWindow(m_window.getNativeWindow());
    renderer.init(m_EventBus);

    m_isRunning = true;
    run();

    return true;
}

Game& Game::get()
{
    return *m_instance;
}

void Game::run()
{
    m_EventBus->subscribe(EventType::WindowClose, [=](const std::shared_ptr<Event>& event)
        {
            m_isRunning = false;
        });

    m_EventBus->subscribe(EventType::KeyPressed, [=](const std::shared_ptr<Event>& event)
        {
            auto e = std::static_pointer_cast<KeyPressedEvent>(event);  
            if (e->key == (int)Input::KeyCode::Escape)
            {
                m_isRunning = false;
            }
        });

    m_EventBus->subscribe(EventType::KeyPressed, [=](const std::shared_ptr<Event>& event)
        {
            auto e = std::static_pointer_cast<KeyPressedEvent>(event);  
            if (e->key == (int)Input::KeyCode::F10)
            {
                m_window.toggleFullscreen();
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
    
}

void Game::render()
{
    m_window.clear(glm::vec3(0.5f, 0.5f, 0.5f));

    renderer.render();

    m_window.swapBuffers();
}
