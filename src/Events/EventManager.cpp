#include "EventManager.h"

// These are just copied from the EventManager class
using EventFn = std::function<void(const Event&)>;
using EventFnCallbacks = std::vector<EventFn>;

std::map<EventType, EventFnCallbacks> EventManager::m_Callbacks;


void EventManager::EventHappened(const Event& event)
{
    EventType type = event.GetType();

    if (m_Callbacks.count(type) > 0)
    {   
        // m_Callbacks[type] is a vector of EventFn which is a std::function<void(Event&)>;
        // For every EventFn, call it!
        for (const EventFn& callback : m_Callbacks[type])
        {
            callback(event);
        }
    }
}

void EventManager::AddCallback(EventType type, EventFn callback)
{
    m_Callbacks[type].emplace_back(callback);
}

// To be able to log events to the console
// Overload the << operator for Event objects
std::ostream& operator<<(std::ostream& os, const Event& event) {
    os << event.ToString();
    return os;
}