#include "game.hpp"

#include "input.hpp"
#include "filesystem.hpp"
#include "event.hpp"
#include "event_manager.hpp"

Game* Game::m_instance = nullptr;

Game::Game() : m_EventManager(std::make_shared<EventManager>(EventManager()))
{
    m_instance = this;
    isRunning = false;

    m_EventManager->subscribe<WindowCloseEvent>([&](auto& event)
    {
        LOGINFO("setting isRunning to false...");
        isRunning = false;
    });
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
    if (!m_window.init(m_EventManager))
	{
		LOGCRITICAL("Failed to create window.");
		return false;
	}

	Input::setWindow(m_window.getNativeWindow());
    renderer.init(m_EventManager);

    isRunning = true;
    run();

    return true;
}

Game& Game::get()
{
    return *m_instance;
}

void Game::run()
{
    while(isRunning)
	{
		update();
        render();
    }
}

void Game::update()
{
    if (Input::isKeyPressed(Input::KeyCode::Escape))
    {
        isRunning = false;
    }
}

void Game::render()
{
    m_window.clear(glm::vec3(0.5f, 0.5f, 0.5f));

    renderer.render();

    m_window.swapBuffers();
}
