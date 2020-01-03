#include <string>
#include <map>

std::multimap<std::string, std::string> readFromFile(std::string aInputFilename);

int countOrbits(const std::multimap<std::string, std::string>& aOrbitalMap, 
                const int aCurrentDepth, 
                const std::string& base);
