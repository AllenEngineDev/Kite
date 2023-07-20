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
    GameLayer(SDL_Renderer* renderer)
        : m_Renderer(renderer) { }

    Game game;

    // SDL, SDL_IMG, SDL Renderer, IMGUI Initialization code 
    void OnAttach() override;
    void OnDetach() override;

    void OnKeyDown(Event& event);
    void OnMousePressed(Event& event);

    void OnUpdate() override;
    void OnRender(SDL_Renderer* renderer) override;
    LAYER_NAME(GameLayer)

private:
    bool m_Running;
    SDL_Renderer* m_Renderer;
};