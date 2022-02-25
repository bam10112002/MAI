#pragma once
#include <string>
#include <fstream>
#include "Find.h"
#include "Matrix.h"

class Map
{
private:
	std::string name;

public:
	Matrix matrix;
	Find find;
	Map(std::string fileName);
	std::string getName();

};

