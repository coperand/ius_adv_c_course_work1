#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "tests.h"
#include "calculations.h"

//Количество итераций
extern int iterations_quantity;

//Точность
extern double eps;

//Функция для сравнения с точностью
int approx_equal(double a, double b, double eps)
{
    return fabs(a - b) <= eps;
}

//Функция для тестирования функции root
void test_root(void)
{
    printf("Testing root...\n");

    //Ожидаемые значения
    const double expected_f1_f2 = 3.847760245113858;
    const double expected_f1_f3 = 0.8541019662496845;
    const double expected_f2_f3 = 3.243928853902777;

    //Test 1: f1 = f2
    if(!approx_equal(root(f1, f2, 3.8, 3.9, eps), expected_f1_f2, eps))
    {
        printf("Test 1 failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Test 1 succeeded\n");

    //Test 2: f1 = f3
    if(!approx_equal(root(f1, f3, 0.5, 1.0, eps), expected_f1_f3, eps))
    {
        printf("Test 2 failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Test 2 succeeded\n");

    //Test 3: f2 = f3
    if(!approx_equal(root(f2, f3, 3.2, 3.3, eps), expected_f2_f3, eps))
    {
        printf("Test 3 failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Test 3 succeeded\n");

    printf("Root tests passed\n\n");
}

//Функция для тестирования функции integral
void test_integral(void)
{
    printf("Testing integral...\n");

    //Test 1: ∫0-1 (0.6x + 3) dx = 3.3
    if(!approx_equal(integral(f1, 0.0, 1.0, eps), 3.3, eps))
    {
        printf("Test 1 failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Test 1 succeeded\n");

    //Test 2: ∫1-4 (3/x) dx = 3*ln(4) = 4.1588830834
    if (!approx_equal(integral(f3, 1.0, 4.0, eps), 3.0 * log(4.0), 1e-6))
    {
        printf("Test 2 failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Test 2 succeeded\n");

    printf("Integral tests passed\n");
}
