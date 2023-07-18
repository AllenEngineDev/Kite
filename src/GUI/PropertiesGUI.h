#include <memory>

#include "Entities/Entity.h"
#include "GUIWindow.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"


struct EntityComponents
{
    Entity* SelectedEntity = nullptr;
    std::shared_ptr<TransformComponent> Transform;
    std::shared_ptr<SpriteComponent> Sprite;

    // Use this to select entity so we can cache the components inside it
    void SetSelectedEntity(Entity* entity)
    {
        SelectedEntity = entity;
        // SetSelectedEntity(nullptr) is valid (this conveys that no entity is selected)
        // We don't want to run GetComponent() on nullptr, so we return
        if (entity == nullptr)
            return;
        Transform = SelectedEntity->GetComponent<TransformComponent>();
        Sprite = SelectedEntity->GetComponent<SpriteComponent>();
    }

    bool IsEntitySelected() const { return SelectedEntity != nullptr; }

};

class PropertiesGUI : public GUIWindow
{
public:
    EntityComponents Components;

    PropertiesGUI()
        : GUIWindow("Properties GUI") { }
    PropertiesGUI(const char* name)
        : GUIWindow(name) { }
    void DisplayProperties();
    
};