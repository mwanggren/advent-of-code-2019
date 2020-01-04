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

bool findPathToNodeFromBase(const std::multimap<std::string, std::string>& aOrbitalMap,
                            const std::string& aBase, 
                            const std::string& aNode,
                            std::vector<std::string>& aPath)
{
    auto lRange = aOrbitalMap.equal_range(aBase);
    for (auto it = lRange.first; it != lRange.second; it++)
    {
        if (it->second == aNode)
            return true;
        if (findPathToNodeFromBase(aOrbitalMap, it->second, aNode, aPath) == true)
        {
            aPath.insert(aPath.begin(), it->second);
            return true;
        }
    }
    return false;
}

std::vector<std::string> findPathFromNodeToNode(const std::multimap<std::string, std::string>& aOrbitalMap,
                                                const std::string& aNodeSrc, 
                                                const std::string& aNodeDst)
{
    std::vector<std::string> lPath;

    std::vector<std::string> lPathToNodeSrc;
    findPathToNodeFromBase(aOrbitalMap, "COM", aNodeSrc, lPathToNodeSrc);
    
    std::vector<std::string> lPathToNodeDst;
    findPathToNodeFromBase(aOrbitalMap, "COM", aNodeDst, lPathToNodeDst);
    
    auto itSrc = lPathToNodeSrc.begin();
    auto itDst = lPathToNodeDst.begin();
    while (*itSrc == *itDst)
    {
        itSrc++;
        itDst++;
    }
    for (; itSrc != lPathToNodeSrc.end(); itSrc++)
        lPath.insert(lPath.begin(), *itSrc);
    lPath.push_back(*(itDst-1));
    for (; itDst != lPathToNodeDst.end(); itDst++)
       lPath.push_back(*itDst);
    
    return lPath;
}