//#include "fraction.h"
#include "operation.h"

int main()
{
    fraction a(3,5);
    fraction b(4,7);

    operation ADD;
    ADD.display(a);
    ADD.display(b);

    return 0;
}