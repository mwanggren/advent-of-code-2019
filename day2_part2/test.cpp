#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "Computer.hpp"

TEST_CASE("Load simple program from file")
{
    Computer lComputer;
    REQUIRE(lComputer.loadProgramFromFile("ultraSimpleInput") == true);
    REQUIRE(lComputer.viewMemory() == std::vector<uint32_t> {1,2,3,45});
}

TEST_CASE("Run short reference programs and expect correct results")
{
    GIVEN( "A computer" ) {
        Computer lComputer;

        WHEN( "the program 1,0,0,0,99 is run" ) {
            lComputer.loadProgram(std::vector<uint32_t> {1,0,0,0,99});
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "the execution is successful and the resulting program is 2,0,0,0,99" ) {
                REQUIRE(lExitStatus == true);
                REQUIRE(lComputer.viewMemory() == std::vector<uint32_t> {2,0,0,0,99});
            }
        }

        WHEN( "the program 2,3,0,3,99 is run" ) {
            lComputer.loadProgram(std::vector<uint32_t> {2,3,0,3,99});
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "the execution is successful and the resulting program is 2,3,0,6,99" ) {
                REQUIRE(lExitStatus == true);
                REQUIRE(lComputer.viewMemory() == std::vector<uint32_t> {2,3,0,6,99});
            }
        }

        WHEN( "the program 2,4,4,5,99,0 is run" ) {
            lComputer.loadProgram(std::vector<uint32_t> {2,4,4,5,99,0});
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "the execution is successful and the resulting program is 2,4,4,5,99,9801" ) {
                REQUIRE(lExitStatus == true);
                REQUIRE(lComputer.viewMemory() == std::vector<uint32_t> {2,4,4,5,99,9801});
            }
        }

        WHEN( "the program 1,1,1,4,99,5,6,0,99 is run" ) {
            lComputer.loadProgram(std::vector<uint32_t> {1,1,1,4,99,5,6,0,99});
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "the execution is successful and the resulting program is 30,1,1,4,2,5,6,0,99" ) {
                REQUIRE(lExitStatus == true);
                REQUIRE(lComputer.viewMemory() == std::vector<uint32_t> {30,1,1,4,2,5,6,0,99});
            }
        }
    }
}

TEST_CASE("Verify result of part 2 using solution for part 1")
{
    Computer lComputer;
    lComputer.loadProgramFromFile("input");
    lComputer.memorySet(1, 82);
    lComputer.memorySet(2, 26);
    lComputer.runUntilHalt();

    REQUIRE(lComputer.viewMemory().at(0) == 19690720);
}
