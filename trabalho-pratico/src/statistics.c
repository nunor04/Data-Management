#include "../include/statistics.h"
#include <stdio.h>
#include <stdlib.h>

// Função de comparação para a função qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Função para calcular a mediana de um conjunto de dados
int calcularMediana(int *dados, int tamanho) {
    // Ordenar o conjunto de dados
    qsort(dados, tamanho, sizeof(int), compare);

    // Calcular a mediana
    if (tamanho % 2 == 0) {
        // Número par de elementos (média dos dois valores centrais)
        int meio1 = dados[(tamanho - 1) / 2];
        int meio2 = dados[tamanho / 2];
        return (int)(meio1 + meio2) / 2.0;
    } else {
        // Número ímpar de elementos (valor central)
        return (int)dados[tamanho / 2];
    }
}

// Função para calcular o atraso de um voo
int calculate_delay_in_seconds(const char* schedule_departure_date, const char* real_departure_date) {
    // Parsing da schedule_departure_date
    int schedule_year, schedule_month, schedule_day, schedule_hour, schedule_min, schedule_sec;
    if (sscanf(schedule_departure_date, "%d/%d/%d %d:%d:%d;", &schedule_year, &schedule_month, &schedule_day,
               &schedule_hour, &schedule_min, &schedule_sec) != 6) {
        return 0;  // Return 0 em caso de erro
    }

    // Parsing da real_departure_date
    int real_year, real_month, real_day, real_hour, real_min, real_sec;
    if (sscanf(real_departure_date, "%d/%d/%d %d:%d:%d;", &real_year, &real_month, &real_day,
               &real_hour, &real_min, &real_sec) != 6) {
        return 0;  // Return 0 em caso de erro
    }

    // Calcular o atraso em segundos
    int delay = ((real_hour - schedule_hour) * 3600 +
                 (real_min - schedule_min) * 60 +
                 (real_sec - schedule_sec));

    return delay;
}