#pragma once

enum class EventType
{
    WindowResize,
    WindowClose,
    WindowFocus,
    WindowLostFocus,
    WindowMinimized,
    WindowMaximized,
    MouseMoved,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseButtonRepeated,
    MouseWheel,
    KeyPressed,
    KeyReleased,
    KeyRepeated
};

struct Event
{
    virtual ~Event() = default;
    EventType type;
};

struct WindowResizeEvent : public Event
{
    WindowResizeEvent(int width, int height)
    {
        type = EventType::WindowResize;
        this->width = width;
        this->height = height;
    }

    int width, height;
};

struct WindowCloseEvent : public Event
{
    WindowCloseEvent()
    {
        type = EventType::WindowClose;
    }
};

struct WindowFocusEvent : public Event
{
    WindowFocusEvent()
    {
        type = EventType::WindowFocus;
    }
};

struct WindowLostFocusEvent : public Event
{
    WindowLostFocusEvent()
    {
        type = EventType::WindowLostFocus;
    }
};

struct WindowMinimizedEvent : public Event
{
    WindowMinimizedEvent()
    {
        type = EventType::WindowMinimized;
    }
};

struct WindowMaximizedEvent : public Event
{
    WindowMaximizedEvent()
    {
        type = EventType::WindowMaximized;
    }
};

struct MouseMovedEvent : public Event
{
    MouseMovedEvent(float x, float y)
    {
        type = EventType::MouseMoved;
        this->x = x;
        this->y = y;
    }

    float x, y;
};

struct MouseButtonPressedEvent : public Event
{
    MouseButtonPressedEvent(int button, int mods)
    {
        type = EventType::MouseButtonPressed;
        this->button = button;
        this->mods = mods;
    }

    int button;
    int mods;
};

struct MouseButtonReleasedEvent : public Event
{
    MouseButtonReleasedEvent(int button, int mods)
    {
        type = EventType::MouseButtonReleased;
        this->button = button;
        this->mods = mods;
    }

    int button;
    int mods;
};

struct MouseButtonRepeatedEvent : public Event
{
    MouseButtonRepeatedEvent(int button, int mods)
    {
        type = EventType::MouseButtonRepeated;
        this->button = button;
        this->mods = mods;
    }

    int button;
    int mods;
};

struct MouseWheelEvent : public Event
{
    MouseWheelEvent(float xoffset, float yoffset)
    {
        type = EventType::MouseWheel;
        this->xoffset = xoffset;
        this->yoffset = yoffset;
    }

    float xoffset;
    float yoffset;
};

struct KeyPressedEvent : public Event
{
    KeyPressedEvent(int key, int mods)
    {
        type = EventType::KeyPressed;
        this->key = key;
        this->mods = mods;
    }

    int key;
    int mods;
};

struct KeyReleasedEvent : public Event
{
    KeyReleasedEvent(int key, int mods)
    {
        type = EventType::KeyReleased;
        this->key = key;
        this->mods = mods;
    }

    int key;
    int mods;
};

struct KeyRepeatedEvent : public Event
{
    KeyRepeatedEvent(int key, int mods)
    {
        type = EventType::KeyRepeated;
        this->key = key;
        this->mods = mods;
    }

    int key;
    int mods;
};
