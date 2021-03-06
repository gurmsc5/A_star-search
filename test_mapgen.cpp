#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "A-star.hpp"

TEST_CASE("Map generator test", "Map Generator class")
{
	Map_Generator Map_Gen(std::make_pair(25, 25));

	auto Map = Map_Gen.GetMap();

	REQUIRE(Map->size() == 25);

	SECTION("Check for valid coordinates")
	{
		bool check = Map_Gen.ValidCoordinates(std::make_pair(20, 20));
		REQUIRE(check == true);
		check = Map_Gen.ValidCoordinates(std::make_pair(30, 30));
		REQUIRE(check == false);
		check = Map_Gen.ValidCoordinates(std::make_pair(25, 25));
		REQUIRE(check == false);
	}
}

TEST_CASE("A_star lists test", "All A_star lists")
{
	A_star a_star(std::make_pair(9, 10));
	REQUIRE(a_star.getEdges() == std::make_pair(9, 10));
	auto closedlist = a_star.get_closedListVec();
	auto celldetails = a_star.getcellDetailsVec();

	/*check if lists were allocated properly*/
	REQUIRE(closedlist->size() == 9);
	
	REQUIRE(celldetails->size() == 9);
	REQUIRE((*celldetails)[0][5].parent.x == -1);
	REQUIRE((*celldetails)[0][5].parent.y == -1);
	auto map = a_star.GetMap();

	a_star.setBlockade_coord(std::make_pair(7, 0), *map);
	a_star.setBlockade_coord(std::make_pair(7, 1), *map);

	a_star.a_star_search(std::make_pair(8, 0), std::make_pair(0, 0));
}