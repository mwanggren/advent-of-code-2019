#include "Value.hpp"
#include <iostream>

int main()
{
    int lStartValue = 138241;
    int lEndValue = 674034;

    int lNumberOfMatches = 0;
    for (int lValue = lStartValue; lValue <= lEndValue; lValue++)
    {
        if(checkValue(lValue))
            lNumberOfMatches++;
    }

    std::cout << "Number of different passwords in range " 
              << lStartValue << "-" << lEndValue 
              << " matching criteria is " << lNumberOfMatches << std::endl;
}