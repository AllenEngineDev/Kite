#include <yaml-cpp/yaml.h>
#include <SDL2/SDL.h>

#include "SceneSerializer.h"
#include "Entities/Entity.h"
#include "Components/SpriteComponent.h"
#include "Components/IDComponent.h"
#include "Components/TransformComponent.h"


// TODO: Use own file format
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
            component->Serialize(out);
        }

        out << YAML::EndMap; // End the map for the entity's components
        out << YAML::EndMap; // End the map for the entity
    }

    out << YAML::EndSeq;
    out << YAML::EndMap;

    std::ofstream outfile(filepath);

    ASSERT(outfile.is_open(), 
        "[ASSERTION FAILED]: [FAILED TO OPEN FILE AT FILEPATH]: " << filepath);

    outfile << out.c_str();
    outfile.close();
}

Scene* SceneSerializer::DeserializeScene(SDL_Renderer* renderer, const std::string& filepath)
{
    YAML::Node config = YAML::LoadFile(filepath);
    Scene* scene = new Scene;
    scene->SetName(config["SceneName"].as<std::string>().c_str());

    YAML::Node entities = config["Entities"];

    // TODO: This is why I want to use my own file format
    // I HATE THIS 3 LAYER FOR LOOP 
    // For the sequence of entities
    for (size_t i = 0; i < entities.size(); i++)
    {
        // Scene will take ownership and delete it
        Entity* entity = new Entity;
        // For the entity map
        for (YAML::const_iterator it = entities[i].begin(); it != entities[i].end();
            it++)
        {
            for (YAML::const_iterator it2 = it->second.begin(); it2 != it->second.end();
            it2++)
            {
                std::string componentName =  it2->first.as<std::string>();
                YAML::Node data = it2->second;

                if (componentName == "IDComponent")
                {
                    uint64_t id = data["ID"].as<uint64_t>();

                    entity->AddComponentConstruct<IDComponent>(id);
                }
                else if (componentName == "SpriteComponent")
                {
                    std::string filepath = data["Filepath"].as<std::string>();

                    entity->AddComponentConstruct<SpriteComponent>(renderer, filepath.c_str());
                }
                else if (componentName == "TransformComponent")
                {
                    int posX = data["Position"][0].as<int>();
                    int posY = data["Position"][1].as<int>();
                    int scaleX = data["Scale"][0].as<int>();
                    int scaleY = data["Scale"][1].as<int>();
                    float rotDegrees = data["Rotation"].as<float>();

                    entity->AddComponentConstruct<TransformComponent>(
                        Vector2<int>(posX, posY),
                        Vector2<int>(scaleX, scaleY),
                        rotDegrees
                        );
                }
            }
        }

        scene->AddEntityToWorld(entity);
    }        

    return scene;
}
