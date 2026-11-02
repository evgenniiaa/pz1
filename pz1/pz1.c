#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <windows.h>

int calculate_Y(double x, double* result) {
    *result = pow(x, 3) + 2 * x + sin(x);
    return 1;
}

int calculate_V(double x, double* result) {
    if (x < -1) {
        *result = log(1 + pow(x, 2)) - 2;
    }
    else if (x >= -1 && x <= 1) {
        *result = pow(x, 2) - 1;
    }
    else {
        *result = sqrt(x - 1) / (1 + pow(x, 2));
    }
    return 1;
}

void print_table(int func_choice, double a, double b, double h) {
    double x, res;

    if (h == 0) {
        printf("Ошибка: шаг не может быть равен нулю.\n");
        return;
    }

    printf("\n x\t\t%s\n", (func_choice == 1) ? "Y(x)" : "V(x)");

    for (x = a; (h > 0) ? (x <= b + 1e-9) : (x >= b - 1e-9); x += h) {
        if (func_choice == 1) {
            calculate_Y(x, &res);
        }
        else {
            calculate_V(x, &res);
        }
        printf("%.4lf\t\t%.4lf\n", x, res);
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;
    double a, b, h;

    printf("1. Y(x) = x^3 + 2x + sin(x)\n");
    printf("2. V(x)\n");
    printf("Выберите функцию (1 или 2): ");
    scanf("%d", &choice);

    printf("Введите начало интервала: ");
    scanf("%lf", &a);

    printf("Введите конец интервала: ");
    scanf("%lf", &b);

    printf("Введите шаг: ");
    scanf("%lf", &h);

    print_table(choice, a, b, h);

    return 0;
}
