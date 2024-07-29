#pragma once

#include <memory>
#include <queue>
#include <vector>
#include <functional>
#include <unordered_map>

#include "event.hpp"

class EventBus
{
public:
    EventBus() = default;

    using EventCallback = std::function<void(const std::shared_ptr<Event>&)>;

    void subscribe(EventType type, const EventCallback callback);

    void pushEvent(const std::shared_ptr<Event>& event);

    void processEventQueue();

private:
    void dispatch(std::shared_ptr<Event>& event);

    std::queue<std::shared_ptr<Event>> m_EventQueue;
    std::unordered_map<EventType, std::vector<std::function<void(const std::shared_ptr<Event>&)>>> m_Subscribers;
};
