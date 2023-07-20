#include "LayerStack.h"
#include "Core.h"

#include <iostream>

// Attaches a layer to the layer stack and runs the OnAttach function on it
void LayerStack::AttachLayer(Layer* layer)
{
    m_Layers.emplace_back(layer);
    layer->OnAttach();
    std::cout << "Layer named " << layer->GetLayerName() << 
    " attached to the layer stack. " << std::endl;
}

// Detaches a layer from the layer stack and runs the OnDetach function on it
void LayerStack::DetachLayer(Layer* layer)
{
    auto layerIterator = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (layerIterator != m_Layers.end()) 
    {
        layer->OnDetach();
        m_Layers.erase(layerIterator);
    }
    else 
    {
        // If layer was not found in m_Layers
        ASSERT(true, "ERROR: TRIED TO DETACH LAYER THAT HASN'T BEEN ATTACHED YET")
    }

    
}

// Runs OnUpdate on all the layers
void LayerStack::UpdateLayers()
{
    for (Layer* layer : m_Layers)
        layer->OnUpdate();
}


// Runs OnRender on all the layers
void LayerStack::RenderLayers(SDL_Renderer* renderer)
{
    for (auto layerIter = m_Layers.rbegin(); layerIter != m_Layers.rend(); ++layerIter)
        (*layerIter)->OnRender(renderer);
}


// Detaches every single layer. Call this at the end
void LayerStack::DetachAllLayers()
{
    for (Layer* layer : m_Layers)
    {
        layer->OnDetach();
        std::cout << "Layer named " << layer->GetLayerName() << 
        " detached from the layer stack and will be deleted. " << std::endl;
        delete layer; // All layers will be created on the heap
    }

    m_Layers.clear();
}