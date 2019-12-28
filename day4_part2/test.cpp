#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "Value.hpp"

TEST_CASE("112233 meets the criteria")
{
    REQUIRE(checkValue(112233) == true);
}

TEST_CASE("123444 does not meet the criteria")
{
    REQUIRE(checkValue(123444) == false);
}

TEST_CASE("111122 meets the criteria")
{
    REQUIRE(checkValue(111122) == true);
}
