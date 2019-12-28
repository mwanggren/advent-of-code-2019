#include "Computer.hpp"
#include "ParameterModes.hpp"
#include <fstream>
#include <iostream>

bool Computer::loadProgramFromFile(std::string aFilename)
{
    std::ifstream lInputFile(aFilename);
    int lReadEntry;

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

void Computer::loadProgram(std::vector<int> aProgram)
{
    mMemory = aProgram;
}

bool Computer::memorySet(int aAddress, int aNewValue)
{
    if (aAddress < mMemory.size()) {
        mMemory.at(aAddress) = aNewValue;
        return true;
    }
    else
        return false;
}

std::vector<int>& Computer::viewMemory()
{
    return mMemory;
}

int Computer::tick()
{
    auto lValue = mMemory.at(mInstructionPointer);
    mInstructionPointer++;
    return lValue;
}

bool Computer::runUntilHalt()
{
    while (mInstructionPointer < mMemory.size())
    {
        auto lOpCodeWithParameters = tick();
        if (lOpCodeWithParameters < 0)
            return false;
        auto lOpCode = lOpCodeWithParameters % 100;
        ParameterModes lParams(lOpCodeWithParameters / 100);

        switch (lOpCode)
        {
            case 1:
            { 
                auto lOperand1 = tick();
                auto lOperand2 = tick();
                auto lResultAddress = tick();
                if (lParams.isImmediate(2))
                    return false;
                mMemory.at(lResultAddress) = 
                    (lParams.isImmediate(0) ? lOperand1 : mMemory.at(lOperand1)) + 
                    (lParams.isImmediate(1) ? lOperand2 : mMemory.at(lOperand2));
                break;
            }
            case 2:
            {
                auto lOperand1 = tick();
                auto lOperand2 = tick();
                auto lResultAddress = tick();
                if (lParams.isImmediate(2))
                    return false;
                mMemory.at(lResultAddress) = 
                    (lParams.isImmediate(0) ? lOperand1 : mMemory.at(lOperand1)) * 
                    (lParams.isImmediate(1) ? lOperand2 : mMemory.at(lOperand2));
                break;
            }
            case 3:
            {
                auto lWriteToAddress = tick();
                std::cout << "Input?" << std::endl;
                std::cin >> mMemory.at(lWriteToAddress);
                break;
            }
            case 4:
            {
                auto operand = tick();
                std::cout << "Output: " << (lParams.isImmediate(0) ? operand : mMemory.at(operand)) << std::endl;
                break;
            }
            case 99:
                return true;
            default:
                return false;
        }
    }
    return false;
}

bool Computer::setInstructionPointer(int aInstructionPointer)
{
    if (aInstructionPointer < mMemory.size()) {
        mInstructionPointer = aInstructionPointer;
        return true;
    }
    return false;
}
