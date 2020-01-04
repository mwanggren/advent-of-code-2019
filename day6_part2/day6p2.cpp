#include "lib.hpp"
#include <iostream>

int main()
{
    auto lOrbitalMap = readFromFile("input");
    auto lPath = findPathFromNodeToNode(lOrbitalMap, "YOU", "SAN");
    auto lJumps = lPath.size() - 1;  // nr of jumps between x nodes is x - 1.

    std::cout << "The minimum number of orbital transfers required is " << lJumps << std::endl;
}