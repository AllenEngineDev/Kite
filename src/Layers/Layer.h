#pragma once
#include "Events/EventManager.h"
#include <iostream>
#include <string>

// Use this on layers you want to use GetLayerName() on 
#define LAYER_NAME(x) std::string GetLayerName() override { return #x; }

// Interface for Layer subclasses
class Layer
{  
public:
    virtual void OnAttach() = 0;
    virtual void OnDetach() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnRender(SDL_Renderer* renderer) = 0;    
    virtual std::string GetLayerName() { return "DefaultLayerName"; }
};

