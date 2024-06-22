#pragma once

#include "window.hpp"

class Game 
{
public:
    Game();
    ~Game();
    bool start();

private:
    void run();
    void update();
    void render();

private:
    Window window;
    bool isRunning;
};