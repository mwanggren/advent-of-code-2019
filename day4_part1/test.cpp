#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "Value.hpp"

TEST_CASE("122345 meets the criteria")
{
    REQUIRE(checkValue(122345) == true);
}

TEST_CASE("111111 meets the criteria")
{
    REQUIRE(checkValue(111111) == true);
}

TEST_CASE("223450 does not meet the criteria")
{
    REQUIRE(checkValue(223450) == false);
}

TEST_CASE("123789 does not meet the criteria")
{
    REQUIRE(checkValue(123789) == false);
}