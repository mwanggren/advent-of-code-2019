#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <catch2/trompeloeil.hpp>

#include <Computer.hpp>
#include <IOSystem.hpp>

#include <iostream>
#include <memory>

struct MockIOSystem : public IOSystem
{
    MAKE_MOCK0(readInput, int());
    MAKE_MOCK1(writeOutput, void(int));
};

int runThrusterTest(int* aPhaseSettings, std::vector<int> aProgram)
{
    int lCurrentThrust = 0;

    for(int ix = 0; ix < 5; ix++)
    {
        MockIOSystem mockIOSystem;
        Computer lComputer (&mockIOSystem);

        lComputer.loadProgram(aProgram);
        trompeloeil::sequence seq1;
        REQUIRE_CALL(mockIOSystem, readInput()).RETURN(aPhaseSettings[ix]).TIMES(1).IN_SEQUENCE(seq1);
        REQUIRE_CALL(mockIOSystem, readInput()).RETURN(lCurrentThrust).TIMES(1).IN_SEQUENCE(seq1);
        REQUIRE_CALL(mockIOSystem, writeOutput(trompeloeil::_)).TIMES(1).IN_SEQUENCE(seq1).LR_SIDE_EFFECT(lCurrentThrust = _1);

        lComputer.runUntilHalt();
    }
    return lCurrentThrust;
}
TEST_CASE("First reference max thruster test")
{
    int lPhaseSettings[5] = {4,3,2,1,0};
    std::vector<int> lProgram {3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0};
    REQUIRE(runThrusterTest(lPhaseSettings, lProgram) == 43210);
}
TEST_CASE("Second reference max thruster test")
{
    int lPhaseSettings[5] = {0,1,2,3,4};
    std::vector<int> lProgram {3,23,3,24,1002,24,10,24,1002,23,-1,23,101,5,23,23,1,24,23,23,4,23,99,0,0};
    REQUIRE(runThrusterTest(lPhaseSettings, lProgram) == 54321);
}
TEST_CASE("Third reference max thruster test")
{
    int lPhaseSettings[5] = {1,0,4,3,2};
    std::vector<int> lProgram {3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0};
    REQUIRE(runThrusterTest(lPhaseSettings, lProgram) == 65210);
}
TEST_CASE("Test solution max thruster test")
{
    int lPhaseSettings[5] = {2,2,2,2,2};
    std::vector<int> lProgram {3,8,1001,8,10,8,105,1,0,0,21,34,47,72,81,102,183,264,345,426,99999,3,9,102,5,9,9,1001,9,3,9,4,9,99,3,9,101,4,9,9,1002,9,3,9,4,9,99,3,9,102,3,9,9,101,2,9,9,102,5,9,9,1001,9,3,9,1002,9,4,9,4,9,99,3,9,101,5,9,9,4,9,99,3,9,101,3,9,9,1002,9,5,9,101,4,9,9,102,2,9,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,1,9,9,4,9,99,3,9,101,1,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,2,9,9,4,9,99,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,1001,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,2,9,9,4,9,3,9,101,2,9,9,4,9,3,9,102,2,9,9,4,9,99,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,99};
    REQUIRE(runThrusterTest(lPhaseSettings, lProgram) == 685342372);
}

TEST_CASE("Load simple program from file")
{
    MockIOSystem mockIOSystem;
    Computer lComputer (&mockIOSystem);
    REQUIRE(lComputer.loadProgramFromFile("ultraSimpleInput") == true);
    REQUIRE(lComputer.viewMemory() == std::vector<int> {1,2,3,45});
}

TEST_CASE("Run short reference programs and expect correct results")
{
    GIVEN( "A computer" ) {
        MockIOSystem mockIOSystem;
        Computer lComputer (&mockIOSystem);

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

        WHEN( "the program 3,1,4,1,104,-1,99 is run and 100 is input" ) {
            lComputer.loadProgram(std::vector<int> {3,1,4,1,104,-1,99});
            trompeloeil::sequence seq1;
            REQUIRE_CALL(mockIOSystem, readInput()).RETURN(100).TIMES(1).IN_SEQUENCE(seq1);
            REQUIRE_CALL(mockIOSystem, writeOutput(100)).IN_SEQUENCE(seq1);
            REQUIRE_CALL(mockIOSystem, writeOutput(-1)).IN_SEQUENCE(seq1);
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "execution is successful and the resulting program is 3,<input value> (100),4,1,104,-1,99" ) {
                REQUIRE(lExitStatus == true);
                REQUIRE(lComputer.viewMemory() == std::vector<int> {3,100,4,1,104,-1,99});
            }
        }

        WHEN( "the program 3,9,8,9,10,9,4,9,99,-1,8 is run and 8 is input" ) {
            lComputer.loadProgram(std::vector<int> {3,9,8,9,10,9,4,9,99,-1,8});
            trompeloeil::sequence seq1;
            REQUIRE_CALL(mockIOSystem, readInput()).RETURN(8).TIMES(1).IN_SEQUENCE(seq1);
            REQUIRE_CALL(mockIOSystem, writeOutput(1)).TIMES(1).IN_SEQUENCE(seq1);
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "execution is successful and 1 is output" ) {
                REQUIRE(lExitStatus == true);
            }
        }
        WHEN( "the program 3,9,8,9,10,9,4,9,99,-1,8 is run and 9 is input" ) {
            lComputer.loadProgram(std::vector<int> {3,9,8,9,10,9,4,9,99,-1,8});
            trompeloeil::sequence seq1;
            REQUIRE_CALL(mockIOSystem, readInput()).RETURN(9).TIMES(1).IN_SEQUENCE(seq1);
            REQUIRE_CALL(mockIOSystem, writeOutput(0)).TIMES(1).IN_SEQUENCE(seq1);
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "execution is successful, and 0 is output" ) {
                REQUIRE(lExitStatus == true);
            }
        }

        WHEN( "the program 3,9,7,9,10,9,4,9,99,-1,8 is run and 7 is input" ) {
            lComputer.loadProgram(std::vector<int> {3,9,7,9,10,9,4,9,99,-1,8});
            trompeloeil::sequence seq1;
            REQUIRE_CALL(mockIOSystem, readInput()).RETURN(7).TIMES(1).IN_SEQUENCE(seq1);
            REQUIRE_CALL(mockIOSystem, writeOutput(1)).TIMES(1).IN_SEQUENCE(seq1);
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "execution is successful, and 1 is output" ) {
                REQUIRE(lExitStatus == true);
            }
        }
        WHEN( "the program 3,9,7,9,10,9,4,9,99,-1,8 is run and 8 is input" ) {
            lComputer.loadProgram(std::vector<int> {3,9,7,9,10,9,4,9,99,-1,8});
            trompeloeil::sequence seq1;
            REQUIRE_CALL(mockIOSystem, readInput()).RETURN(8).TIMES(1).IN_SEQUENCE(seq1);
            REQUIRE_CALL(mockIOSystem, writeOutput(0)).TIMES(1).IN_SEQUENCE(seq1);
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "execution is successful, and 0 is output" ) {
                REQUIRE(lExitStatus == true);
            }
        }

        WHEN( "the program 3,3,1108,-1,8,3,4,3,99 is run and 8 is input" ) {
            lComputer.loadProgram(std::vector<int> {3,3,1108,-1,8,3,4,3,99});
            trompeloeil::sequence seq1;
            REQUIRE_CALL(mockIOSystem, readInput()).RETURN(8).TIMES(1).IN_SEQUENCE(seq1);
            REQUIRE_CALL(mockIOSystem, writeOutput(1)).TIMES(1).IN_SEQUENCE(seq1);
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "execution is successful, and 1 is output" ) {
                REQUIRE(lExitStatus == true);
            }
        }
        WHEN( "the program 3,3,1108,-1,8,3,4,3,99 is run and 9 is input" ) {
            lComputer.loadProgram(std::vector<int> {3,3,1108,-1,8,3,4,3,99});
            trompeloeil::sequence seq1;
            REQUIRE_CALL(mockIOSystem, readInput()).RETURN(9).TIMES(1).IN_SEQUENCE(seq1);
            REQUIRE_CALL(mockIOSystem, writeOutput(0)).TIMES(1).IN_SEQUENCE(seq1);
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "execution is successful, and 0 is output" ) {
                REQUIRE(lExitStatus == true);
            }
        }

        WHEN( "the program 3,3,1107,-1,8,3,4,3,99 is run and 7 is input" ) {
            lComputer.loadProgram(std::vector<int> {3,3,1107,-1,8,3,4,3,99});
            trompeloeil::sequence seq1;
            REQUIRE_CALL(mockIOSystem, readInput()).RETURN(7).TIMES(1).IN_SEQUENCE(seq1);
            REQUIRE_CALL(mockIOSystem, writeOutput(1)).TIMES(1).IN_SEQUENCE(seq1);
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "execution is successful, and 1 is output" ) {
                REQUIRE(lExitStatus == true);
            }
        }
        WHEN( "the program 3,3,1107,-1,8,3,4,3,99 is run and 8 is input" ) {
            lComputer.loadProgram(std::vector<int> {3,3,1107,-1,8,3,4,3,99});
            trompeloeil::sequence seq1;
            REQUIRE_CALL(mockIOSystem, readInput()).RETURN(8).TIMES(1).IN_SEQUENCE(seq1);
            REQUIRE_CALL(mockIOSystem, writeOutput(0)).TIMES(1).IN_SEQUENCE(seq1);
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "execution is successful, and 0 is output" ) {
                REQUIRE(lExitStatus == true);
            }
        }

        WHEN( "the program 3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9 is run and 0 is input" ) {
            lComputer.loadProgram(std::vector<int> {3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9});
            trompeloeil::sequence seq1;
            REQUIRE_CALL(mockIOSystem, readInput()).RETURN(0).TIMES(1).IN_SEQUENCE(seq1);
            REQUIRE_CALL(mockIOSystem, writeOutput(0)).TIMES(1).IN_SEQUENCE(seq1);
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "execution is successful, and 0 is output" ) {
                REQUIRE(lExitStatus == true);
            }
        }
        WHEN( "the program 3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9 is run and 4 is input" ) {
            lComputer.loadProgram(std::vector<int> {3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9});
            trompeloeil::sequence seq1;
            REQUIRE_CALL(mockIOSystem, readInput()).RETURN(4).TIMES(1).IN_SEQUENCE(seq1);
            REQUIRE_CALL(mockIOSystem, writeOutput(1)).TIMES(1).IN_SEQUENCE(seq1);
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "execution is successful, and 1 is output" ) {
                REQUIRE(lExitStatus == true);
            }
        }

        WHEN( "the program 3,3,1105,-1,9,1101,0,0,12,4,12,99,1 is run and 0 is input" ) {
            lComputer.loadProgram(std::vector<int> {3,3,1105,-1,9,1101,0,0,12,4,12,99,1});
            trompeloeil::sequence seq1;
            REQUIRE_CALL(mockIOSystem, readInput()).RETURN(0).TIMES(1).IN_SEQUENCE(seq1);
            REQUIRE_CALL(mockIOSystem, writeOutput(0)).TIMES(1).IN_SEQUENCE(seq1);
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "execution is successful, and 0 is output" ) {
                REQUIRE(lExitStatus == true);
            }
        }
        WHEN( "the program 3,3,1105,-1,9,1101,0,0,12,4,12,99,1 is run and 4 is input" ) {
            lComputer.loadProgram(std::vector<int> {3,3,1105,-1,9,1101,0,0,12,4,12,99,1});
            trompeloeil::sequence seq1;
            REQUIRE_CALL(mockIOSystem, readInput()).RETURN(4).TIMES(1).IN_SEQUENCE(seq1);
            REQUIRE_CALL(mockIOSystem, writeOutput(1)).TIMES(1).IN_SEQUENCE(seq1);
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "execution is successful, and 1 is output" ) {
                REQUIRE(lExitStatus == true);
            }
        }

        WHEN( "the program 3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99 is run and 7 is input" ) {
            lComputer.loadProgram(std::vector<int> {3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99});
            trompeloeil::sequence seq1;
            REQUIRE_CALL(mockIOSystem, readInput()).RETURN(7).TIMES(1).IN_SEQUENCE(seq1);
            REQUIRE_CALL(mockIOSystem, writeOutput(999)).TIMES(1).IN_SEQUENCE(seq1);
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "execution is successful, and 999 is output" ) {
                REQUIRE(lExitStatus == true);
            }
        }
        WHEN( "the program 3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99 is run and 8 is input" ) {
            lComputer.loadProgram(std::vector<int> {3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99});
            trompeloeil::sequence seq1;
            REQUIRE_CALL(mockIOSystem, readInput()).RETURN(8).TIMES(1).IN_SEQUENCE(seq1);
            REQUIRE_CALL(mockIOSystem, writeOutput(1000)).TIMES(1).IN_SEQUENCE(seq1);
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "execution is successful, and 1000 is output" ) {
                REQUIRE(lExitStatus == true);
            }
        }
        WHEN( "the program 3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99 is run and 9 is input" ) {
            lComputer.loadProgram(std::vector<int> {3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99});
            trompeloeil::sequence seq1;
            REQUIRE_CALL(mockIOSystem, readInput()).RETURN(9).TIMES(1).IN_SEQUENCE(seq1);
            REQUIRE_CALL(mockIOSystem, writeOutput(1001)).TIMES(1).IN_SEQUENCE(seq1);
            auto lExitStatus = lComputer.runUntilHalt();

            THEN ( "execution is successful, and 1001 is output" ) {
                REQUIRE(lExitStatus == true);
            }
        }

    }
}
