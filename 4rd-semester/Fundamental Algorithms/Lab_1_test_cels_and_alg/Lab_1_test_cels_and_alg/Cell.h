#pragma once
#include <cmath>
#include <iostream>
#include "json/single_include/nlohmann/json.hpp"
#include <fstream>
#include <vector>
#include <map>

enum class Cell_Type {NONE = 0, EMPTY = 10, WALL = -1, FOREST = 20 };
class Coord
{
public:
	int x, y;
	Coord() {}
	Coord(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
	bool operator != (const Coord& r)const
	{
		if (x == r.x && y == r.y) { return false;}
		return true;
	}
};

class Cell
{
private: 
	Cell_Type type;
	int approx;
	double waight;
	double distanse;

	int calculate_approx(const Coord& cell_coord, const Coord& target_coord);

public:
	static std::map<std::string, Cell_Type> convert;

	Cell();
	Cell(const Cell_Type& t);
	bool is_passable() const; 
	int get_cost() const;
	int change_waight(const double & new_waight);
	double set_distanse(const Coord& cell_coord, const Coord& target_coord, const double& last_distanse);

};


class Map
{
private:
	int width;
	int height;
	std::string name;
	Cell** matrix;

public:
	enum class  Way { UP, DOUN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOUNLEFT, DOUNRIGHT };

	Map(char* file_name);
	std::string get_name();
	//TODO: деструктор
};





