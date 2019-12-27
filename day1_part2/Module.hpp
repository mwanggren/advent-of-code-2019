#ifndef MODULE_HPP
#define MODULE_HPP

#include <cstdint>

class Module
{
private:
    uint32_t mMass;

    uint32_t getFuelFromMass(uint32_t lMass);

public:
    Module(uint32_t aMass) : mMass(aMass) {}
    ~Module() {};

    uint32_t getFuel();
};

#endif