#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "map-generator.hpp"

TEST_CASE("Map generator test", "Map Generator class")
{
	Map_Generator Map_Gen(std::make_pair(25, 25));

	auto Map = Map_Gen.GetMap();

	REQUIRE(Map->size() == 25);
}