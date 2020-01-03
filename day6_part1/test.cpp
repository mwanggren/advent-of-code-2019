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