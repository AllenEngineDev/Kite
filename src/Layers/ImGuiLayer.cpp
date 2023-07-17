#include "IDManager.h"
#include "Events/EventManager.h"

#include "ImGuiLayer.h"
#include "GUI/TransformComponentGUI.h"
#include "Components/IDComponent.h"


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
    //ImGui::StyleColorsLight();

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
}



void ImGuiLayer::SetupGui()
{
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(),
         ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::Begin("Main Viewport");
    ImVec2 vMin = ImGui::GetWindowContentRegionMin();
    ImVec2 vMax = ImGui::GetWindowContentRegionMax();
    vMin.x += ImGui::GetWindowPos().x;
    vMin.y += ImGui::GetWindowPos().y;
    vMax.x += ImGui::GetWindowPos().x;
    vMax.y += ImGui::GetWindowPos().y;

    m_ViewportRect.Recalculate(vMin, vMax);
    EventManager::EventHappened(GuiViewportChange(m_ViewportRect));

    ImGui::End();

    ImGui::Begin("Console");
    ImGui::Text("Rect Position: (%.2f, %.2f)", m_ViewportRect.X, m_ViewportRect.Y);
    ImGui::Text("Rect Size: (%.2f, %.2f)", m_ViewportRect.Width, m_ViewportRect.Height);
    for (std::string& output : m_GUIData.ConsoleOutputs)
        ImGui::Text(output.c_str());
    ImGui::End();

    ImGui::Begin("Entity list");
    ImGui::End();

    if (m_GUIData.IsEntitySelected())
    {
        ImGui::Begin("Properties");
        if (m_GUIData.Components.Transform != nullptr)
            TransformComponentGui transformGui(m_GUIData.Components.Transform);
     
        ImGui::End();
    }
    else 
    {
        ImGui::Begin("Properties");
        ImGui::Text("No entity selected");
        ImGui::End();
    }
}


void ImGuiLayer::OnEntitySelected(Event &event)
{
    const auto& entityEvent = static_cast<const EntitySelectedEvent&>(event);
    m_GUIData.SetSelectedEntity(entityEvent.GetEntity());
}

void ImGuiLayer::OnMousePressed(Event &event)
{
    
    const auto& mouseEvent = static_cast<const MousePressedEvent&>(event);
    Vector2<int> pressedPosition = mouseEvent.GetPressedPosition();
    // auto pp = Vector2<float>(pressedPosition.X * 0.68, pressedPosition.Y * 0.68);
    std::stringstream ss;
    ss << "Mouse Pressed At (" << pressedPosition.X << ", " << pressedPosition.Y << " )";
    m_GUIData.ConsoleOutputs.emplace_back(ss.str());
    
    // Checks if the mouse press was in the game viewport
    // If it was, we don't need to set it handled because the press should be given to the game layer
    bool pressedInMainViewport = m_ViewportRect.IsPositionInBounds(mouseEvent.GetWindowPressedPosition());
    if (!pressedInMainViewport) 
        event.SetHandled(true);
    else
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

// Called when the ImGUI Layer is attached to the Engine Layer Stack
// Contains initialization code as well as setting up EventCallbacks
void ImGuiLayer::OnDetach()
{
    // ImGUI Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}
