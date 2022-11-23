#include <iostream>

using namespace std;

int least_common_multiple(int d1, int d2)
{
    int large = d1 > d2 ? d1 : d2;
    int small = large == d1 ? d2 : d1;
    for (int i = 1; ; i++)
    {
        if ((large*i) % small == 0)
        {
            large = large*i;
            break;
        }
    }
    return large;
}

class fraction
{
    private:
        int numerator, denominator; 
    public:
        fraction(int numr = 1, int denomr = 1);
        fraction operator+(fraction &frac);
        ~fraction();
};

