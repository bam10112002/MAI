#pragma once
#include <functional>
#include <utility>
#include "Matrix.h"

class Find
{
private:
	Matrix* matrix;
	void min_waight(Coord& tmp, Coord& baseCoord, double& baseWaight);

public:
	enum class  Way { UP, DOUN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOUNLEFT, DOUNRIGHT };

	Find() {};
	Find(Matrix* _matrix);
	std::vector<Coord> operator()(Coord start, Coord target, std::function<void(Coord, Way)> collback );

private:
	std::vector<Coord> A_star(Coord start, Coord target, std::function<void(Coord, Way)> collback);
	std::vector<Coord> Dijkstra(Coord start, Coord target, std::function<void(Coord, Way)> collback);
};

