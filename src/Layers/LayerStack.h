#pragma once
#include <vector>
#include "Layers/Layer.h"

class LayerStack
{
public:
    void AttachLayer(Layer* layer);
    void DetachLayer(Layer*layer);
private:
    std::vector<Layer*> m_Layers;
};