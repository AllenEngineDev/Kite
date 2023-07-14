#pragma once
#include "Renderer.h"
#include "Layers/Layer.h"
#include "Game/Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class GameLayer : public Layer
{
public:
    Game game;
    LAYER_NAME(GameLayer)

    // SDL, SDL_IMG, SDL Renderer, IMGUI Initialization code 
    void OnAttach() override;
    void OnDetach() override;

    void OnEvent(const Event& event) override;

    void OnUpdate() override;
    void OnRender() override;

    static SDL_Window* GetWindow() { return m_Window; };
    static Renderer& GetRenderer() { return m_Renderer; }
    static void AddEntityToWorld(Entity* entity);
    void RenderAllEntities();
private:
    bool m_Running;

    static std::vector<Entity*> m_Entities;
    static SDL_Window* m_Window;
    static Renderer m_Renderer;

    void InitWindow(const char* title, unsigned int width, unsigned int height);
    void InitRenderer();

};