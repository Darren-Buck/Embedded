#include <stdio.h>

#include "int_arithmetic/int_arithmetic.h"
#include "double_arithmetic/double_arithmetic.h"

void int_library()
{
    int num1 = 10;
    int num2 = 5;
    int res;

    res = add_int(num1, num2);
    printf("add_int: %d\n", res);

    res = subtract_int(num1, num2);
    printf("add_int: %d\n", res);

    res = multiply_int(num1, num2);
    printf("add_int: %d\n", res);

    res = divide_int(num1, num2);
    printf("add_int: %d\n", res);
}

void double_library()
{
    double num1 = 15;
    double num2 = 5;
    double res;

    res = add_double(num1, num2);
    printf("add_double: %f\n", res);

    res = subtract_double(num1, num2);
    printf("add_double: %f\n", res);

    res = multiply_double(num1, num2);
    printf("add_double: %f\n", res);

    res = divide_double(num1, num2);
    printf("add_double: %f\n", res);
}

int main()
{
    int_library();
    double_library();

    return 0;
}