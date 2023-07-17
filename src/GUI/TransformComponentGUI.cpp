#include "GUI/TransformComponentGUI.h"

TransformComponentGui::TransformComponentGui(std::shared_ptr<TransformComponent> const transform)
{
    AddPositionGUI(transform);
    AddScaleGUI(transform);
    AddRotationGUI(transform);
}

void TransformComponentGui::AddPositionGUI(std::shared_ptr<TransformComponent> const transform)
{   
    ImGui::Text("Position:");
    ImGui::SameLine();
    int position[2] = { transform->GetPosition().X, transform->GetPosition().Y };
    if (ImGui::DragInt2("##Position", position))
        transform->SetPosition({ position[0], position[1] });
}

void TransformComponentGui::AddScaleGUI(std::shared_ptr<TransformComponent> const transform)
{
    // Scale
    ImGui::Text("Scale:");
    ImGui::SameLine();
    int scale[2] = { transform->GetScale().X , transform->GetScale().Y };
    if (ImGui::DragInt2("##Scale", scale))
        transform->SetScale({ scale[0], scale[1] });
}

void TransformComponentGui::AddRotationGUI(std::shared_ptr<TransformComponent> const transform)
{
    // Rotation
    ImGui::Text("Rotation:");
    ImGui::SameLine();
    float rotation = transform->GetRotationDegrees();
    if (ImGui::DragFloat("##Rotation", &rotation))
        transform->SetRotationDegrees(rotation);
}