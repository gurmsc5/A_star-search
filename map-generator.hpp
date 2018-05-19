#ifndef MAP_GENERATOR_HPP
#define MAP_GENERATOR_HPP
#include <vector>
#include <utility>


struct Coordinates {
	int x, y;
	Coordinates(int _x, int _y) :x(_x), y(_y) {};
};


struct Cell {
	Cell *parent;
	/*first is x coordinate
	second is y coordinate*/
	std::pair<int,int> coordinates;
	double F, G, H;
	/*custom constructor*/
	Cell(std::pair<int, int> coord, double f,
		double g, double h,
		Cell *_parent = nullptr) : coordinates(coord), F(f),
		G(g), H(h), parent(parent) {};
};


/*aliases for better code readability*/
using CoordinatesVec = std::vector<std::vector<int>>;
using CellVec = std::vector<std::vector<Cell>>;
using Coordinates_List = std::vector<Coordinates>;

class Map_Generator {
private:
	/*2D map*/
	CoordinatesVec *Map;
	std::pair<int, int> Edges;
public:
	/*custom constructor that sets the edges of the Map*/
	Map_Generator(std::pair<int, int> edges);

	/*return a pointer to the constructed Map*/
	CoordinatesVec * GetMap();

	/*set up a blockade given a pair of coordinates
	a value of 1 on Map represents a blockade
	a value of 0 on Map represents clear passage*/
	bool setBlockade_coord(std::pair<int, int> &block, CoordinatesVec &map);

	/*set up blockade given a list of coordinates*/
	/*returns a failed set of coordinates that were not blocked because of invalid
	coordinates*/
	Coordinates_List setBlockade_coordlist(Coordinates_List &blockvec, CoordinatesVec &map);

	/*check if coordinates are within range
	pair.first = x
	pair.second = y*/
	bool ValidCoordinates(std::pair<int, int> edges);
};


#endif // !MAP-GENERATOR_HPP