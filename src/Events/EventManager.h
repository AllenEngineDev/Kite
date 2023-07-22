#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_scancode.h>
#include <functional>
#include <map>
#include <string>
#include <sstream>

#include "Rect.h"
#include "Vector.h"
#include "Components/IDComponent.h"

// Use this in all classes that inherit from Event base class
#define EVENT_CLASS_TYPE(type) EventType GetType() const override { return EventType::type; }\


// All Event Types should go in this class, this should be the same name as the class 
// For example EventType::KeyDownEvent also has a class called KeyDownEvent
enum class EventType
{
    KeyDownEvent,
    MousePressedEvent,
    MouseReleasedEvent,
    MouseMotionEvent,

    // Events that pass across the layers
    // TODO: Seperate these events that pass across the layers into its own enum class
    EntitySelectedEvent,
    GuiViewportChange,
    PlayButtonPressedEvent
};

// Base class for all events
// YOU MUST USE EVENT_CLASS_TYPE(EventType::WhateverTypeYouWant) in every Event class that inherits from this
class Event
{
public:
    virtual EventType GetType() const = 0;

    // Override this for logging purposes when you want to log an event 
    // Include information about the specific event that happened (eg. key codes)
    // when overriding
    virtual std::string ToString() const { return "DefaultEventString"; }

    bool IsHandled() const { return m_Handled; }

    void SetHandled(bool value) { m_Handled = value; } 
private:
    EventType m_Type;
    bool m_Handled;
};

 // If you change these two using definitions, make sure to change them in EventManager.cpp too!
using EventFn = std::function<void(Event&)>;
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


class Entity;

// When an entity is selected
class EntitySelectedEvent : public Event
{
public:
    EntitySelectedEvent(Entity* entity)
        : m_Entity(entity) { }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Entity Selected Event: Entity ID -> " << m_Entity->GetComponent<IDComponent>()->GetID() ;
        return ss.str(); 
    }

    // IMPORTANT - Perform null-checking. If this is nullptr -> this means a mouse event has happened
    // that has not selected an entity
    Entity* GetEntity() const { return m_Entity; }

    EVENT_CLASS_TYPE(EntitySelectedEvent)

private:
    Entity* m_Entity;
};

// When the ImGui Viewport is resized -> this is to ensure the rendering viewport also resizes
class GuiViewportChange : public Event
{
public:
    GuiViewportChange(Rect newRect)
        : m_Rect(newRect) { }
    
    const Rect& GetRect() const { return m_Rect; }

    std::string ToString() const override 
    {
        std::stringstream ss;
        ss << "Viewport changed!: Position: (" << m_Rect.X << ", " << m_Rect.Y << ") Size: ("
            << m_Rect.Width << ", " << m_Rect.Height << ")";
        return ss.str();  
    }

    EVENT_CLASS_TYPE(GuiViewportChange)

private:
    Rect m_Rect;
};

class PlayButtonPressedEvent : public Event
{
public:
    PlayButtonPressedEvent() { };
    std::string ToString() const override
    {
        return "Play button was pressed!";
    }

    EVENT_CLASS_TYPE(PlayButtonPressedEvent)

};

class MousePressedEvent : public Event
{
public:
    MousePressedEvent(const Vector2<int>& pressedPosition)
        : m_PressedPosition(pressedPosition) { } 
    MousePressedEvent(const Vector2<int>& pressedPosition, 
        const Vector2<int>& windowPressedPosition)
        : m_PressedPosition(pressedPosition), m_WindowPressedPosition(windowPressedPosition) { } 

    // Returns the position where the mouse was pressed
    Vector2<int> GetPressedPosition() const
    {
        return m_PressedPosition;
    }

    Vector2<int> GetWindowPressedPosition() const
    {
        return m_WindowPressedPosition;
    }

    void SetMousePosition(const Vector2<int>& newPos)  
    {
        m_PressedPosition = newPos;
    }

    std::string ToString() const override 
    {
        std::stringstream ss;
        ss << "MousePressedEvent: Position: " << m_PressedPosition.X
             << ", " << m_PressedPosition.Y;
        return ss.str();  
    }

    EVENT_CLASS_TYPE(MousePressedEvent);

private:
    Vector2<int> m_PressedPosition;
    Vector2<int> m_WindowPressedPosition;
};

class MouseMotionEvent : public Event
{
public:
    MouseMotionEvent(Vector2<int> mousePosition, Vector2<int> windowMousePosition)
        : m_MousePosition(mousePosition), m_WindowMousePosition(windowMousePosition) { }

    Vector2<int> GetMousePosition() const { return m_MousePosition; }
    Vector2<int> GetWindowMousePosition() const { return m_WindowMousePosition; }

    EVENT_CLASS_TYPE(MouseMotionEvent)
private:
    Vector2<int> m_MousePosition;
    Vector2<int> m_WindowMousePosition;
};

class MouseReleasedEvent : public Event
{
public:
    MouseReleasedEvent(const Vector2<int>& releasedPosition)
            : m_ReleasedPosition(releasedPosition) { } 
    MouseReleasedEvent(const Vector2<int>& releasedPosition, 
        const Vector2<int>& windowReleasedPosition)
        : m_ReleasedPosition(releasedPosition), m_WindowReleasedPosition(windowReleasedPosition) { } 

        // Returns the position where the mouse was released
    Vector2<int> GetPressedPosition() const
    {
        return m_ReleasedPosition;
    }

    Vector2<int> GetWindowReleasedPosition() const
    {
        return m_WindowReleasedPosition;
    }

    void SetMousePosition(const Vector2<int>& newPos)  
    {
        m_ReleasedPosition = newPos;
    }

    std::string ToString() const override 
    {
        std::stringstream ss;
        ss << "MouseReleasedEvent: Position: " << m_ReleasedPosition.X
             << ", " << m_ReleasedPosition.Y;
        return ss.str();  
    }


    EVENT_CLASS_TYPE(MouseReleasedEvent)
private:
    Vector2<int> m_ReleasedPosition;
    Vector2<int> m_WindowReleasedPosition;
};

// This is only meant to be used to pass Events along the different layers in the layer stack
class EventManager
{
public:
    // Get the singleton instance
    static EventManager& Get(); 
    // Calls all functions attached to this EventType
    static void EventHappened(Event&& event);

    // The callback function will be called when EventHappened is called 
    // with this type passed in as an argument
    static void AddCallback(EventType type, EventFn callback, bool pushFront = false);

    // Remember to call this after detaching a layer from the layer stack
    static void RemoveCallback(EventType type, EventFn callback );

    // Only pass in valid Event*'s to this function, it does NOT perform type-checking.
    // Returns nullptr if the cast failed.
    template<typename T>
    static const T* CastEventToType(const Event* event)
    {
        return static_cast<const T*>(event);
    }
private:
    // TODO: This could be better as an unordered map
    static std::map<EventType, EventFnCallbacks> m_Callbacks;

    EventManager() = default; // Private constructor to prevent direct instantiation
    EventManager(const EventManager&) = delete; // Disable copy constructor
    EventManager& operator=(const EventManager&) = delete; // Disable assignment operator

};


std::ostream& operator<<(std::ostream& os, const Event& event);