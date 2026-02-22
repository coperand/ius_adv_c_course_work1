#include <stdio.h>
#include <stdbool.h>

#include "calculations.h"
#include "tests.h"

//Точность
double eps = 1e-10;

int main(int argc, char* argv[])
{
    printf("Intersection of f1 and f2: x = %.10f\n", root(f1, f2, 3.8, 3.9, eps));

    test_root();
    test_integral();
}
