#pragma once
#include <functional>
#include "Cell.h"

class Path
{
private:
	Cell** matrix;
public:
	enum class  Way{ UP, DOUN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOUNLEFT, DOUNRIGHT};
	
	Path(Cell** _matrix) { matrix = _matrix; }
	std::vector<Coord> find_path(Coord start, Coord target, std::function<void(Coord, Path::Way)> collback);

};

