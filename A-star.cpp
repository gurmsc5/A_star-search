#include "A-star.hpp"
#include <stdint.h>

A_star::A_star(Pair edges):
	Map_Generator(edges),Edges(edges)
{
	_closedList = new std::vector(edges.first, std::vector<bool>(edges.second));
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

	directions= { {0,0},{0,1},{0,-1},
				{1,0},{1,1},{1,-1},
				{-1,0},{-1,1},{-1,-1} };

	set_heuristic(&DistanceFormulas::euclidian);
}

A_star::~A_star()
{
	delete cellDetails;
	delete _closedList;
}



/*set heuristic function*/
void A_star::set_heuristic(HeuristicFunction H)
{
	Heuristic = std::bind(H, std::placeholders::_1, std::placeholders::_2);
}



CellVec * A_star::getcellDetailsVec() const
{
	return cellDetails;
}
ClosedList * A_star::get_closedListVec() const
{
	return _closedList;
}


bool A_star::found_destination(Pair src, Pair dest)
{
	return((src.first == dest.first) && (src.second == dest.second));
}



void A_star::a_star_search(Pair src, Pair dest)
{


	/*initialize first node of celldetails*/
	(*cellDetails)[src.first][src.second].F = 0.0;
	(*cellDetails)[src.first][src.second].G = 0.0;
	(*cellDetails)[src.first][src.second].H = 0.0;
	(*cellDetails)[src.first][src.second].parent.x = src.first;
	(*cellDetails)[src.first][src.second].parent.y = src.second;

	/*initialize the starting cell on open list*/
	_openList.insert(std::make_pair(std::make_pair(src.first, src.second), 0.0));


	bool found = false;
	Coordinates coord;
	while (!_openList.empty())
	{
		/*remove pair from beginning of open list*/
		auto pair = *_openList.begin();

		/*delete from open list*/
		_openList.erase(_openList.begin());


		coord.x = pair.first.first;
		coord.y = pair.first.second;
		/*add the coordinate pair to closed list*/
		(*_closedList)[coord.x][coord.y] = true;

		/*generate the successor for the cell*/

		double f{ 0.0 }, g{ 0.0 }, h{ 0.0 };

		for (auto it = directions.begin(); it != directions.end(); it++)
		{
			if (ValidCoordinates(std::make_pair((it->x + coord.x), (it->y + coord.y))))
			{
				if (found_destination((std::make_pair((it->x + coord.x), (it->y + coord.y))), dest)) {
					(*cellDetails)[it->x + coord.x][it->y + coord.y].parent.x = coord.x;
					(*cellDetails)[it->x + coord.x][it->y + coord.y].parent.y = coord.y;
					std::cout << "Destination found" << std::endl;
					tracePath(cellDetails, dest);
					found = true;
					return;
				}

				/*if successor is not on the closed list and is unblocked
				find f = g+h
				add the successor along with f,g,h values to open list
				Also update cell details*/
				else if((*_closedList)[it->x + coord.x][it->y + coord.y] == false &&
				checkUnblocked(Map,std::make_pair(it->x+coord.x,it->y+coord.y)))
				{
					g = (*cellDetails)[coord.x][coord.y].G + 1.0;
					auto t = std::make_pair(it->x + coord.x, it->y + coord.y);
					h = Heuristic(t, dest);
					f = g + h;

					/*add to the open list*/
					if ((*cellDetails)[it->x + coord.x][it->y + coord.y].F == FLT_MAX ||
						(*cellDetails)[it->x + coord.x][it->y + coord.y].F > f) {
						_openList.insert(std::make_pair(std::make_pair(it->x + coord.x,
							it->y + coord.y), f));

						(*cellDetails)[it->x + coord.x][it->y + coord.y].F = f;
						(*cellDetails)[it->x + coord.x][it->y + coord.y].G = g;
						(*cellDetails)[it->x + coord.x][it->y + coord.y].H = h;
						(*cellDetails)[it->x + coord.x][it->y + coord.y].parent.x = coord.x;
						(*cellDetails)[it->x + coord.x][it->y + coord.y].parent.y = coord.y;
					}
					
				}
			}
		}
	}

	if (!found) {
		std::cout << "Destination not found" << std::endl;
	}
}


void A_star::tracePath(CellVec * cellvec, Pair dest)
{
	std::vector<Pair> Path;

	int row = dest.first;
	int col = dest.second;

	while (!(((*cellvec)[row][col].parent.x == row) &&
		    ((*cellvec)[row][col].parent.y == col)))
	{
		Path.push_back(std::make_pair(row, col));
		
		int temp_r = (*cellvec)[row][col].parent.x;
		int temp_c = (*cellvec)[row][col].parent.y;

		row = temp_r;
		col = temp_c;
	}
	Path.push_back(std::make_pair(row,col));

	std::cout << "Path Travelled: ";
	for (auto &it : Path) {
		std::cout << "-> (" << it.first << "," << it.second<<")"<<std::endl;
	}
}










double DistanceFormulas::euclidian(Pair src, Pair dst)
{
	return((double)sqrt((src.first - dst.first)*(src.first - dst.first)
		+ (src.second - dst.second)*(src.second - dst.second)));
}