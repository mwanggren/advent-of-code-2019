#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "lib.hpp"

TEST_CASE("Ultra simple file is read correctly")
{
    auto lOrbitalMap = readFromFile("ultraSimpleInput");
    REQUIRE(lOrbitalMap == std::multimap<std::string, std::string> {{"COM", "A"}, {"A", "B"}, {"A", "C"}});
}

TEST_CASE("Simple orbit spec is correctly read and calculated")
{
    auto lOrbitalMap = readFromFile("simpleInput");
    auto lTotOrbits = countOrbits(lOrbitalMap, 0, "COM");
    REQUIRE(lTotOrbits == 42);
}

TEST_CASE("Simple path from base to node is correctly determined")
{
    auto lOrbitalMap = readFromFile("simpleInput");
    std::vector<std::string> lPath;
    REQUIRE(findPathToNodeFromBase(lOrbitalMap, "COM", "D", lPath) == true);
    REQUIRE(lPath == std::vector<std::string> {"B", "C"});
}

TEST_CASE("Verify calculation of nodes in the path in bewteen L and I in simpleInput")
{
    auto lOrbitalMap = readFromFile("simpleInput");
    auto lPath = findPathFromNodeToNode(lOrbitalMap, "L", "I");
    REQUIRE(lPath == std::vector<std::string> {"K", "J", "E", "D"});    
}