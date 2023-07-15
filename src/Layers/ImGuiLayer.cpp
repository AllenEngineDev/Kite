#include "ImGuiLayer.h"
#include "IDManager.h"
#include "Components/IDComponent.h"
#include <string>
#include <sstream>

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
}

void ImGuiLayer::SetupGui()
{
    ImGui::Begin("Transform Components");

    // Iterating through the ID to Entity map 
    for (auto const& [id, entity] : IDManager::Get().GetMap())
    {
        auto transform = entity->GetComponent<TransformComponent>();
        auto idComponent = entity->GetComponent<IDComponent>();

        std::stringstream ss;
        ss << "Transform Component for Entity with ID: ";
        ss << idComponent->GetID();

        ImGui::Text(ss.str().c_str());

        // Position
        ImGui::Text("Position:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0, 0, 1, 1), "%d, %d",
            transform->GetPosition().X,
            transform->GetPosition().Y);

        // Scale
        ImGui::Text("Scale:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0, 1, 0, 1), "%d, %d",
            transform->GetScale().X,
            transform->GetScale().Y);

        // Rotation
        ImGui::Text("Rotation:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "%.2f", transform->GetRotationDegrees());

    }

    ImGui::End();

}


void ImGuiLayer::OnEvent(const Event &event)
{
    std::cout << event.ToString() << std::endl;
}

void ImGuiLayer::OnUpdate()
{
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


void ImGuiLayer::OnDetach()
{
    // ImGUI Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}
