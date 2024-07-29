#pragma once

#include "window.hpp"
#include "renderer.hpp"
#include "event_bus.hpp"

class Game
{
public:
    Game();
    ~Game();
    bool initPaths();
    bool start();

    static Game& get();
    Window& getWindow() { return m_window; }

private:
    void run();
    void processEvents();
    void update();
    void render();

private:
    Window m_window;
    bool isRunning;

    Renderer renderer;

    std::shared_ptr<EventBus> m_EventBus;
    static Game* m_instance;
};
