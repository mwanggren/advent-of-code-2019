#ifndef COMPUTER_HPP
#define COMPUTER_HPP

#include <cstdint>
#include <string>
#include <vector>

class Computer
{
public:
    Computer(): mInstructionPointer(0) {};
    ~Computer() {};
    bool loadProgramFromFile(std::string aFilename);
    void loadProgram(std::vector<int> aProgram);
    bool memorySet(int aAddress, int aNewValue);
    std::vector<int>& viewMemory();
    bool runUntilHalt();
    int tick();
    bool setInstructionPointer(int lInstructionPointer);

private:
    std::vector<int> mMemory;
    int mInstructionPointer;
};

#endif