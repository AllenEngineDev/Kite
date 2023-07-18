#include "GUI/PropertiesGUI.h"
#include "GUI/TransformComponentGUI.h"

void PropertiesGUI::DisplayProperties()
{
    if (Components.IsEntitySelected())
    {
        TransformComponentGui transformGui(Components.Transform);
    }
}