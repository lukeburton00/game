#pragma once

#include "window.hpp"
#include "renderer.hpp"
#include "event_manager.hpp"

class Game
{
public:
    Game();
    ~Game();
    bool start();
    static Game& get();
    EventManager& getEventManager() { return m_EventManager; }
    Window& getWindow() { return m_window; }

private:
    void run();
    void update();
    void render();

private:
    Window m_window;
    bool isRunning;
    EventManager m_EventManager;
    Renderer renderer;

    static Game* m_instance;
};
