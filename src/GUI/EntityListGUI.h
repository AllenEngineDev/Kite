#include "GUIWindow.h"

class EntityListGUI : public GUIWindow
{
public:
    EntityListGUI()
        : GUIWindow("Entity List") { }
    EntityListGUI(const char* name)
        : GUIWindow(name) { }
};