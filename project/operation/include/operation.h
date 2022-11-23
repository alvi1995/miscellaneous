#pragma once
#include "fraction.h"

int least_common_multiple(int d1, int d2);

class operation
{
    public:
        friend int least_common_multiple(int d1, int d2);
        void display(fraction a);
        ~operation();
};