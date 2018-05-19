#include "map-generator.hpp"



Map_Generator::Map_Generator(std::pair<int, int> edges): Edges(edges){

	Map = new std::vector(edges.first, std::vector<int>(edges.second));
}

CoordinatesVec * Map_Generator::GetMap() {
	return Map;
}


bool Map_Generator::setBlockade(std::pair<int, int> &block, CoordinatesVec *map)
{

}

bool Map_Generator::setBlockade(CoordinatesVec &blockvec, CoordinatesVec *map)
{

}

bool Map_Generator::ValidCoordinates(std::pair<int, int> edges)
{

}