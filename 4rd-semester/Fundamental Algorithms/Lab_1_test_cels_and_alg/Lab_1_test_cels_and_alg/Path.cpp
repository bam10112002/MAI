#include <map>
#include "Path.h"

std::vector<Coord> Path::find_path(Coord start, Coord target, std::function<void(Coord, Path::Way)> collback)
{
	std::multimap<double, Coord> cels_waights;
	Coord count = start;




	while (count != target)
	{
		matrix[count.x][count.y].set_distanse(count,target,0);

	}
}
