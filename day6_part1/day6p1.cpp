#include "lib.hpp"
#include <iostream>

int main()
{
    auto lOrbitalMap = readFromFile("input");
    std::cout << "Total number of orbits = " << countOrbits(lOrbitalMap, 0, "COM") << std::endl;
}