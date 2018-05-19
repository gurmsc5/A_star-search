#ifndef MAP_GENERATOR_HPP
#define MAP_GENERATOR_HPP
#include <vector>
#include <utility>

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



using CoordinatesVec = std::vector<std::vector<int>>;
using CellVec = std::vector<std::vector<Cell>>;


class Map_Generator {
private:
	/*2D map*/
	CoordinatesVec *Map;
	std::pair<int, int> Edges;
public:
	Map_Generator(std::pair<int, int> edges);
	CoordinatesVec * GetMap();

	/*set up a blockade given a pair of coordinates
	a value of 1 on Map represents a blockade
	a value of 0 on Map represents clear passage*/
	bool setBlockade(std::pair<int, int> &block, CoordinatesVec *map);

	/*set up blockade given a list of coordinates*/
	bool setBlockade(CoordinatesVec &blockvec, CoordinatesVec *map);

	/*check if coordinates are within range*/
	bool ValidCoordinates(std::pair<int, int> edges);
};


#endif // !MAP-GENERATOR_HPP