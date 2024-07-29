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

    void subscribe(EventType type, const EventCallback callback)
    {
        m_Subscribers[type].emplace_back(callback);
    }

    void pushEvent(const std::shared_ptr<Event>& event)
    {
        m_EventQueue.push(event);
    }

    void processEventQueue()
    {
        while (!m_EventQueue.empty())
        {
            auto event = m_EventQueue.front();
            m_EventQueue.pop();
            dispatch(event);
        }
    }

private:
    void dispatch(std::shared_ptr<Event>& event)
    {
        auto it = m_Subscribers.find(event->type);
        if (it != m_Subscribers.end())
        {
            for (auto& callback : it->second)
            {
                callback(event);
            }
        }
    }

    std::queue<std::shared_ptr<Event>> m_EventQueue;
    std::unordered_map<EventType, std::vector<std::function<void(const std::shared_ptr<Event>&)>>> m_Subscribers;
};
