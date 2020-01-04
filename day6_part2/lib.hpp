#include <string>
#include <map>
#include <vector>

std::multimap<std::string, std::string> readFromFile(std::string aInputFilename);

int countOrbits(const std::multimap<std::string, std::string>& aOrbitalMap, 
                const int aCurrentDepth, 
                const std::string& base);

bool findPathToNodeFromBase(const std::multimap<std::string, std::string>& aOrbitalMap,
                            const std::string& aBase, 
                            const std::string& aNode,
                            std::vector<std::string>& aPath);

std::vector<std::string> findPathFromNodeToNode(const std::multimap<std::string, std::string>& aOrbitalMap,
                                                const std::string& aNodeSrc, 
                                                const std::string& aNodeDst);
