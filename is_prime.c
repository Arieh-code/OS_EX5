#include "is_prime.h"
#include <math.h>

bool isPrime(unsigned int number)
{
    // Handle special cases for 0 and 1
    if (number < 2)
    {
        return false;
    }

    // Check divisibility up to the square root of the number
    unsigned int sqrtNum = sqrt(number);
    for (unsigned int i = 2; i <= sqrtNum; i++)
    {
        if (number % i == 0)
        {
            return false;
        }
    }

    return true;
}