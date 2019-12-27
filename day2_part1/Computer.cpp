#include "Computer.hpp"
#include <fstream>

// We could add an mProgramCounter and a function step()

bool Computer::loadProgramFromFile(std::string aFilename)
{
    std::ifstream lInputFile(aFilename);
    uint32_t lReadEntry;

    lInputFile >> lReadEntry;
    mProgram.push_back(lReadEntry);
    char lSeparator;
    while (lInputFile >> lSeparator >> lReadEntry && lSeparator == ',')
        mProgram.push_back(lReadEntry);
    lInputFile.close();
    if (!lInputFile.eof())
        return false;
    return true;
}

void Computer::loadProgram(std::vector<uint32_t> aProgram)
{
    mProgram = aProgram;
}

bool Computer::modifyProgramPos(uint32_t aPos, uint32_t aNewValue)
{
    if (aPos < mProgram.size()) {
        mProgram.at(aPos) = aNewValue;
        return true;
    }
    else
        return false;
}

std::vector<uint32_t>& Computer::viewProgram()
{
    return mProgram;
}

bool Computer::runUntilEndMarker()
{
    for (int i = 0; i < mProgram.size(); i+=4)
    {
        auto& lOpCode = mProgram.at(i);

        if (lOpCode == 99)
            return true;

        auto lInputPosition1 = mProgram.at(i+1);
        auto lInputPosition2 = mProgram.at(i+2);
        auto lOutputPosition = mProgram.at(i+3);
        switch (lOpCode)
        {
            case 1:
                mProgram.at(lOutputPosition) = mProgram.at(lInputPosition1) + mProgram.at(lInputPosition2);
                break;
            case 2:
                mProgram.at(lOutputPosition) = mProgram.at(lInputPosition1) * mProgram.at(lInputPosition2);
                break;
        }
    }
    return false;
}