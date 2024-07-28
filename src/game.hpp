#pragma once

#include "window.hpp"
#include "renderer.hpp"
#include "event_manager.hpp"

class Game
{
public:
    Game();
    ~Game();
    bool initPaths();
    bool start();

    static Game& get();
    std::shared_ptr<EventManager> getEventManager() { return m_EventManager; }
    Window& getWindow() { return m_window; }

private:
    void run();
    void update();
    void render();

private:
    Window m_window;
    bool isRunning;

    Renderer renderer;

    std::shared_ptr<EventManager> m_EventManager;
    static Game* m_instance;
};
