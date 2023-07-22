#include <imgui.h>
#include <nfd.h>
#include "SpriteComponentGUI.h"

SpriteComponentGUI::SpriteComponentGUI
    (const std::shared_ptr<SpriteComponent> spriteComponent)
{
    ImGui::Text("Sprite Component: ");
    std::string text = "Filepath: " + spriteComponent->GetFilepath();
    ImGui::Text(text.c_str());


    // TODO: THIS IS REALLY SLOW, MAYBE BECAUSE WE ARE COMPILING IN DEBUG?
    // The .a static library files for NFD are built in Release-x64 - maybe that has 
    // something to do with it 
    if (ImGui::Button("Change Filepath?"))
    {
        std::cout << "Change filepath" << std::endl;
        nfdchar_t* outPath = NULL;
        nfdresult_t result = NFD_OpenDialog(NULL, NULL, &outPath);

        switch (result)
        {
            case NFD_OKAY:
            {   
                // TODO: Make this local to the game project directory
                std::string filepath = std::string(outPath);
                // Use path
                spriteComponent->ChangeTexture(filepath.c_str());
                free(outPath);
                break;
            }
            case NFD_CANCEL:
            {
                std::cout << "User pressed cancel";
                break;
            }
            default:
            {
                std::cout << "Error has occured with filepath " << NFD_GetError() 
                    << std::endl;
            }
        }

    }
}