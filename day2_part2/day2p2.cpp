#include "Computer.hpp"
#include <iostream>

// I just can't be bothered with the error handling of error return codes here...
int main()
{
    Computer lComputer;
    lComputer.loadProgramFromFile("input");
    std::vector<uint32_t> lProgram = lComputer.viewMemory();

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            lComputer.loadProgram(lProgram);
            lComputer.setInstructionPointer(0);
            lComputer.memorySet(1, i);
            lComputer.memorySet(2, j);
            lComputer.runUntilHalt();
            if (lComputer.viewMemory().at(0) == 19690720) {
                std::cout << "Noun is " << i << " and verb is " << j << ", answer is " << 100 * i + j << std::endl;
                return 0;
            }
        }
    }
    std::cout << "Failed to find an answer" << std::endl;
}