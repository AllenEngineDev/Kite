#pragma once
#include <string>

class Component
{
    virtual std::string GetName()
    {
        return "Component";
    }
};