#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>

#include "calculations.h"
#include "tests.h"

//Структура с аргументами командной строки
struct command_line_arguments
{
    int abscissas;
    int iterations;
    int tests;
};

//Количество итераций
extern int iterations_quantity;

//Точность
double eps = 1e-10;

//Функция разбора аргументов командной строки
struct command_line_arguments parse_args(int argc, char* argv[])
{
    int opt = 0;
    char help_str[] =
    "Options:\n"
    "-h, --help                 - Print help and exit\n"
    "-a, --abscissas            - Print abscissas\n"
    "-i, --iterations           - Print iterations\n"
    "-t, --tests                - Run tests\n";

    const struct option long_opts[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"abscissas", no_argument, NULL, 'a'},
        {"iterations", no_argument, NULL, 'i'},
        {"tests", no_argument, NULL, 't'},
        {NULL, 0, NULL, 0}
    };

    //Структура с разобранными аргументами командной строки
    struct command_line_arguments arguments;
    memset(&arguments, 0, sizeof(arguments));

    while( (opt = getopt_long(argc, argv, "hait", long_opts, NULL)) != -1 )
    {
        switch (opt)
        {
            case 'h':
                printf("%s", help_str);
                exit(EXIT_SUCCESS);
            case 'a':
                arguments.abscissas = 1;
                break;
            case 'i':
                arguments.iterations = 1;
                break;
            case 't':
                arguments.tests = 1;
                break;
            default:
                printf("Failed to parse argument: %s\n", optarg);
                exit(EXIT_FAILURE);
        }
    }

    return arguments;
}

//Функция подсчёта площади
void compute_area(int abscissas, int iterations)
{
    //Находим пересечение f1 и f2
    double x12 = root(f1, f2, 3.8, 3.9, eps);
    if(abscissas)
        printf("Intersection of f1 and f2: x = %.10f\n", x12);
    if(iterations)
        printf("Iterations for f1=f2: %d\n", iterations_quantity);
    if(abscissas || iterations)
        printf("\n");

    //Находим пересечение f1 и f3
    double x13 = root(f1, f3, 0.5, 1.0, eps);
    if(abscissas)
        printf("Intersection of f1 and f3: x = %.10f\n", x13);
    if(iterations)
        printf("Iterations for f1=f3: %d\n", iterations_quantity);
    if(abscissas || iterations)
        printf("\n");

    //Находим пересечение f2 и f3
    double x23 = root(f2, f3, 3.2, 3.3, eps);
    if(abscissas)
        printf("Intersection of f2 and f3: x = %.10f\n", x23);
    if(iterations)
        printf("Iterations for f2=f3: %d\n", iterations_quantity);
    if(abscissas || iterations)
        printf("\n");

    //Считаем и выводим площадь
    printf("Calculated area: %.10f\n", integral(f1, x13, x23, eps) - integral(f3, x13, x23, eps) + integral(f1, x23, x12, eps) - integral(f2, x23, x12, eps));
}

int main(int argc, char* argv[])
{
    //Разбираем аргументы командной строки
    struct command_line_arguments arguments = parse_args(argc, argv);

    //Прогоняем тесты при необходимости
    if(arguments.tests)
    {
        test_root();
        test_integral();
        exit(EXIT_SUCCESS);
    }

    //Подсчитываем площадь
    compute_area(arguments.abscissas, arguments.iterations);
}
