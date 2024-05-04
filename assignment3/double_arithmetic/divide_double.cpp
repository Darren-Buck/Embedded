#include <iostream>

#include "double_arithmetic.h"

double divide_double(double num1, double num2)
{
    if (num2 == 0)
    {
        std::cerr << "Cannot divide by zero\n";
        return 0;
    }

    return num1 / num2;
}
