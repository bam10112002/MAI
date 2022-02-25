#include "Map.h"

Map::Map(std::string fileName)
{
	nlohmann::json j{};
	std::ifstream jsonFile(fileName);
	jsonFile >> j;

	name = j["name"].get<std::string>();
	matrix = Matrix(j);
	find = Find(&matrix);
}

std::string Map::getName()
{
	return name;
}
