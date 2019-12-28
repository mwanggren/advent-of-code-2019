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
    int lNrIdenticalDigitsInARow = 1;
    for (const auto& lCurrentDigit : lDigits)
    {
        if (lLastDigit > lCurrentDigit)
            lDigitDecreasing = true;

        if (lLastDigit == lCurrentDigit)
        {
            lNrIdenticalDigitsInARow++;

            // Special case for the last digit:
            if ( (&lCurrentDigit == &lDigits.back()) && (lNrIdenticalDigitsInARow == 2) )
                lDuplicateAdjacentDigits = true;
        }
        else 
        {
            if (lNrIdenticalDigitsInARow == 2)
                lDuplicateAdjacentDigits = true;

            lNrIdenticalDigitsInARow = 1;
        }

        lLastDigit = lCurrentDigit;
    }

    return !(lDigitDecreasing) && lDuplicateAdjacentDigits;
}

#endif