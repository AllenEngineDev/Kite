#include "ImGuiLayer.h"

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
    ImGui::Begin("Transform Component!");
    float targetPosition[] = { 0.0f, 0.0f };
    ImGui::SliderFloat2("Position", targetPosition, 0.0, 800.0);
    ImGui::Button("Hello!");
    ImGui::End();
}


void ImGuiLayer::OnEvent(const Event &event)
{
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
