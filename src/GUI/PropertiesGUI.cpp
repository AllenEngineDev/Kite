#include "GUI/PropertiesGUI.h"
#include "GUI/TransformComponentGUI.h"
#include "GUI/SpriteComponentGUI.h"

void PropertiesGUI::DisplayProperties()
{
    if (Components.IsEntitySelected())
    {
        if (Components.Transform != nullptr)
            TransformComponentGui transformGui(Components.Transform);
        if (Components.Sprite != nullptr)
        {
            SpriteComponentGUI spriteGUI(Components.Sprite);
        }
    }
}