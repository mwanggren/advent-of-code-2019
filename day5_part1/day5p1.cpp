#include "Computer.hpp"
#include <iostream>

int main()
{
    Computer lComputer;
    if (!(lComputer.loadProgramFromFile("input")))
        std::cout << "failed to load program from file" << std::endl; 
    if (!(lComputer.runUntilHalt()))
        std::cout << "failed to run program until completion" << std::endl; 
}