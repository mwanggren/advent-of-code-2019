#include <Computer.hpp>

#include "IOStreams.hpp"

#include <iostream>
#include <memory>
#include <cstdlib>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Please provide input file as only parameter!" << std::endl;
        return EXIT_FAILURE;
    }
    std::string lInputFile = argv[1];
    IOStreams lStreamsIOSystem;
    Computer lComputer (&lStreamsIOSystem);
    if (!(lComputer.loadProgramFromFile(lInputFile)))
        std::cout << "failed to load program from file" << std::endl; 
    if (!(lComputer.runUntilHalt()))
        std::cout << "failed to run program until completion" << std::endl; 
}