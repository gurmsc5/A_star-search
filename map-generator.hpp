#ifndef MAP_GENERATOR_HPP
#define MAP_GENERATOR_HPP
#include <vector>
#include <utility>


struct Coordinates {
	int x, y;
	Coordinates(int _x, int _y) :x(_x), y(_y) {};
	Coordinates() {};
};


struct Cell {
	/*first is x coordinate
	second is y coordinate*/
	Coordinates parent;
	double F, G, H;
	/*custom constructor*/
	Cell( double f,
		double g, double h, Coordinates _parent) : F(f),
		G(g), H(h), parent(_parent) {};
	Cell() {};
};




/*aliases for better code readability*/
using Pair = std::pair<int, int>;
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
	Map_Generator(Pair edges);
	~Map_Generator() {
		delete Map;
	};
	/*return a pointer to the constructed Map*/
	CoordinatesVec * GetMap() const;

	/*set up a blockade given a pair of coordinates
	a value of 1 on Map represents a blockade
	a value of 0 on Map represents clear passage*/
	bool setBlockade_coord(Pair &block, CoordinatesVec &map);

	/*set up blockade given a list of coordinates*/
	/*returns a failed set of coordinates that were not blocked because of invalid
	coordinates*/
	Coordinates_List setBlockade_coordlist(Coordinates_List &blockvec, CoordinatesVec &map);

	/*check if coordinates are within range
	pair.first = x
	pair.second = y*/
	bool ValidCoordinates(Pair edges) const;

	/*get the map edges*/
	std::pair<int, int> getEdges() const;

	/*check if there is a blocked coordinate on the map*/
	bool checkUnblocked(CoordinatesVec *map, Pair coord);
};


#endif // !MAP-GENERATOR_HPP