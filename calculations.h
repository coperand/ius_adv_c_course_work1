#ifndef __CALCULATIONS_H__
#define __CALCULATIONS_H__

//Функция нахождения корня уравнения f(x)=g(x) на [a, b] с точностью eps (метод бисекции)
double root(double (*f)(double), double (*g)(double), double a, double b, double eps);

//Функция вычисления интеграла от f(x) на [a, b] с точностью eps (метод трапеций)
double integral(double (*f)(double), double a, double b, double eps);

//Функции f1, f2, f3 и их производные
double f1(double x);
double f2(double x);
double f3(double x);
double df1(double x);
double df2(double x);
double df3(double x);

#endif
