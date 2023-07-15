#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_scancode.h>
#include <functional>
#include <map>
#include <string>
#include <sstream>

#include "Vector.h"

// Use this in all classes that inherit from Event base class
#define EVENT_CLASS_TYPE(type) EventType GetType() const override { return EventType::type; }\


// All Event Types should go in this class, this should be the same name as the class 
// For example EventType::KeyDownEvent also has a class called KeyDownEvent
enum class EventType
{
    KeyDownEvent,
    MousePressedEvent,

    // Events that pass across the layers
    // TODO: Seperate these events that pass across the layers into its own enum class
    EntitySelectedEvent
};

// Base class for all events
// YOU MUST USE EVENT_CLASS_TYPE(EventType::WhateverTypeYouWant) in every Event class that inherits from this
class Event
{
public:
    virtual EventType GetType() const { return m_Type; }

    // Override this for logging purposes when you want to log an event 
    // Include information about the specific event that happened (eg. key codes)
    // when overriding
    virtual std::string ToString() const { return "DefaultEventString"; } 
private:
    EventType m_Type;
};

 // If you change these two using definitions, make sure to change them in EventManager.cpp too!
using EventFn = std::function<void(const Event&)>;
using EventFnCallbacks = std::vector<EventFn>;

class KeyDownEvent : public Event
{
public:
    KeyDownEvent(SDL_KeyboardEvent* keyEvent)
        : m_KeyEvent(keyEvent) { }

    SDL_Scancode GetKeyCode() const { return m_KeyEvent->keysym.scancode; }

    std::string ToString() const override 
    {
        std::stringstream ss;
        ss << "KeyDownEvent: Keycode: " << GetKeyCode();
        return ss.str();  
    }

    EVENT_CLASS_TYPE(KeyDownEvent);
private:
    SDL_KeyboardEvent* m_KeyEvent;
};


// When an entity is selected
class EntitySelectedEvent : public Event
{
public:
    EntitySelectedEvent(uint64_t entityID)
        : m_EntityID(entityID) { }

    EVENT_CLASS_TYPE(EntitySelectedEvent)

private:
    uint64_t m_EntityID;
};

class MousePressedEvent : public Event
{
public:
    MousePressedEvent(SDL_MouseButtonEvent* mouseEvent) 
        : m_MouseEvent(mouseEvent) { }

    // Returns the position where the mouse was pressed
    Vector2<int> GetPressedPosition() const
    {
        return Vector2<int>(m_MouseEvent->x, m_MouseEvent->y);
    }

    std::string ToString() const override 
    {
        std::stringstream ss;
        ss << "MousePressedEvent: Position: " << m_MouseEvent->x << ", " << m_MouseEvent->y;
        return ss.str();  
    }

    EVENT_CLASS_TYPE(MousePressedEvent);

private:
    SDL_MouseButtonEvent* m_MouseEvent;
};

// This is only meant to be used to pass Events along the different layers in the layer stack
class EventManager
{
private:
    // TODO: This could be better as an unordered map
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


std::ostream& operator<<(std::ostream& os, const Event& event);