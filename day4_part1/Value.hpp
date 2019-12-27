#ifndef VALUE_HPP
#define VALUE_HPP

#include <vector>

bool checkValue(int aValue)
{
    std::vector<int> lDigits;
    int lDigit;

    while(aValue != 0)
    {
        lDigit = aValue % 10;
        lDigits.insert(lDigits.begin(), lDigit);
        aValue = aValue / 10;
    }

    bool lDigitDecreasing = false;
    bool lDuplicateAdjacentDigits = false;
    int lLastDigit = 0;
    for (auto lCurrentDigit : lDigits)
    {
        if (lLastDigit > lCurrentDigit)
            lDigitDecreasing = true;
        if (lLastDigit == lCurrentDigit)
            lDuplicateAdjacentDigits = true;
        lLastDigit = lCurrentDigit;
    }

    return !(lDigitDecreasing) && lDuplicateAdjacentDigits;
}

#endif