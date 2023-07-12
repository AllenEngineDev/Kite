#pragma once

#include <SDL2/SDL.h>
#include <functional>
#include <map>

// Use this in all classes that inherit from Event base class
#define EVENT_CLASS_TYPE(type) EventType GetType() const override { return EventType::type; }\

// All Event Types should go in this class, this should be the same name as the class 
// For example EventType::KeyDownEvent also has a class called KeyDownEvent
enum class EventType
{
    KeyDownEvent,
};

// Base class for all events
// YOU MUST USE EVENT_CLASS_TYPE(EventType::WhateverTypeYouWant) in every Event class that inherits from this
class Event
{
public:
    virtual EventType GetType() const { return m_Type; }

private:
    EventType m_Type;
};

class KeyDownEvent : public Event
{
public:
    KeyDownEvent(SDL_KeyboardEvent* keyEvent)
        : m_KeyEvent(keyEvent) { }

    EVENT_CLASS_TYPE(KeyDownEvent);
private:
    SDL_KeyboardEvent* m_KeyEvent;
};

class EventManager
{
private:
    // If you change these two using definitions, make sure to change them in EventManager.cpp too!
    using EventFn = std::function<void(const Event&)>;
    using EventFnCallbacks = std::vector<EventFn>;

    static std::map<EventType, EventFnCallbacks> m_Callbacks;
public:
    // Calls all functions attached to this EventType
    static void EventHappened(const Event& event);

    // The callback function will be called when EventHappened is called 
    // with this type passed in as an argument
    static void AddCallback(EventType type, EventFn callback);


    // Only pass in valid Event*'s to this function, it does NOT perform type-checking.
    // Returns nullptr if the cast failed.
    template<typename T>
    static const T* CastEventToType(const Event* event)
    {
        return static_cast<const T*>(event);
    }

};