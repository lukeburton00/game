#pragma once

#include <vector>
#include <typeindex>
#include <functional>
#include <unordered_map>
#include <algorithm>

#include "event.hpp"
#include "log.hpp"

class EventDispatcher 
{
public:
    EventDispatcher() = default;

    template <typename T>
    using EventCallback = std::function<void(const T&)>;

    using SubscriptionHandle = size_t;

    template<typename T>
    SubscriptionHandle subscribe(const EventCallback<T>& callback) 
    {
        auto handle = m_NextHandle++;
        m_Subscribers[typeid(T)].emplace_back(handle, [callback](const Event& event) 
        {
            callback(static_cast<const T&>(event));
        });
        return handle;
    }

    template<typename T>
    void unsubscribe(SubscriptionHandle handle) 
    {
        for (auto& kv: m_Subscribers)
        {
            LOGINFO("Unsubscribing");
            auto& subscribers = kv.second;
            subscribers.erase(std::remove_if(subscribers.begin(), subscribers.end(), 
                [handle](const std::pair<SubscriptionHandle, std::function<void(const Event&)>>& pair) 
                {
                    return pair.first == handle;
                }), subscribers.end());
        }
    }

    template<typename T>
    void dispatch(const T& event) 
    {
        auto& subscribers = m_Subscribers[typeid(T)];
        for (auto& subscriber : subscribers) 
        {
            subscriber.second(event);
        }
    }
    
private:
    SubscriptionHandle m_NextHandle = 0;
    
    std::unordered_map
        <std::type_index, std::vector<
        std::pair<SubscriptionHandle, std::function<void(const Event&)>>>> m_Subscribers;
};
