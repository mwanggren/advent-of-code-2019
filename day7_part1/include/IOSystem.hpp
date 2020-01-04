#ifndef IOSSYSTEM_HPP
#define IOSSYSTEM_HPP

struct IOSystem
{
    virtual ~IOSystem() = default;
    virtual int readInput() = 0;
    virtual void writeOutput(int aValue) = 0;
};

#endif