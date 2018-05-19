#include "A-star.hpp"
#include <stdint.h>

A_star::A_star(Pair edges):
	Map_Generator(edges),Edges(edges)
{
	_closedList = new std::vector(edges.first, std::vector<std::pair<bool,int>>(edges.second));
	cellDetails = new std::vector(edges.first, std::vector<Cell>(edges.second));
	Map = GetMap();

	for (int i{ 0 }; i < edges.first; i++) {
		for (int j{ 0 }; j < edges.second; j++)
		{
			(*cellDetails)[i][j].F = FLT_MAX;
			(*cellDetails)[i][j].G = FLT_MAX;
			(*cellDetails)[i][j].H = FLT_MAX;
			(*cellDetails)[i][j].parent = { -1,-1 };
		}
	}
}

A_star::~A_star()
{
	delete cellDetails;
	delete _closedList;
}


CellVec * A_star::getcellDetailsVec()
{
	return cellDetails;
}
ClosedList * A_star::get_closedListVec()
{
	return _closedList;
}




void A_star::a_star_search(Pair src, Pair dest)
{

}
