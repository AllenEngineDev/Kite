#include <string>
#include <fstream>

#include "Components/Component.h"
#include "Scene.h"
#include "Core.h"

class SceneSerializer
{
private:
    SceneSerializer() = default;
public:
    static SceneSerializer Get()
    {
        static SceneSerializer scnSerializer;
        return scnSerializer;
    }

    void SerializeScene(const Scene& scene, const std::string& filepath);
    Scene* DeserializeScene(const std::string& filepath);
};