#pragma once
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "json/single_include/nlohmann/json.hpp"

enum class Cell_Type { NONE = 0, EMPTY = 10, WALL = -1, FOREST = 20 };

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
		if (x == r.x && y == r.y) { return false; }
		return true;
	}
	friend bool operator > (const Coord& l ,const Coord& r)
	{
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
	double get_waight();
	double get_distanse() const;
	int get_cost() const;
	int change_waight(const double& new_waight);
	double set_distanse(const Coord& cell_coord, const Coord& target_coord, const double& last_distanse, const double coeff = 1.0);
};

class Matrix
{
	friend class Find;	

protected:
	int width;
	int height;
	Cell** matrix;

public:
	Matrix(const nlohmann::json& JSON);
	Matrix() {};
	void printMatrix();
};


class Matrix2
{
	static std::map<std::string, Cell_Type> convert;
	int width;
	int height;
	std::map<Coord, std::vector<Coord>> matr;
	bool is_valid_coord(const Coord coord, const std::vector<std::vector<std::string>>& mart);

public:
	Matrix2(nlohmann::json JSON_matr);

};