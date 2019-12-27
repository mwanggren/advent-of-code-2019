#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

#include "Module.hpp"
#include "FuelCounterUpper.hpp"

TEST_CASE("Fuel is computed for a module")
{
    REQUIRE(Module(12).getFuel() == 2);
    REQUIRE(Module(14).getFuel() == 2);
    REQUIRE(Module(1969).getFuel() == 654 + 216 + 70 + 21 + 5);
    REQUIRE(Module(100756).getFuel() == 33583+ 11192 + 3728 + 1240 + 411 + 135 + 43 + 12 + 2);
}

TEST_CASE("Total fuel is computed from ultra short input file")
{
    REQUIRE(calculateTotalFuel("ultraShortInput") == 2);
}

TEST_CASE("Total fuel is computed from short input file")
{
    REQUIRE(calculateTotalFuel("shortInput") == 51316);
}
