#include "pch.h"
#include <fstream>
#include "DataReader.h"

void DataReader::LoadXMLFile(const std::string& filename)
{
    doc.LoadFile(filename.c_str());
    assert(!doc.Error());
}

std::vector<DataReader::EntityComponents> DataReader::GetEntities()
{
    std::vector<DataReader::EntityComponents> entities;
    auto entityElements = doc.FirstChildElement("entities");
    if (entityElements)
    {
        auto entityElement = entityElements->FirstChildElement("entity");
        while (entityElement)
        {
            auto& entity = entities.emplace_back();
            auto component = entityElement->FirstChildElement();
            while (component)
            {
                auto text = component->GetText();
                if (!text)
                    entity.emplace_back(component->Name(), "");
                else
                    entity.emplace_back(component->Name(), text);

                component = component->NextSiblingElement();
            }
            entityElement = entityElement->NextSiblingElement("entity");
        }
    }
    return entities;
}
