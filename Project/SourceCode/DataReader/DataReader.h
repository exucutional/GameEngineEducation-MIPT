#pragma once
#include "pch.h"
#include <string>
#include <vector>
#include <cassert>
#include <array>
#include <sstream>
#include "tinyxml2.h"

class DATAREADER_API DataReader
{
public:
    void LoadXMLFile(const std::string& filename);
    using EntityComponents = std::vector<std::pair<std::string, std::string>>;
    std::vector<EntityComponents> GetEntities();
    template <int n>
    static std::array<float, n> StringToVec(const std::string& s);
private:
    tinyxml2::XMLDocument doc;
};

template <int n>
static std::array<float, n> DataReader::StringToVec(const std::string& s)
{
    std::array<float, n> vec = { 0.0f };
    std::stringstream ss(s);
    std::string token;
    int i = 0;
    while (std::getline(ss, token, ' ') && i < n)
    {
        vec[i++] = (float)std::stof(token);
    }
    return vec;
}
