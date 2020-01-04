#ifndef IORIGGED_HPP
#define IORIGGED_HPP

#include <IOSystem.hpp>
#include <vector>

// NOTE: Got AddressSanitizer: heap-buffer-overflow when doing it the way I wanted
//       at first, will have to dig into it more. Now it's a lot more ugly. Clean up!

struct IORigged : public IOSystem
{
    // int readInput()
    // {
    //     int retval = mInputs.at(0);
    //     mInputs.erase(mInputs.begin());
    //     return retval;
    // }

    int readInput()
    {
        int retval = mInputCounter == 0 ? mFirstInput : mSecondInput;
        mInputCounter++;
        return retval;
    }

    void writeOutput(int aValue)
    {
        mLastOutput = aValue;
    }

    // void addInput(int aValue)
    // {
    //     mInputs.push_back(aValue);
    // }
    void setFirstInput(int aValue)
    {
        mFirstInput = aValue;
        mInputCounter = 0;
    }
    void setSecondInput(int aValue)
    {
        mSecondInput = aValue;
    }

    int readLastOutput()
    {
        return mLastOutput;
    }

    // std::vector<int> mInputs;
    int mFirstInput;
    int mSecondInput;
    int mInputCounter;
    int mLastOutput;
};

#endif