#ifndef COMPUTER_HPP
#define COMPUTER_HPP

#include <IOSystem.hpp>

#include <cstdint>
#include <string>
#include <vector>

class Computer
{
public:
    Computer(IOSystem* aIOSystem): mIOSystem(aIOSystem), mInstructionPointer(0) {};
    ~Computer() {};
    bool loadProgramFromFile(std::string aFilename);
    void loadProgram(std::vector<int> aProgram);
    bool memorySet(int aAddress, int aNewValue);
    std::vector<int>& viewMemory();
    bool runUntilHalt();
    int tick();
    bool setInstructionPointer(int lInstructionPointer);

private:
    int getParameter(int aOperandNr, int aOperand);

    std::vector<int> mMemory;
    IOSystem* mIOSystem;
    int mInstructionPointer;
};

#endif