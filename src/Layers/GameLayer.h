#pragma once

#include "Renderer.h"
#include "Layers/Layer.h"
#include "Scene/Scene.h"
#include "Rect.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Wrapper around the Game class
// Passes events along to the actual Game representation in the editor
class GameLayer : public Layer
{
public:
    GameLayer(SDL_Renderer* renderer)
        : m_Renderer(renderer) { }

    // SDL, SDL_IMG, SDL Renderer, IMGUI Initialization code 
    void OnAttach() override;
    void OnDetach() override;

    // Event callbacks
    void OnKeyDown(Event& event);
    void OnMousePressed(Event& event);
    void OnMouseReleased(Event& event);
    void OnMouseMotion(Event& event);

    void OnUpdate() override;
    void OnRender(SDL_Renderer* renderer) override;
    Scene* GetScene() const { return m_Scene; }

    LAYER_NAME(GameLayer)
private:
    Scene* m_Scene;
    Rect m_CameraRect;
    bool m_IsCameraDragged = false;
    Vector2<int> m_DragStartPosition;
    bool m_Running;
    SDL_Renderer* m_Renderer;
};