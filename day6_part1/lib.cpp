#include "lib.hpp"
#include <fstream>

std::multimap<std::string, std::string> readFromFile(std::string aInputFilename)
{
    std::ifstream lInputFile(aInputFilename);
    std::multimap<std::string, std::string> lOrbitalMap;
    std::string lCenter;
    std::string lOrbiter;
    char lSeparator;
    while (std::getline(lInputFile, lCenter, ')') && std::getline(lInputFile, lOrbiter))
        lOrbitalMap.insert(std::pair<std::string, std::string> (lCenter, lOrbiter));
    lInputFile.close();
    return lOrbitalMap;
}

int countOrbits(const std::multimap<std::string, std::string>& aOrbitalMap, 
                const int aCurrentDepth, 
                const std::string& base)
{
    int lTotBelowThis = 0;
    auto lRange = aOrbitalMap.equal_range(base);
    for (auto it = lRange.first; it != lRange.second; it++)
        lTotBelowThis += countOrbits(aOrbitalMap, aCurrentDepth+1, it->second);
    return lTotBelowThis + aCurrentDepth;
}   
