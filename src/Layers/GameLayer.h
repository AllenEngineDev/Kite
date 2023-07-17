#pragma once
#include "Renderer.h"
#include "Layers/Layer.h"
#include "Game/Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Wrapper around the Game class
// Passes events along to the actual Game representation in the editor
class GameLayer : public Layer
{
public:
    Game game;
    LAYER_NAME(GameLayer)

    // SDL, SDL_IMG, SDL Renderer, IMGUI Initialization code 
    void OnAttach() override;
    void OnDetach() override;

    void OnKeyDown(const Event& event);
    void OnMousePressed(const Event& event);

    void OnUpdate() override;
    void OnRender() override;

private:
    bool m_Running;
};