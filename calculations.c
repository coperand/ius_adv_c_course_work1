#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "calculations.h"

//Функции f1, f2, f3
double f1(double x)
{
    return 0.6 * x + 3;
}
double f2(double x)
{
    return pow(x - 2, 3) - 1;
}
double f3(double x)
{ 
    if (x == 0.0)
    {
        printf("Dividing by zero\n");
        exit(EXIT_FAILURE);
    }
    return 3.0 / x;
}

//Производные функций f1, f2, f3
double df1(double x)
{
    return 0.6;
}
double df2(double x)
{
    return 3.0 * pow(x - 2, 2);
}
double df3(double x)
{
    return -3.0 / (x * x);
}

//Количество итераций
int iterations_quantity = 0;

//Функция нахождения корня уравнения f(x)=g(x) на [a, b] с точностью eps (метод бисекции)
double root(double (*f)(double), double (*g)(double), double a, double b, double eps)
{
    double fa = f(a) - g(a);
    double fb = f(b) - g(b);
    if(fa * fb > 0)
    {
        printf("No sign changing\n");
        exit(EXIT_FAILURE);
    }

    double c, fc;
    iterations_quantity = 0;
    while((b - a) / 2.0 > eps)
    {
        c = (a + b) / 2.0;
        fc = f(c) - g(c);
        iterations_quantity++;

        if(fc == 0.0)
            break;

        if(fa * fc < 0)
        {
            b = c;
            fb = fc;
        }
        else
        {
            a = c;
            fa = fc;
        }
    }

    return (a + b) / 2.0;
}

//Функция вычисления интеграла от f(x) на [a, b] с точностью eps (метод трапеций)
double integral(double (*f)(double), double a, double b, double eps)
{
    int n = 1;
    double h = b - a;
    double s_old = h * (f(a) + f(b)) / 2.0;
    double s_new;

    do
    {
        h /= 2.0;
        double sum = 0.0;
        for(int i = 0; i < n; ++i)
            sum += f(a + (2 * i + 1) * h);

        s_new = s_old / 2.0 + h * sum;
        if(fabs(s_new - s_old) < eps)
            break;

        s_old = s_new;
        n *= 2;
    } while(1);

    return s_new;
}
