#include "Matrix.h"


//Cell
std::map<std::string, Cell_Type> Cell::convert =
{
	std::pair<std::string, Cell_Type>(std::string("EMPTY") , Cell_Type::EMPTY),
	std::pair<std::string, Cell_Type>(std::string("WALL")  , Cell_Type::WALL),
	std::pair<std::string, Cell_Type>(std::string("FOREST"), Cell_Type::FOREST)
};

int Cell::calculate_approx(const Coord& cell_coord, const Coord& target_coord)
{
	return (abs(cell_coord.x - target_coord.x) + abs(cell_coord.y - target_coord.y)) * int(Cell_Type::EMPTY);
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

double Cell::get_waight()
{
	return waight;
}

double Cell::get_distanse() const
{
	return distanse;
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

int Cell::change_waight(const double& new_waight)
{
	if (waight > new_waight || waight == -1)
	{
		waight = new_waight;
	}
	return waight;
}

double Cell::set_distanse(const Coord& cell_coord, const Coord& target_coord, const double& last_distanse, const double coeff)
{
	double new_distanse;
	new_distanse = last_distanse + int(type)*coeff;
	approx = calculate_approx(cell_coord, target_coord);
	waight = change_waight(new_distanse + approx);
	if (waight == new_distanse + approx)
		distanse = new_distanse;
	return waight;
}

Matrix::Matrix(const nlohmann::json& JSON)
{
	
	std::vector<std::vector<std::string>> vector_matrix = JSON["matrix"].get<std::vector<std::vector<std::string>>>();
	height = vector_matrix.size();
	width = vector_matrix[0].size();
	
	matrix = new Cell * [width];
	for (int i = 0; i < height; i++)
	{
		matrix[i] = new Cell[height];
		for (int j = 0; j < width; j++)
		{
			matrix[i][j] = Cell(Cell::convert[vector_matrix[i][j]]);	//TODO: добавить обработку неправильного ввода из файла
		}
	}
}

void Matrix::printMatrix()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout << matrix[i][j].get_cost() << "\t";
		}
		std::cout << std::endl;
	}
}

bool Matrix2::is_valid_coord(const Coord coord, const std::vector<std::vector<std::string>>& matrix_vec)
{
	if (coord.x >= 0 && coord.y >= 0 && coord.x < width && coord.y < height && int(convert[matrix_vec[coord.y][coord.x]]) > 0)
	{
		return true;
	}
	return false;
}

Matrix2::Matrix2(nlohmann::json JSON_matr)
{
	std::vector<std::vector<std::string>> vector_matrix = JSON_matr["matrix"].get<std::vector<std::vector<std::string>>>();
	height = vector_matrix.size();
	width = vector_matrix[0].size();

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (this->is_valid_coord(Coord(j,i), vector_matrix)
			{

			}
		}
	}
}

std::map<std::string, Cell_Type> Matrix2::convert =
{
	std::pair<std::string, Cell_Type>(std::string("EMPTY") , Cell_Type::EMPTY),
	std::pair<std::string, Cell_Type>(std::string("WALL")  , Cell_Type::WALL),
	std::pair<std::string, Cell_Type>(std::string("FOREST"), Cell_Type::FOREST)
};
