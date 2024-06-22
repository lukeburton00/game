#include "game.hpp"

#include "input.hpp"

Game::Game()
{
    isRunning = false;
}

Game::~Game()
{

}

void Game::start()
{
    const int WIDTH = 640;
	const int HEIGHT = 480;
	const std::string TITLE = "OpenGL";

    window = Window(WIDTH, HEIGHT, TITLE);
    window.init();

	Input::init(window.getNativeWindow());

    isRunning = true;
    run();
}

void Game::run()
{
    while(!glfwWindowShouldClose(window.getNativeWindow()))
	{
		update();
        render();
    }
}

void Game::update()
{
    if (Input::isKeyPressed(Input::KeyCode::Escape))
    {
        glfwSetWindowShouldClose(window.getNativeWindow(), true);
    }
}

void Game::render()
{
    window.clear(glm::vec3(1.f, 1.f, 1.f));

    window.swapBuffers();
}