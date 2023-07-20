#pragma once
#include <vector>
#include "Layers/Layer.h"

class LayerStack
{
public:
    void AttachLayer(Layer* layer);
    void DetachLayer(Layer*layer);
    void DetachAllLayers();

    void UpdateLayers();
    void RenderLayers(SDL_Renderer* renderer);
private:
    std::vector<Layer*> m_Layers;
};