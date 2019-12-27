#ifndef COMPUTER_HPP
#define COMPUTER_HPP

#include <cstdint>
#include <string>
#include <vector>

class Computer
{
public:
    Computer() {};
    ~Computer() {};
    bool loadProgramFromFile(std::string aFilename);
    void loadProgram(std::vector<uint32_t> aProgram);  // Mainly here for testability
    bool modifyProgramPos(uint32_t aPos, uint32_t aNewValue);
    std::vector<uint32_t>& viewProgram();
    bool runUntilEndMarker();

private:
    std::vector<uint32_t> mProgram;
};

#endif