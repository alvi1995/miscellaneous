#pragma once
#include <iostream>

using namespace std;

class fraction
{
    private:
        int numerator, denominator; 
    public:
        fraction(int numr = 1, int denomr = 1);
        int numr();
        int dnmr();
        ~fraction();
};

