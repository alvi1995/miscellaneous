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

void simplify(int* numerator, int* denominator, int divisor)
{
    if (divisor <= *numerator)
    {
        if (!(*numerator%divisor) && !(*denominator%divisor))
        {
            *numerator = *numerator/divisor;
            *denominator = *denominator/divisor;
            simplify(numerator,denominator, divisor);
        }
        else
        {
            simplify(numerator, denominator, divisor+1);    
        }   
    }
}

class fraction
{
    private:
        int numerator, denominator; 
    public:
        fraction(int numr = 1, int denomr = 1);
        fraction operator+(fraction &frac);
        fraction operator-(fraction &frac);
        fraction operator*(fraction &frac);
        fraction operator/(fraction &frac);
        friend ostream& operator<<(std::ostream &COUT, fraction& frac);
        ~fraction();
};

fraction::fraction(int numr, int denomr) : numerator(numr), denominator(denomr) {}

fraction fraction::operator+(fraction &frac)
{
    fraction sum;
    sum.numerator = denominator*frac.numerator + numerator*frac.denominator;
    sum.denominator = least_common_multiple(denominator, frac.denominator);
    simplify(&sum.numerator, &sum.denominator, 2);
    return sum;
}

fraction fraction::operator-(fraction &frac)
{
    fraction difference;
    difference.numerator = denominator*frac.numerator - numerator*frac.denominator;
    difference.denominator = least_common_multiple(denominator, frac.denominator);
    simplify(&difference.numerator, &difference.denominator, 2);
    return difference;
}

fraction fraction::operator*(fraction &frac)
{
    fraction multiply;
    multiply.numerator = frac.numerator * numerator;
    multiply.denominator = frac.denominator * denominator;
    simplify(&multiply.numerator, &multiply.denominator, 2);
    return multiply;
}

fraction fraction::operator/(fraction &frac)
{
    fraction division;
    division.numerator = frac.denominator * numerator;
    division.denominator = frac.numerator * denominator;
    simplify(&division.numerator, &division.denominator, 2);
    return division;
}

std::ostream& operator<<(std::ostream &COUT, fraction& frac)
{
    COUT << frac.numerator << "/" << frac.denominator << std::endl;
    return COUT;
}

fraction::~fraction() {}

int main()
{
    fraction f1(3,5);
    fraction f2(4,7);
    fraction f3(4,8);
    fraction f4 = f1 + f2;
    fraction f5 = f3 - f4;
    fraction f6 = f4*f5;
    fraction f7 = f5/f6;
    std::cout << f1 << f2 << f3 << f4 << f5 << f6 << f7 << std::endl;
    return 0;
}