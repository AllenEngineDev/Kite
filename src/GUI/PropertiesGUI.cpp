#include "GUI/PropertiesGUI.h"
#include "GUI/TransformComponentGUI.h"

void PropertiesGUI::DisplayProperties()
{
    if (Components.IsEntitySelected())
    {
        if (Components.Transform != nullptr)
            TransformComponentGui transformGui(Components.Transform);
    }
}