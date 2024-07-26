#pragma once

#include "event_manager.hpp"
#include "log.hpp"

class EventPublisher
{
public:

    EventPublisher() : m_EventManager(nullptr){}
    EventPublisher(std::shared_ptr<EventManager> event_manager) : m_EventManager(event_manager){}

    void setEventManager(std::shared_ptr<EventManager> event_manager)
    {
        m_EventManager = event_manager;
    }

    template<typename T>
    void publish(const T& event)
    {
        if (m_EventManager)
            m_EventManager->dispatch(event);

        else
            LOGERROR("EventManager not set for EventPublisher.");
    }

private:
    std::shared_ptr<EventManager> m_EventManager;
};
