#ifndef IOSTREAMS_HPP
#define IOSTREAMS_HPP

#include <IOSystem.hpp>

#include <iostream>

struct IOStreams : public IOSystem
{
    int readInput()
    {
        std::cout << "Input?" << std::endl;
        int lValueRead;
        std::cin >> lValueRead;
        return lValueRead;
    }

    void writeOutput(int aValue)
    {
    std::cout << "Output: " << aValue << std::endl;
}

};

#endif