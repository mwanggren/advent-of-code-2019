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
    void loadProgram(std::vector<uint32_t> aProgram);
    bool memorySet(uint32_t aAddress, uint32_t aNewValue);
    std::vector<uint32_t>& viewMemory();
    bool runUntilHalt();
    bool setInstructionPointer(uint32_t lInstructionPointer);

private:
    std::vector<uint32_t> mMemory;
    uint32_t mInstructionPointer;
};

#endif