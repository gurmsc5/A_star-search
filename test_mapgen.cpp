#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "map-generator.hpp"

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
	}
}