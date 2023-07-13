#include "LayerStack.h"

// Attaches a layer to the layer stack and runs the OnAttach function on it
void LayerStack::AttachLayer(Layer* layer)
{
    m_Layers.emplace_back(layer);
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
}