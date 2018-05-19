#ifndef A_STAR_HPP
#define A_STAR_HPP
#include <map>
#include "map-generator.hpp"

using OpenList = std::map<std::pair<int,int>, double>;
using ClosedList = std::vector<std::vector<std::pair<bool,int>>>;

class A_star:public Map_Generator
{
private:
	/*open/closed lists*/
	OpenList _openList;
	ClosedList * _closedList;


	/*vector to hold cell details*/
	CellVec * cellDetails;

	/*Map layout*/
	CoordinatesVec *Map;

	/*define the edges*/
	Pair Edges;

public:

	A_star(Pair edges);
	~A_star();
	void a_star_search(Pair src, Pair dest);
	/*get cell vector details*/
	CellVec * getcellDetailsVec();
	/*get closedList details*/
	ClosedList * get_closedListVec();


};

#endif // !A_STAR_HPP
