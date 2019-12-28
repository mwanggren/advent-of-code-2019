#ifndef PARAMETER_MODES_HPP
#define PARAMETER_MODES_HPP

#include <vector>

class ParameterModes
{
public:
    ParameterModes(int aUnparsedParameterModes)
    {
        while(aUnparsedParameterModes != 0)
        {
            auto lParameterMode = aUnparsedParameterModes % 10;
            mParameterModes.push_back(lParameterMode);
            aUnparsedParameterModes = aUnparsedParameterModes / 10;
        }

    }
    ~ParameterModes() {}

    bool isImmediate(int index) 
    {
        if (index < mParameterModes.size())
            return (mParameterModes.at(index) == 1);
        return false; // Leading zeros
    }

private:
    std::vector<int> mParameterModes;
};

#endif