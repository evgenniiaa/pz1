#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

double calculate_Y(double x);
double calculate_V(double x);
void tabulate(double (*func)(double), double a, double b, double h, const char* name, int is_V);
void print_graph(double (*func)(double), double a, double b, double h, const char* name, int is_V);

int main() {
    setlocale(LC_ALL, "Russian");

    int action;
    double x, a, b, h;
    int interval_type;

    do {
        printf("\n--- МЕНЮ ---\n");
        printf("1. Вычислить Y(x) в точке\n");
        printf("2. Вычислить V(x) в точке\n");
        printf("3. Табулировать Y(x)\n");
        printf("4. Табулировать V(x)\n");
        printf("5. Построить график Y(x)\n");
        printf("6. Построить график V(x)\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");

        if (scanf("%d", &action) != 1) {
            printf("Ошибка ввода. Введите число.\n");
            while (getchar() != '\n');
            continue;
        }

        if (action == 0) break;

        if (action < 1 || action > 6) {
            printf("Неверный пункт меню.\n");
            continue;
        }

        if (action == 1 || action == 2) {
            printf("Введите x: ");
            if (scanf("%lf", &x) != 1) {
                printf("Ошибка ввода.\n");
                while (getchar() != '\n');
                continue;
            }

            if (action == 1) {
                printf("Y(%.4lf) = %.4lf\n", x, calculate_Y(x));
            }
            else {
                if (x > 1) {
                    printf("V(%.4lf) = %.4lf\n", x, calculate_V(x));
                }
                else {
                    printf("Ошибка: для x > 1 функция V(x) не определена (ОДЗ).\n");
                }
            }
        }
        else {
            printf("\nВыберите тип промежутка:\n");
            printf("1. Отрезок [a, b]\n");
            printf("2. Интервал (a, b)\n");
            printf("3. Полуинтервал (a, b]\n");
            printf("4. Полуинтервал [a, b)\n");
            printf("Ваш выбор: ");

            if (scanf("%d", &interval_type) != 1 || interval_type < 1 || interval_type > 4) {
                printf("Ошибка выбора промежутка.\n");
                while (getchar() != '\n');
                continue;
            }

            printf("Введите начало (a): ");
            if (scanf("%lf", &a) != 1) { while (getchar() != '\n'); continue; }
            printf("Введите конец (b): ");
            if (scanf("%lf", &b) != 1) { while (getchar() != '\n'); continue; }
            printf("Введите шаг (h): ");
            if (scanf("%lf", &h) != 1) { while (getchar() != '\n'); continue; }

            if (h <= 0) {
                printf("Ошибка: шаг должен быть положительным.\n");
                continue;
            }
            if (a >= b) {
                printf("Ошибка: начало должно быть меньше конца.\n");
                continue;
            }

            if (interval_type == 2 || interval_type == 3) a += 1e-9;
            if (interval_type == 2 || interval_type == 4) b -= 1e-9;

            if (action == 3) {
                tabulate(calculate_Y, a, b, h, "Y(x)", 0);
            }
            else if (action == 4) {
                tabulate(calculate_V, a, b, h, "V(x)", 1);
            }
            else if (action == 5) {
                print_graph(calculate_Y, a, b, h, "Y(x)", 0);
            }
            else if (action == 6) {
                if (b <= 1) {
                    printf("График V(x) не может быть построен (ОДЗ: x > 1).\n");
                }
                else {
                    print_graph(calculate_V, a, b, h, "V(x)", 1);
                }
            }
        }
    } while (1);

    return 0;
}

double calculate_Y(double x) {
    return pow(x, 3) + 2 * x + sin(x);
}

double calculate_V(double x) {
    if (x < -1) {
        return log(1 + pow(x, 2)) - 2;
    }
    else if (x >= -1 && x <= 1) {
        return pow(x, 2) - 1;
    }
    else {
        return sqrt(x - 1) / (1 + pow(x, 2));
    }
}

void tabulate(double (*func)(double), double a, double b, double h, const char* name, int is_V) {
    printf("\nТаблица значений для %s:\n", name);
    printf(" x\t\t%s\n", name);
    printf("------------------------\n");

    for (double i = a; i <= b + 1e-9; i += h) {
        if (is_V && i <= 1) {
            printf("%.4lf\t\t--- (не определена)\n", i);
        }
        else {
            printf("%.4lf\t\t%.4lf\n", i, func(i));
        }
    }
}

void print_graph(double (*func)(double), double a, double b, double h, const char* name, int is_V) {
    printf("\nПсевдографик для %s:\n", name);
    printf("Ось Y\n");

    double max_val = 0;
    for (double i = a; i <= b + 1e-9; i += h) {
        if (is_V && i <= 1) continue;
        double val = func(i);
        if (val > max_val) max_val = val;
    }

    int rows = 10;
    for (int r = rows; r >= -rows; r--) {
        double level = max_val * r / rows;
        printf("%7.2lf | ", level);

        for (double x = a; x <= b + 1e-9; x += h) {
            if (is_V && x <= 1) {
                printf(" ");
                continue;
            }
            double val = func(x);
            if (fabs(val - level) <= (max_val / rows) / 2.0) {
                printf("*");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }

    printf("        +");
    for (double x = a; x <= b + 1e-9; x += h) printf("-");
    printf("\n         ");
    printf("%.1lf", a);
    for (int i = 0; i < 5; i++) printf(" ");
    printf("%.1lf\n", b);
}
