#include "fraction.h"

fraction::fraction(int numr, int denomr) : numerator(numr), denominator(denomr) {}

int fraction::numr() 
{
    return this->numerator;
}

int fraction::dnmr() 
{
    return this->denominator;
}

fraction::~fraction() {}