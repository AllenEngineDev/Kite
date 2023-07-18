#include "Events/EventManager.h"

#include "ImGuiLayer.h"
#include "GUI/TransformComponentGUI.h"

#include <string>
#include <functional>
#include <sstream>

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
    EventManager::AddCallback(EventType::EntitySelectedEvent, 
        std::bind(&ImGuiLayer::OnEntitySelected, this, std::placeholders::_1), true);

    // Debug Event Callbacks
    EventManager::AddCallback(EventType::MousePressedEvent, 
        std::bind(&ImGuiLayer::OnMousePressed, this, std::placeholders::_1), true);

    // Setting up ImGUI window names
    m_MainViewport = MainViewportGUI("Main Viewport");
    m_ConsoleGUI = ConsoleGUI("Console Output");
    m_EntityListGUI = EntityListGUI("Entity List");
    m_PropertiesGUI = PropertiesGUI("Properties");
}



void ImGuiLayer::SetupGui()
{
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(),
         ImGuiDockNodeFlags_PassthruCentralNode);

    // Main Viewport
    m_MainViewport.Begin();
    // Calculating the viewport rect so that the Renderer knows where to render
    m_ViewportRect = m_MainViewport.CalculateViewportRect();
    m_MainViewport.End();
    EventManager::EventHappened(GuiViewportChange(m_ViewportRect));

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


void ImGuiLayer::OnEntitySelected(Event &event)
{
    const auto& entityEvent = static_cast<const EntitySelectedEvent&>(event);
    Entity* entity = entityEvent.GetEntity();
    m_GUIData.SetSelectedEntity(entity);
    m_PropertiesGUI.Components.SetSelectedEntity(entity);
}

void ImGuiLayer::OnMousePressed(Event &event)
{
    
    const auto& mouseEvent = static_cast<const MousePressedEvent&>(event);
    Vector2<int> pressedPosition = mouseEvent.GetPressedPosition();
    // auto pp = Vector2<float>(pressedPosition.X * 0.68, pressedPosition.Y * 0.68);
    std::stringstream ss;
    ss << "Mouse Pressed At (" << pressedPosition.X << ", " << pressedPosition.Y << " )";
    m_ConsoleGUI.AddOutput(ss.str());
    
    // Checks if the mouse press was in the game viewport
    // If it was, we don't need to set it handled because the press should be given to the game layer
    bool pressedInMainViewport = m_ViewportRect.IsPositionInBounds(mouseEvent.GetWindowPressedPosition());
    if (!pressedInMainViewport) 
        event.SetHandled(true);
    else
        m_PropertiesGUI.Components.SetSelectedEntity(nullptr);
        m_GUIData.SetSelectedEntity(nullptr); // This will be called before EntitySelectedEvent
    // This is just to ensure in cases where there is no entity selected, this is still nullptr
}


void ImGuiLayer::OnUpdate()
{
    SetupGui();
}

void ImGuiLayer::OnRender()
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
}
