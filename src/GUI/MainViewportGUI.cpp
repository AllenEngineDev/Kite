#include "MainViewportGUI.h"

Rect MainViewportGUI::CalculateViewportRect()
{
    ImVec2 vMin = ImGui::GetWindowContentRegionMin();
    ImVec2 vMax = ImGui::GetWindowContentRegionMax();
    vMin.x += ImGui::GetWindowPos().x;
    vMin.y += ImGui::GetWindowPos().y;
    vMax.x += ImGui::GetWindowPos().x;
    vMax.y += ImGui::GetWindowPos().y;

    Rect viewportRect;

    viewportRect.Recalculate(vMin, vMax);

    return viewportRect;
}