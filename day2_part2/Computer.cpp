#include "Computer.hpp"
#include <fstream>

bool Computer::loadProgramFromFile(std::string aFilename)
{
    std::ifstream lInputFile(aFilename);
    uint32_t lReadEntry;

    lInputFile >> lReadEntry;
    mMemory.push_back(lReadEntry);
    char lSeparator;
    while (lInputFile >> lSeparator >> lReadEntry && lSeparator == ',')
        mMemory.push_back(lReadEntry);
    lInputFile.close();
    if (!lInputFile.eof())
        return false;
    return true;
}

void Computer::loadProgram(std::vector<uint32_t> aProgram)
{
    mMemory = aProgram;
}

bool Computer::memorySet(uint32_t aAddress, uint32_t aNewValue)
{
    if (aAddress < mMemory.size()) {
        mMemory.at(aAddress) = aNewValue;
        return true;
    }
    else
        return false;
}

std::vector<uint32_t>& Computer::viewMemory()
{
    return mMemory;
}

bool Computer::runUntilHalt()
{
    while (mInstructionPointer < mMemory.size())
    {
        auto& lOpCode = mMemory.at(mInstructionPointer);

        if (lOpCode == 99)
            return true;

        // For now, all instructions except halt are 4 addresses long:
        auto lInputAddress1 = mMemory.at(mInstructionPointer+1);
        auto lInputAddress2 = mMemory.at(mInstructionPointer+2);
        auto lOutputAddress = mMemory.at(mInstructionPointer+3);
        switch (lOpCode)
        {
            case 1:
                mMemory.at(lOutputAddress) = mMemory.at(lInputAddress1) + mMemory.at(lInputAddress2);
                break;
            case 2:
                mMemory.at(lOutputAddress) = mMemory.at(lInputAddress1) * mMemory.at(lInputAddress2);
                break;
        }
        mInstructionPointer += 4;
    }
    return false;
}

bool Computer::setInstructionPointer(uint32_t lInstructionPointer)
{
    if (lInstructionPointer < mMemory.size()) {
        mInstructionPointer = lInstructionPointer;
        return true;
    }
    return false;
}
