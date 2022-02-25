#include "Cell.h"

std::map<std::string, Cell_Type> Cell::convert =
{
	std::pair<std::string, Cell_Type>(std::string("EMPTY") , Cell_Type::EMPTY),
	std::pair<std::string, Cell_Type>(std::string("WALL")  , Cell_Type::WALL),
	std::pair<std::string, Cell_Type>(std::string("FOREST"), Cell_Type::FOREST)
};

int Cell::calculate_approx(const Coord& cell_coord, const Coord& target_coord)
{
	return (abs(cell_coord.x - target_coord.x) + abs(cell_coord.y - target_coord.y)) * int(Cell_Type::EMPTY) ;
}

Cell::Cell()
{
	type = Cell_Type::NONE;
	approx = waight = distanse = -1;
}

Cell::Cell(const Cell_Type& t)
{
	type = t;
	approx = waight = distanse = -1;

}

bool Cell::is_passable() const
{
	if (int(type) < 0) 
			return false;
	return true;
}

int Cell::get_cost() const
{
	return int(type);
}

int Cell::change_waight(const double & new_waight)
{
	if (waight < new_waight)
	{
		waight = new_waight;
	}
	return waight;
}

double Cell::set_distanse(const Coord & cell_coord, const Coord& target_coord,const double & last_distanse)
{
	double new_distanse;
	new_distanse = last_distanse + int(type);
	approx = calculate_approx(cell_coord, target_coord);
	waight = change_waight(new_distanse + approx);
	if (waight == new_distanse + approx)
		distanse = new_distanse;
	return waight;
}










//MAP
Map::Map(char* file_name)
{
	nlohmann::json j{};
	std::ifstream jf("matrix.json");	//TODO: Добавить файл нэйм
	jf >> j;
	std::vector<std::vector<std::string>> m = j["matrix"].get<std::vector<std::vector<std::string>>>();
	
	name = j["name"].get<std::string>();
	width = m.size();
	height = m[0].size();

	matrix = new Cell*[width];
	for(int i = 0; i < width; i++)
	{
		matrix[i] = new Cell[height];
		for (int j = 0; j < height; j++)
		{
			matrix[i][j] = Cell(Cell::convert[m[i][j]]);	//TODO: добавить обработку неправильного ввода из файла
		}
	}
}

std::string Map::get_name()
{
	return name;
}

void Map::Find(Coord start, Coord target, std::function<void(Coord, Way)> collback)
{
	std::multimap<double, Coord> cels_waights;
	Coord count = start;
	Coord tmp = start;

	if (matrix[count.x- 1][count.y].is_passable() && count.x - 1 > 0)
	{
		matrix[count.x - 1][count.y].set_distanse(Coord(count.x - 1, count.y), target, 0);
		collback(Coord(count.x - 1, count.y), Way::LEFT);
	}
	if (matrix[count.x + 1][count.y].is_passable() && count.x + 1 < width)
	{
		matrix[count.x + 1][count.y].set_distanse(Coord(count.x + 1, count.y), target, 0);
		collback(Coord(count.x + 1, count.y), Way::RIGHT);
	}

	if (matrix[count.x][count.y-1].is_passable() && count.y - 1 > 0)
	{
		matrix[count.x][count.y - 1].set_distanse(Coord(count.x, count.y-1), target, 0);
		collback(Coord(count.x, count.y-1), Way::UP);
	}
	if (matrix[count.x][count.y+1].is_passable() && count.y + 1 < height)
	{
		matrix[count.x][count.y+1].set_distanse(Coord(count.x, count.y+1), target, 0);
		collback(Coord(count.x, count.y+1), Way::DOUN);
	}

	if (matrix[count.x - 1][count.y-1].is_passable() && count.x - 1 > 0 && count.y - 1 > 0)
	{
		matrix[count.x - 1][count.y-1].set_distanse(Coord(count.x - 1, count.y-1), target, 0);
		collback(Coord(count.x - 1, count.y-1), Way::UPRIGHT);
	}
	if (matrix[count.x + 1][count.y+1].is_passable() && count.x + 1 < width && count.y + 1 < height)
	{
		matrix[count.x + 1][count.y+1].set_distanse(Coord(count.x + 1, count.y+1), target, 0);
		collback(Coord(count.x + 1, count.y+1), Way::DOUNRIGHT);
	}

	if (matrix[count.x - 1][count.y + 1].is_passable() && count.x - 1 > 0 && count.y + 1 < height)
	{
		matrix[count.x - 1][count.y + 1].set_distanse(Coord(count.x - 1, count.y + 1), target, 0);
		collback(Coord(count.x - 1, count.y + 1), Way::DOUNLEFT);
	}
	if (matrix[count.x + 1][count.y - 1].is_passable() && count.x + 1 < width && count.y - 1 > 0)
	{
		matrix[count.x + 1][count.y - 1].set_distanse(Coord(count.x + 1, count.y - 1), target, 0);
		collback(Coord(count.x + 1, count.y - 1), Way::UPLEFT);
	}
}	

