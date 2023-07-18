#include "ConsoleGUI.h"


void ConsoleGUI::AddOutput(const std::string& output)
{
    m_Outputs.emplace_back(output);
}

void ConsoleGUI::PrintOutputs()
{
    // Loop through and print all outputs
    for (std::string& output : m_Outputs)
        ImGui::Text(output.c_str());
}