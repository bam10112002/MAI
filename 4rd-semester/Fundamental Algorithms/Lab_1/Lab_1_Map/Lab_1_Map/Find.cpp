#include "Find.h"

Find::Find(Matrix* _matrix)
{
	matrix = _matrix;
}

void Find::min_waight(Coord& tmp, Coord& baseCoord, double& baseWaight)
{
	if (tmp.x >= 0 && tmp.y >= 0 && tmp.y < matrix->height && tmp.x < matrix->width && matrix->matrix[tmp.y][tmp.x].is_passable() && matrix->matrix[tmp.y][tmp.x].get_waight() != -1)
	{
		if (baseWaight == -1)
		{
			baseWaight = matrix->matrix[tmp.y][tmp.x].get_waight();
			baseCoord = Coord(tmp.x, tmp.y);
		}
		if (baseWaight > matrix->matrix[tmp.y][tmp.x].get_waight())
		{
			baseWaight = matrix->matrix[tmp.y][tmp.x].get_waight();
			baseCoord = Coord(tmp.x, tmp.y);
		}
	}
}

std::vector<Coord> Find::operator()(Coord start, Coord target, std::function<void(Coord, Way)> collback)
{
	return A_star(start, target, collback);
	//return Dijkstra(start, target, collback);
}


std::vector<Coord> Find::A_star(Coord start, Coord target, std::function<void(Coord, Way)> collback)
{
	Coord curent = start;
	std::multimap<double, Coord> cels_waights;
	//std::swap(curent.x, curent.y);
	double old_distanse = 0, old_weight;

	// Прямой ход
	while (curent != target) {
		if (curent.x - 1 >= 0 && matrix->matrix[curent.y][curent.x - 1].is_passable())
		{
			old_weight = matrix->matrix[curent.y][curent.x - 1].get_waight();
			if (old_weight != matrix->matrix[curent.y][curent.x - 1].set_distanse(Coord(curent.x - 1, curent.y), target, old_distanse))
			{
				if (collback)
					collback(Coord(curent.x - 1, curent.y), Way::LEFT);
				cels_waights.emplace(matrix->matrix[curent.y][curent.x - 1].get_waight(), Coord(curent.x - 1, curent.y));
			}
		}
		if (curent.x + 1 < matrix->width && matrix->matrix[curent.y][curent.x + 1].is_passable())
		{
			old_weight = matrix->matrix[curent.y][curent.x + 1].get_waight();
			if (old_weight != matrix->matrix[curent.y][curent.x + 1].set_distanse(Coord(curent.x + 1, curent.y), target, old_distanse))
			{
				if (collback)
					collback(Coord(curent.x + 1, curent.y), Way::RIGHT);
				cels_waights.emplace(matrix->matrix[curent.y][curent.x + 1].get_waight(), Coord(curent.x + 1, curent.y));
			}
		}

		if (curent.y - 1 >= 0 && matrix->matrix[curent.y - 1][curent.x].is_passable())
		{
			old_weight = matrix->matrix[curent.y - 1][curent.x].get_waight();
			if (old_weight != matrix->matrix[curent.y - 1][curent.x].set_distanse(Coord(curent.x, curent.y - 1), target, old_distanse)) {
				if (collback)
					collback(Coord(curent.x, curent.y - 1), Way::UP);
				cels_waights.emplace(matrix->matrix[curent.y - 1][curent.x].get_waight(), Coord(curent.x, curent.y - 1));
			}
		}
		if (curent.y + 1 < matrix->height && matrix->matrix[curent.y + 1][curent.x].is_passable())
		{
			old_weight = matrix->matrix[curent.y + 1][curent.x].get_waight();
			if (old_weight != matrix->matrix[curent.y + 1][curent.x].set_distanse(Coord(curent.x, curent.y + 1), target, old_distanse))
			{
				if (collback)
					collback(Coord(curent.x, curent.y + 1), Way::DOUN);
				cels_waights.emplace(matrix->matrix[curent.y + 1][curent.x].get_waight(), Coord(curent.x, curent.y + 1));
			}
		}

		if (curent.x - 1 >= 0 && curent.y - 1 >= 0 && matrix->matrix[curent.y - 1][curent.x - 1].is_passable())
		{
			old_weight = matrix->matrix[curent.y - 1][curent.x - 1].get_waight();
			if (old_weight != matrix->matrix[curent.y - 1][curent.x - 1].set_distanse(Coord(curent.x - 1, curent.y - 1), target, old_distanse, 1.4))
			{
				if (collback)
					collback(Coord(curent.x - 1, curent.y - 1), Way::UPRIGHT);
				cels_waights.emplace(matrix->matrix[curent.y - 1][curent.x - 1].get_waight(), Coord(curent.x - 1, curent.y - 1));
			}
		}
		if (curent.x + 1 < matrix->width && curent.y + 1 < matrix->height && matrix->matrix[curent.y + 1][curent.x + 1].is_passable())
		{
			old_weight = matrix->matrix[curent.y + 1][curent.x + 1].get_waight();
			if (old_weight != matrix->matrix[curent.y + 1][curent.x + 1].set_distanse(Coord(curent.x + 1, curent.y + 1), target, old_distanse, 1.4))
			{
				if (collback)
					collback(Coord(curent.x + 1, curent.y + 1), Way::DOUNRIGHT);
				cels_waights.emplace(matrix->matrix[curent.y + 1][curent.x + 1].get_waight(), Coord(curent.x + 1, curent.y + 1));
			}
		}

		if (curent.x - 1 >= 0 && curent.y + 1 < matrix->height && matrix->matrix[curent.y + 1][curent.x - 1].is_passable())
		{
			old_weight = matrix->matrix[curent.y + 1][curent.x - 1].get_waight();
			if (old_weight != matrix->matrix[curent.y + 1][curent.x - 1].set_distanse(Coord(curent.x - 1, curent.y + 1), target, old_distanse, 1.4))
			{
				if (collback)
					collback(Coord(curent.x - 1, curent.y + 1), Way::DOUNLEFT);
				cels_waights.emplace(matrix->matrix[curent.y + 1][curent.x - 1].get_waight(), Coord(curent.x - 1, curent.y + 1));
			}
		}
		if (curent.x + 1 < matrix->width && curent.y - 1 >= 0 && matrix->matrix[curent.y - 1][curent.x + 1].is_passable())
		{
			old_weight = matrix->matrix[curent.y - 1][curent.x + 1].get_waight();
			if (old_weight != matrix->matrix[curent.y - 1][curent.x + 1].set_distanse(Coord(curent.x + 1, curent.y - 1), target, old_distanse, 1.4))
			{
				if (collback)
					collback(Coord(curent.x + 1, curent.y - 1), Way::UPLEFT);
				cels_waights.emplace(matrix->matrix[curent.y - 1][curent.x + 1].get_waight(), Coord(curent.x + 1, curent.y - 1));
			}
		}

		if (cels_waights.size() == 0) { throw std::exception("The path to the destination was not found"); }
		auto it = (cels_waights.begin());
		curent = (*it).second;
		cels_waights.erase(it);
		old_distanse = matrix->matrix[curent.y][curent.x].get_distanse();
	}

	std::cout << old_distanse << std::endl;
	std::vector<Coord> rez;

	// Обратный ход 
	while (curent != start)
	{
		rez.push_back(curent);
		double baseWaight = -1;
		Coord baseCoord, tmp(curent.x, curent.y);

		tmp.x--;
		min_waight(tmp, baseCoord, baseWaight);

		tmp.y--;
		min_waight(tmp, baseCoord, baseWaight);

		tmp.x++;
		min_waight(tmp, baseCoord, baseWaight);

		tmp.x++;
		min_waight(tmp, baseCoord, baseWaight);

		tmp.y++;
		min_waight(tmp, baseCoord, baseWaight);

		tmp.y++;
		min_waight(tmp, baseCoord, baseWaight);

		tmp.x--;
		min_waight(tmp, baseCoord, baseWaight);

		tmp.x--;
		min_waight(tmp, baseCoord, baseWaight);


		curent = baseCoord;
	}
	return rez;
}

std::vector<Coord> Find::Dijkstra(Coord start, Coord target, std::function<void(Coord, Way)> collback)
{

	return std::vector<Coord>();
}