#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <windows.h>

double calculate_Y(double x) {
    return pow(x, 3) + 2 * x + sin(x);
}

double calculate_V(double x) {
    double result;

    if (x < -1) {
        result = log(1 + pow(x, 2)) - 2;
    }
    else if (x >= -1 && x <= 1) {
        result = pow(x, 2) - 1;
    }
    else {
        result = sqrt(x - 1) / (1 + pow(x, 2));
    }

    return result;
}

void zadanie1() {
    double x;
    int choice;

    printf("1. Y(x) = x^3 + 2x + sin(x)\n");
    printf("2. V(x)\n");
    printf("Выберите функцию (1 или 2): ");

    if (scanf("%d", &choice) != 1) {
        printf("Ошибка ввода!\n");
        return;
    }

    printf("Введите x: ");
    if (scanf("%lf", &x) != 1) {
        printf("Ошибка ввода!\n");
        return;
    }

    if (choice == 1) {
        printf("Y(%.4lf) = %.4lf\n", x, calculate_Y(x));
    }
    else if (choice == 2) {
        printf("V(%.4lf) = %.4lf\n", x, calculate_V(x));
    }
    else {
        printf("Неверный выбор.\n");
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    zadanie1();

    return 0;
}
