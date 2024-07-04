#pragma once

#include "window.hpp"
#include "renderer.hpp"
#include "event_dispatcher.hpp"

class Game 
{
public:
    Game();
    ~Game();
    bool start();
    static Game& get();
    EventDispatcher& getEventDispatcher() { return m_dispatcher; }
    Window& getWindow() { return m_window; }

private:
    void run();
    void update();
    void render();

private:
    Window m_window;
    bool isRunning;
    EventDispatcher m_dispatcher;
    Renderer renderer;

    static Game* m_instance;
};