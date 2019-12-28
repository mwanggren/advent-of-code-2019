#include "Computer.hpp"
#include "IOStreams.hpp"
#include <iostream>
#include <memory>

int main()
{
    IOStreams streamsIOSystem;
    Computer lComputer (&streamsIOSystem);
    if (!(lComputer.loadProgramFromFile("input")))
        std::cout << "failed to load program from file" << std::endl; 
    if (!(lComputer.runUntilHalt()))
        std::cout << "failed to run program until completion" << std::endl; 
}