#include "map-generator.hpp"



Map_Generator::Map_Generator(Pair edges): Edges(edges){

	Map = new std::vector(edges.first, std::vector<int>(edges.second));
}

CoordinatesVec * Map_Generator::GetMap() {
	return Map;
}


bool Map_Generator::setBlockade_coord(Pair &block, CoordinatesVec &map)
{
	if (ValidCoordinates(block)) {
		map[block.first][block.second] = 1;
		return true;
	}
	else{
		return false;
	}
}

Coordinates_List Map_Generator::setBlockade_coordlist(Coordinates_List &blockvec, CoordinatesVec &map)
{
	Coordinates_List failedcoordinates;
	for (const auto &it : blockvec) {
		bool check = setBlockade_coord(std::make_pair(it.x, it.y), map);
		if (!check){
			failedcoordinates.push_back(it);
		}
	}
	return failedcoordinates;
}

bool Map_Generator::ValidCoordinates(Pair edges)
{
	if (((edges.first>=0)&&(edges.first >= Edges.first)) || 
		((edges.second>=0)&&(edges.second >= Edges.second)))
		return false;
	else
		return true;
}

std::pair<int, int> Map_Generator::getEdges() {
	return Edges;
}

bool Map_Generator::checkUnblocked(CoordinatesVec *map, Pair coord)
{
	if (ValidCoordinates(coord)) {
		if ((*map)[coord.first][coord.second] == 1)
			return true;
		else
			return false;
	}
	else
		return false;
}