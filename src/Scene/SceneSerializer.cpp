#include "SceneSerializer.h"
#include <yaml-cpp/yaml.h>

// void SceneSerializer::SerializeComponent(const std::shared_ptr<Component>& component)
// {
//     out << YAML::BeginMap; 

//     out << YAML::Key << "Key1";
//     out << YAML::Value << "Key value";

//     out << YAML::EndMap;
// }

void SceneSerializer::SerializeScene(const Scene& scene, const std::string& filepath)
{
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "SceneName";
    out << YAML::Value << scene.GetName();

    out << YAML::Key << "Entities";
    out << YAML::BeginSeq;

    for (const Entity* entity : scene.GetEntities())
    {
        out << YAML::BeginMap; // Begin the map for the entity
        out << YAML::Key << entity->GetName();

        out << YAML::Value << YAML::BeginMap; // Begin the map for the entity's components

        for (const std::shared_ptr<Component>& component : entity->GetComponents())
        {
            out << YAML::Key << component->GetName();
            // SerializeComponent(out, component);
            component->Serialize(out);
        }

        out << YAML::EndMap; // End the map for the entity's components
        out << YAML::EndMap; // End the map for the entity
    }

    out << YAML::EndSeq;
    out << YAML::EndMap;

    std::ofstream outfile(filepath);

    ASSERT(outfile.is_open(), 
        "[ASSERTION FAILED]: FAILED TO OPEN FILE AT FILEPATH " << filepath);

    outfile << out.c_str();
    outfile.close();
}