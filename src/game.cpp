#include "game.hpp"

#include "input.hpp"

Game* Game::m_instance = nullptr;

Game::Game()
{
    m_instance = this;
    isRunning = false;

    m_dispatcher.subscribe<WindowCloseEvent>([&](auto& event)
    {
        isRunning = false;
    });
}

Game::~Game()
{

}

bool Game::start()
{
    const int WIDTH = 640;
	const int HEIGHT = 480;
	const std::string TITLE = "OpenGL";

    m_window = Window(WIDTH, HEIGHT, TITLE);
    if (!m_window.init())
	{
		LOGCRITICAL("Failed to create window.");
		return false;
	}

	Input::init(m_window.getNativeWindow());
    renderer.init();

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