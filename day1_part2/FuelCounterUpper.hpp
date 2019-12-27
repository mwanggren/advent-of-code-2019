#ifndef FUEL_COUNTER_UPPER_HPP
#define FUEL_COUNTER_UPPER_HPP

#include <string>
#include <cstdint>
#include <fstream>
#include "Module.hpp"

uint32_t calculateTotalFuel(std::string aInputFilename)
{
    uint32_t lTotalFuel;
    std::ifstream lInputFile(aInputFilename);
    uint32_t lModuleFuel;
    while (lInputFile >> lModuleFuel)
        lTotalFuel += Module(lModuleFuel).getFuel();
    lInputFile.close();

    return lTotalFuel;
}

#endif