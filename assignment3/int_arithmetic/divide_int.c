#include <stdio.h>

#include "int_arithmetic.h"

int divide_int(int num1, int num2)
{
    if (num2 == 0)
    {
        fprintf(stderr, "Cannot divide by zero\n");
        return 0;
    }

    return num1 / num2;
}
