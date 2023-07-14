#pragma once
#include "Events/EventManager.h"
#include <iostream>
#include <string>

// Use this on layers you want to use GetLayerName() on 
#define LAYER_NAME(x) std::string GetLayerName() { return #x; }

// Interface for Layer subclasses
class Layer
{  
public:
    virtual void OnAttach() = 0;
    virtual void OnDetach() = 0;
    virtual void OnEvent(const Event& event) = 0;
    virtual void OnUpdate() = 0;
    virtual void OnRender() = 0;    
    std::string GetLayerName() { return "DefaultLayerName"; }
};

class TestLayer : public Layer
{
public:
    LAYER_NAME(TestLayer)

    void OnAttach()
    {   
        std::cout << "Attached Layer with name " << GetLayerName() << std::endl;
    }   

    void OnDetach()
    {
        std::cout << "Detached Layer with name " << GetLayerName() << std::endl;
    }


    void OnEvent(const Event& event)
    {
        std::cout << event << std::endl;
    }

    void OnUpdate()
    {

    }
    
    void OnRender()
    {

    }
};