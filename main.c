#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#define VERSHINY 5
#define MAXREBER (VERSHINY*VERSHINY)

int main() {
    setlocale(LC_ALL, "Russian");
    int matr_smezh[VERSHINY][VERSHINY] = { 0 };
    int stepen[VERSHINY] = { 0 };
    int petlya[VERSHINY] = { 0 };
    int razmer = 0;
    int svyaz_u[MAXREBER], svyaz_v[MAXREBER], kol_reber = 0;

    srand(time(NULL));

    for (int i = 0; i < VERSHINY; i++)
        for (int j = i; j < VERSHINY; j++) {
            if (i == j && rand() % 5 < 2) matr_smezh[i][i] = 1;
            else if (i != j && rand() % 5 < 2) matr_smezh[i][j] = matr_smezh[j][i] = 1;
        }
    for (int i = 0; i < VERSHINY; i++)
        for (int j = i; j < VERSHINY; j++)
            if (matr_smezh[i][j]) {
                svyaz_u[kol_reber] = i;
                svyaz_v[kol_reber] = j;
                kol_reber++;
                razmer++;
            }
    int maks_stepen = 0;
    for (int i = 0; i < VERSHINY; i++) {
        petlya[i] = matr_smezh[i][i];
        int summa = 0;
        for (int j = 0; j < VERSHINY; j++) summa += matr_smezh[i][j];
        stepen[i] = summa + petlya[i];
        if (stepen[i] > maks_stepen) maks_stepen = stepen[i];
    }

    printf("Количество вершин: %d\n", VERSHINY);
    printf("Размер графа (число рёбер, включая петли): %d\n\n", razmer);

    printf("Матрица смежности:\n");
    for (int i = 0; i < VERSHINY; i++) {
        for (int j = 0; j < VERSHINY; j++)
            printf("%2d ", matr_smezh[i][j]);
        printf("\n");
    }
    printf("\nМатрица инцидентности:\n");
    for (int v = 0; v < VERSHINY; v++) {
        for (int r = 0; r < kol_reber; r++) {
            if (svyaz_u[r] == svyaz_v[r])
                printf("%2d ", (v == svyaz_u[r]) ? 2 : 0);
            else
                printf("%2d ", (v == svyaz_u[r] || v == svyaz_v[r]) ? 1 : 0);
        }
        printf("\n");
    }
    printf("\n i |");
    for (int j = 0; j < VERSHINY; j++) printf(" %d", j);
    printf(" | петля | степень\n");
    printf("    ");
    for (int j = 0; j < VERSHINY; j++);
    printf("\n");
    for (int i = 0; i < VERSHINY; i++) {
        printf(" %d |", i);
        for (int j = 0; j < VERSHINY; j++)
            printf(" %d", matr_smezh[i][j]);
        printf(" |   %d   |   %d\n", petlya[i], stepen[i]);
    }
    printf("\nСвязи вершин:\n");
    for (int i = 0; i < VERSHINY; i++) {
        printf("Вершина %d: ", i);
        int pervaya = 1;
        for (int j = 0; j < VERSHINY; j++) {
            if (matr_smezh[i][j]) {
                if (i == j)
                    printf("%s(петля)", pervaya ? "" : ", ");
                else
                    printf("%s%d", pervaya ? "" : ", ", j);
                pervaya = 0;
            }
        }
        if (pervaya) printf("нет соседей");
        printf("\n");
    }
    printf("\nТипы вершин:\n");
    for (int i = 0; i < VERSHINY; i++) {
        if (stepen[i] == 0)
            printf("Вершина %d — изолированная\n", i);
        else if (stepen[i] == 1)
            printf("Вершина %d — концевая вершина\n", i);
        else if (stepen[i] == maks_stepen)
            printf("Вершина %d — доминирующая вершина\n", i);
        else if (petlya[i])
            printf("Вершина %d — с петлёй\n", i);
        else
            printf("Вершина %d — обычная\n", i);
    }
    return 0;
}
