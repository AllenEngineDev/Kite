#include <memory>
#include <imgui.h>

#include "Components/TransformComponent.h"


class TransformComponentGui
{
public:
    TransformComponentGui(std::shared_ptr<TransformComponent> const transform);
private:
    void AddPositionGUI(std::shared_ptr<TransformComponent> const transform);
    void AddScaleGUI(std::shared_ptr<TransformComponent> const transform);
    void AddRotationGUI(std::shared_ptr<TransformComponent> const transform);
};
