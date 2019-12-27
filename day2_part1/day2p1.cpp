#include "Computer.hpp"
#include <iostream>

// I just can't be bothered with the error handling of error return codes here...
int main()
{
    Computer lComputer;
    lComputer.loadProgramFromFile("input");
    lComputer.modifyProgramPos(1, 12);
    lComputer.modifyProgramPos(2, 2);
    lComputer.runUntilEndMarker();

    std::cout << "Position 0 of finished program is " << lComputer.viewProgram().at(0) << std::endl;
}