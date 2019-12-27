#include "Module.hpp"
#include <algorithm>

uint32_t Module::getFuel()
{
    uint32_t lMass = mMass;
    uint32_t lTotFuel = 0;
    while(lMass > 0)
    {
        uint32_t lAdditionalFuel = getFuelFromMass(lMass);
        lTotFuel += lAdditionalFuel;
        lMass = lAdditionalFuel;
    }

    return lTotFuel;
}

uint32_t Module::getFuelFromMass(uint32_t lMass)
{
    return std::max(0, (((int32_t)lMass)/3)-2);
}
