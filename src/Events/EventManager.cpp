#include "EventManager.h"

// These are just copied from the EventManager class
using EventFn = std::function<void(Event&)>;
using EventFnCallbacks = std::vector<EventFn>;

std::map<EventType, EventFnCallbacks> EventManager::m_Callbacks;


void EventManager::EventHappened(Event&& event)
{
    // Getting the event type so we can get the relevant callbacks from m_Callbacks
    EventType type = event.GetType();

    if (m_Callbacks.count(type) > 0)
    {   
        // m_Callbacks[type] is a vector of EventFn which is a std::function<void(Event&)>;
        // For every EventFn, call it!
        for (const EventFn& callback : m_Callbacks[type])
        {
            if (!event.IsHandled())
                callback(event);
        }
    }
}

void EventManager::AddCallback(EventType type, EventFn callback, bool pushFront)
{
    // Insert to the front of the map if this is the case
    // This will be the events that will be handled first
    if (pushFront) 
    {
        m_Callbacks[type].insert(m_Callbacks[type].begin(), callback);
        return;
    }

    m_Callbacks[type].emplace_back(callback);
}

// To be able to log events to the console
// Overload the << operator for Event objects
std::ostream& operator<<(std::ostream& os, const Event& event) {
    os << event.ToString();
    return os;
}