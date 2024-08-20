#pragma once

#include "window.hpp"
#include "renderer/renderer.hpp"
#include "eventBus.hpp"

class Game
{
public:
    Game();

    Game(const Game&) = delete;
    Game& operator= (const Game&) = delete;

    bool initPaths();
    bool start();

    static Game& get();
    Window& getWindow() { return m_window; }

private:
    void run();
    void processEvents();
    void update();
    void render();
    void onEvent(const std::shared_ptr<Event>& event);

private:
    Window m_window;
    bool m_isRunning;

    Renderer renderer;
    Camera camera;

    std::shared_ptr<EventBus> m_EventBus;
    static Game* m_instance;
};
