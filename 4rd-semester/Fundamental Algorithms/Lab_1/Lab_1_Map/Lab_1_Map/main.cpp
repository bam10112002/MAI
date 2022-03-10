#include <iostream>
#include "Find.h"
#include "Map.h"
#include "Matrix.h"

using namespace std;

int main() 
{
		
	map<Coord, int> m;
	m.emplace(Coord(1, 2), 1);

	//Map map(string("map_1.json"));
	//cout << "map name: " << map.getName() << endl << endl;
	//map.matrix.printMatrix();
	//map.find(Coord(3, 0), Coord(3, 3), NULL);
	return 0;

}
