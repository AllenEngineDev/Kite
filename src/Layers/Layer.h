#pragma once
#include "Events/EventManager.h"

// Interface for Layer subclasses
class Layer
{  
public:
    virtual void OnAttach() = 0;
    virtual void OnDetach() = 0;
    virtual void OnEvent(const Event& event) = 0;
    virtual void OnUpdate() = 0;
    virtual void OnRender() = 0;    
};

class TestLayer
{
public:
    void OnAttach()
    {

    }
    void OnDetach()
    {

    }
    void OnEvent(const Event& event)
    {

    }
    void OnUpdate()
    {

    }
    void OnRender()
    {
        
    }
};