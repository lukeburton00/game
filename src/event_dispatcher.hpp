#pragma once

#include <vector>
#include <typeindex>
#include <functional>
#include <unordered_map>

#include "event.hpp"

class EventDispatcher {
public:
    EventDispatcher() = default;

    template <typename T>
    using EventCallback = std::function<void(const T&)>;

    template<typename T>
    void subscribe(const EventCallback<T>& callback) {
        m_Subscribers[typeid(T)].push_back([callback](const Event& event) {
            callback(static_cast<const T&>(event));
        });
    }

    template<typename T>
    void unsubscribe(const EventCallback<T>& callback) {
        auto& subscribers = m_Subscribers[typeid(T)];
        subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), callback), subscribers.end());
    }

    template<typename T>
    void dispatch(const T& event) {
        auto& subscribers = m_Subscribers[typeid(T)];
        for (auto& callback : subscribers) {
            callback(event);
        }
    }
    
private:
    std::unordered_map<std::type_index, std::vector<std::function<void(const Event&)>>> m_Subscribers;
};