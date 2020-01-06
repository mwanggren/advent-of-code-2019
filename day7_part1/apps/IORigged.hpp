#ifndef IORIGGED_HPP
#define IORIGGED_HPP

#include <IOSystem.hpp>
#include <vector>

struct IORigged : public IOSystem
{
    // struct IOSystem:

    int readInput() override
    {
        int retval = mInputs.at(0);
        mInputs.erase(mInputs.begin());
        return retval;
    }

    void writeOutput(int aValue) override
    {
        mLastOutput = aValue;
    }

    // Rigging helpers:

    void addInput(int aValue)
    {
        mInputs.push_back(aValue);
    }

    int readLastOutput()
    {
        return mLastOutput;
    }

private:
    std::vector<int> mInputs;
    int mLastOutput;
};

#endif