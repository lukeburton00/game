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
    EventBus(const EventBus&) = delete;
    EventBus& operator= (const EventBus&) = delete;

    void subscribe(EventType type, const EventCallback& callback);
    void pushEvent(const std::shared_ptr<Event>& event);
    void processEventQueue();

private:
    void dispatch(const std::shared_ptr<Event>& event);

private:
    std::queue<std::shared_ptr<Event>> m_EventQueue;
    std::unordered_map<EventType, std::vector<EventCallback>> m_Subscribers;
};
