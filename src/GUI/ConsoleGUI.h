#include <vector>
#include <string>

#include "GUIWindow.h"

class ConsoleGUI : public GUIWindow
{
public:
    ConsoleGUI()
        : GUIWindow("Console") { }
    ConsoleGUI(const char* name)
        : GUIWindow(name) { }
    void PrintOutputs();
    void AddOutput(const std::string& output);
private:
    std::vector<std::string> m_Outputs;
};