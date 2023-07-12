#pragma once
#include <string>

class Component
{
private:
    virtual std::string GetName()
    {
        return "Component";
    }
};