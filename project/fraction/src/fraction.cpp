#include "fraction.h"

fraction::fraction(int numr, int denomr) : numerator(numr), denominator(denomr) {}

fraction fraction::operator+(fraction &frac)
{
    fraction sum;
    sum.numerator = denominator*frac.numerator + numerator*frac.denominator;
    sum.denominator = least_common_multiple(denominator, frac.denominator);
    return sum;
}

fraction::~fraction() {}