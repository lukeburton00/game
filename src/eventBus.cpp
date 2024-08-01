#include "eventBus.hpp"

void EventBus::subscribe(EventType type, const EventCallback& callback)
{
    m_Subscribers[type].emplace_back(callback);
}

void EventBus::pushEvent(const std::shared_ptr<Event>& event)
{
    m_EventQueue.push(event);
}

void EventBus::processEventQueue()
{
    while (!m_EventQueue.empty())
    {
        auto& event = m_EventQueue.front();
        dispatch(event);
        m_EventQueue.pop();
    }
}

void EventBus::dispatch(const std::shared_ptr<Event>& event)
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