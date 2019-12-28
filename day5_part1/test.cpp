#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "Computer.hpp"

TEST_CASE("Load simple program from file")
{
    Computer lComputer;
    REQUIRE(lComputer.loadProgramFromFile("ultraSimpleInput") == true);
    REQUIRE(lComputer.viewMemory() == std::vector<int> {1,2,3,45});
}

TEST_CASE("Run short reference programs and expect correct results")
{
    GIVEN( "A computer" ) {
        Computer lComputer;

        WHEN( "the program 1,0,0,0,99 is run" ) {
            lComputer.loadProgram(std::vector<int> {1,0,0,0,99});
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "the execution is successful and the resulting program is 2,0,0,0,99" ) {
                REQUIRE(lExitStatus == true);
                REQUIRE(lComputer.viewMemory() == std::vector<int> {2,0,0,0,99});
            }
        }

        WHEN( "the program 2,3,0,3,99 is run" ) {
            lComputer.loadProgram(std::vector<int> {2,3,0,3,99});
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "the execution is successful and the resulting program is 2,3,0,6,99" ) {
                REQUIRE(lExitStatus == true);
                REQUIRE(lComputer.viewMemory() == std::vector<int> {2,3,0,6,99});
            }
        }

        WHEN( "the program 2,4,4,5,99,0 is run" ) {
            lComputer.loadProgram(std::vector<int> {2,4,4,5,99,0});
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "the execution is successful and the resulting program is 2,4,4,5,99,9801" ) {
                REQUIRE(lExitStatus == true);
                REQUIRE(lComputer.viewMemory() == std::vector<int> {2,4,4,5,99,9801});
            }
        }

        WHEN( "the program 1,1,1,4,99,5,6,0,99 is run" ) {
            lComputer.loadProgram(std::vector<int> {1,1,1,4,99,5,6,0,99});
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "the execution is successful and the resulting program is 30,1,1,4,2,5,6,0,99" ) {
                REQUIRE(lExitStatus == true);
                REQUIRE(lComputer.viewMemory() == std::vector<int> {30,1,1,4,2,5,6,0,99});
            }
        }

        WHEN( "the program 1002,4,3,4,33 is run" ) {
            lComputer.loadProgram(std::vector<int> {1002,4,3,4,33});
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "the execution is successful and the resulting program is 1002,4,3,4,99" ) {
                REQUIRE(lExitStatus == true);
                REQUIRE(lComputer.viewMemory() == std::vector<int> {1002,4,3,4,99});
            }
        }

        WHEN( "the program 1102,-1,2,0,99 is run" ) {
            lComputer.loadProgram(std::vector<int> {1102,-1,2,0,99});
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "the execution is successful and the resulting program is -2,-1,2,0,99" ) {
                REQUIRE(lExitStatus == true);
                REQUIRE(lComputer.viewMemory() == std::vector<int> {-2,-1,2,0,99});
            }
        }

        WHEN( "the program 3,1,4,1,104,-1,99 is run" ) {
            lComputer.loadProgram(std::vector<int> {3,1,4,1,104,-1,99});
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "the user is asked for a number, user inputs 100, execution is successful "
                   "and the resulting program is 3,<input value> (100),4,1,104,-1,99 and the output is 1\n-1" ) {
                REQUIRE(lExitStatus == true);
                REQUIRE(lComputer.viewMemory() == std::vector<int> {3,100,4,1,104,-1,99});
            }
        }
    }
}
