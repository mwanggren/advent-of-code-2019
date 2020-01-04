#include "Computer.hpp"
#include "ParameterModes.hpp"
#include <fstream>

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
    if (aAddress < (int)mMemory.size()) {
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

bool Computer::setInstructionPointer(int aInstructionPointer)
{
    if (aInstructionPointer < (int)mMemory.size()) {
        mInstructionPointer = aInstructionPointer;
        return true;
    }
    return false;
}

bool Computer::runUntilHalt()
{
    while (mInstructionPointer < (int)mMemory.size())
    {
        auto lOpCodeWithParameters = tick();
        if (lOpCodeWithParameters < 0)
            return false;
        auto lOpCode = lOpCodeWithParameters % 100;
        ParameterModes lParams(lOpCodeWithParameters / 100);

        switch (lOpCode)
        {
            case 1: // Add
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
            case 2: // Multiply
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
            case 3: // Read input
            {
                auto lWriteToAddress = tick();
                mMemory.at(lWriteToAddress) = mIOSystem->readInput();
                break;
            }
            case 4: // Write output
            {
                auto operand = tick();
                mIOSystem->writeOutput(lParams.isImmediate(0) ? operand : mMemory.at(operand));
                break;
            }
            case 5: // Jump if true
            {
                auto lCondition = tick();
                auto lDestination = tick();
                if (lParams.isImmediate(0) ? lCondition : mMemory.at(lCondition))
                    setInstructionPointer(lParams.isImmediate(1) ? lDestination : mMemory.at(lDestination)); 
                break;
            }
            case 6: // Jump if false
            {
                auto lCondition = tick();
                auto lDestination = tick();
                if (!(lParams.isImmediate(0) ? lCondition : mMemory.at(lCondition)))
                    setInstructionPointer(lParams.isImmediate(1) ? lDestination : mMemory.at(lDestination)); 
                break;
            }
            case 7: // Less than
            {
                auto lOperand1 = tick();
                auto lOperand2 = tick();
                auto lResultAddress = tick();
                mMemory.at(lResultAddress) = 
                    ((lParams.isImmediate(0) ? lOperand1 : mMemory.at(lOperand1)) < 
                    (lParams.isImmediate(1) ? lOperand2 : mMemory.at(lOperand2))) ? 1 : 0;
                break;
            }
            case 8: // Equals
            {
                auto lOperand1 = tick();
                auto lOperand2 = tick();
                auto lResultAddress = tick();
                mMemory.at(lResultAddress) = 
                    ((lParams.isImmediate(0) ? lOperand1 : mMemory.at(lOperand1)) == 
                     (lParams.isImmediate(1) ? lOperand2 : mMemory.at(lOperand2))) ? 1 : 0;
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
