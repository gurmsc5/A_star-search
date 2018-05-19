#ifndef A_STAR_HPP
#define A_STAR_HPP
#include <map>
#include <iostream>
#include <functional>
#include "map-generator.hpp"

/*aliases for lists to increase readability*/
using OpenList = std::map<Pair, double>;
using ClosedList = std::vector<std::vector<bool>>;

/*function wrapper to enable choosing from multiple distance formulas(future)*/
using HeuristicFunction = std::function<double(Pair, Pair)>;
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

	Coordinates_List directions;

	/*define the edges*/
	Pair Edges;

	/*define heuristic function*/
	HeuristicFunction Heuristic;

public:

	A_star(Pair edges);
	~A_star();
	void a_star_search(Pair src, Pair dest);

	/*DEBUGGING*/
	/*get cell vector details*/
	CellVec * getcellDetailsVec() const;
	/*get closedList details*/
	ClosedList * get_closedListVec() const;

	/*utility function to check if destination is found*/
	bool found_destination(Pair src, Pair dest);

	/*set heuristic function*/
	void set_heuristic(HeuristicFunction H);


	/*trace the path taken by the algorithm*/
	void tracePath(CellVec * closedlist, Pair dest);
};



class DistanceFormulas {
public:
	static double euclidian(Pair src, Pair dst);
};

#endif // !A_STAR_HPP
