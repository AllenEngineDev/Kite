#include <string>
#include <functional>
#include <sstream>

#include <imgui_internal.h>

#include "Events/EventManager.h"

#include "ImGuiLayer.h"
#include "GUI/TransformComponentGUI.h"
    

// Called when the ImGUI Layer is attached to the Engine Layer Stack
// Contains initialization code as well as setting up EventCallbacks
void ImGuiLayer::OnAttach()
{
    // ImGUI Initialization
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls


    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(m_Window, m_Renderer);
    ImGui_ImplSDLRenderer2_Init(m_Renderer);

    // Setting up fonts
    // You can change the font ImGUI uses by using ImGui::PushFont(font) -> Must be called after ImGui::NewFrame().
    // I.E in SetupGui()
    ImFont* font = io.Fonts->AddFontFromFileTTF("../res/fonts/Roboto-Regular.ttf", 16.0f);

    // Enabling docking
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;


    // Setting up Event callbacks
    EventManager::Get().AddCallback(EventType::EntitySelectedEvent, 
        std::bind(&ImGuiLayer::OnEntitySelected, this, std::placeholders::_1), true);

    // Debug Event Callbacks
    EventManager::Get().AddCallback(EventType::MousePressedEvent, 
        std::bind(&ImGuiLayer::OnMousePressed, this, std::placeholders::_1), true);

    // Setting up ImGUI window names
    m_MainViewport = MainViewportGUI("Main Viewport");
    m_ConsoleGUI = ConsoleGUI("Console Output");
    m_EntityListGUI = EntityListGUI("Entity List");
    m_PropertiesGUI = PropertiesGUI("Properties");
}



void ImGuiLayer::SetupGui()
{
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_NoTabBar);
    // Main Viewport
    m_MainViewport.Begin();
    // Calculating the viewport rect so that the Renderer knows where to render
    m_ViewportRect = m_MainViewport.CalculateViewportRect();
    m_MainViewport.End();
    EventManager::Get().EventHappened(GuiViewportChange(m_ViewportRect));

    // Play bar
    ImGui::Begin("Play!");
    // Get the window size
    ImVec2 windowSize = ImGui::GetWindowSize();

    // Get the size of the button
    ImVec2 buttonSize(75, 25); // Adjust the size according to your preference

    // Calculate the position to center the button
    ImVec2 buttonPosition(
        (windowSize.x - buttonSize.x) * 0.5f,
        (windowSize.y - buttonSize.y) * 0.5f
    );

    // Set the cursor position to center the button
    ImGui::SetCursorPos(buttonPosition);

    // Create the centered button
    if (ImGui::Button("Play", buttonSize)) 
    {
        // Handle button click event
        // Add your action here
        m_ConsoleGUI.AddOutput("Play button pressed!");
        EventManager::Get().EventHappened(PlayButtonPressedEvent());
    }

    ImGui::End();

    // Console GUI
    m_ConsoleGUI.Begin();
    m_ConsoleGUI.PrintOutputs();
    m_ConsoleGUI.End();

    m_EntityListGUI.Begin();
    // TODO: Make this display all entities -> m_EntityListGUI.DisplayAllEntities();
    m_EntityListGUI.End();

    // Properties GUI
    m_PropertiesGUI.Begin();
    m_PropertiesGUI.DisplayProperties();
    m_PropertiesGUI.End();
}


// TODO: Fix this, we shouldn't have to check if entity is nullptr on an entity selected event
// We are doing this in Game.cpp -> CheckForMouseCollisions()
// IIRC, we make it possible for entity to be nullptr for the properties window to have a nullptr entity in which case it doesn't have to 
// render any properties
void ImGuiLayer::OnEntitySelected(Event &event)
{
    const auto& entityEvent = static_cast<const EntitySelectedEvent&>(event);
    Entity* entity = entityEvent.GetEntity();
    m_PropertiesGUI.Components.SetSelectedEntity(entity);


}

void ImGuiLayer::OnMousePressed(Event &event)
{
    
    const auto& mouseEvent = static_cast<const MousePressedEvent&>(event);
    Vector2<int> pressedPosition = mouseEvent.GetPressedPosition();

    // Checks if the mouse press was in the game viewport
    // If it was, we don't need to set it handled because the press should be given to the game layer
    bool pressedInMainViewport = m_ViewportRect.IsPositionInBounds(mouseEvent.GetWindowPressedPosition());
    if (!pressedInMainViewport) 
        event.SetHandled(true);
    else
        m_PropertiesGUI.Components.SetSelectedEntity(nullptr);
         // This will be called before EntitySelectedEvent
    // This is just to ensure in cases where there is no entity selected, this is still nullptr
}


void ImGuiLayer::OnUpdate()
{
    SetupGui();
}

void ImGuiLayer::OnRender(SDL_Renderer* renderer)
{
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::StartNewFrame()
{
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

// Called when the ImGUI layer is removed from the layer stack
// Contains cleanup code
void ImGuiLayer::OnDetach()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    EventManager::Get().RemoveCallback(EventType::EntitySelectedEvent, 
        std::bind(&ImGuiLayer::OnEntitySelected, this, std::placeholders::_1));

    EventManager::Get().RemoveCallback(EventType::MousePressedEvent, 
        std::bind(&ImGuiLayer::OnMousePressed, this, std::placeholders::_1));
}
