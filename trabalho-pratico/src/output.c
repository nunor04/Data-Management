/*
    Módulo responsável por dar output de cada query (batch e interativo)

    Primeiro o user tem de escolher se quer modo batch ou interativo
*/
#include <stdio.h>
#include "../include/output.h"

void batch_mode_q3(int N, Query3 result, int formato, const char* targetHotel, int ficheiroVazio){

    const char* filename_base = "../trabalho-pratico/Resultados/commandXYZ_output.txt";
    size_t file_size = strlen(filename_base) + 1;  // + '\0'
    char* filename = malloc(file_size);
    snprintf(filename, file_size, "../trabalho-pratico/Resultados/command%d_output.txt", N);

    FILE* foutput = fopen(filename, "w");
    
    if(ficheiroVazio == 1){
        fclose(foutput);
    } else {
        if (foutput != NULL) {
            if (result.media != 0) {
                    // Dar print no ficheiro dependendo do formato (3 ou 3F)
                    if (formato == 1) {
                        fprintf(foutput, "%.3f\n", result.media);
                    } else if (formato == 2) {
                        fprintf(foutput, "--- 1 ---\nrating: %.3f\n", result.media);
                    } else {
                        fprintf(foutput, "Nenhuma avaliação encontrada.\n");
                    }

                }   
                // Fechar o ficheiro de output
                fclose(foutput);
                printf("File '%s' created successfully.\n", filename);
            } else {
            perror("Error creating output file");
        }

        free(filename);
    }
}


void batch_mode_q4(int N, QueryResult result, int formato, const char* hotel_id, int ficheiroVazio) {
    const char* filename_base = "../trabalho-pratico/Resultados/commandXYZ_output.txt";
    size_t file_size = strlen(filename_base) + 1;  // + '\0'
    char* filename = malloc(file_size);
    snprintf(filename, file_size, "../trabalho-pratico/Resultados/command%d_output.txt", N);

    FILE* foutput = fopen(filename, "w");

    if (ficheiroVazio == 1) {
        fclose(foutput);
    } else {
        if (foutput != NULL) {
            if (result.contador_reservations > 0) {
                // Dar print no ficheiro 
                for (int i = 0; i < result.contador_reservations; i++){
                    if (formato == 1) {
                        fprintf(foutput, "%s;%s;%s;%s;%s;%.3f\n", result.id[i], result.begin_date[i], result.end_date[i], result.user_id[i], result.rating[i], result.preco_total[i]);
                    } else if(formato == 2){ 
                        if(i == result.contador_reservations - 1) fprintf(foutput,"--- %d ---\nid: %s\nbegin_date: %s\nend_date: %s\nuser_id: %s\nrating: %s\ntotal_price: %.3f\n", i+1, result.id[i], result.begin_date[i], result.end_date[i], result.user_id[i], result.rating[i], result.preco_total[i]);
                        else fprintf(foutput,"--- %d ---\nid: %s\nbegin_date: %s\nend_date: %s\nuser_id: %s\nrating: %s\ntotal_price: %.3f\n\n", i+1, result.id[i], result.begin_date[i], result.end_date[i], result.user_id[i], result.rating[i], result.preco_total[i]);
                    }
                }
            } else {
                fprintf(foutput, "Nenhuma reserva encontrada para este hotel%s.\n", hotel_id);
            }

            // Fechar o ficheiro de output
            fclose(foutput);
            printf("File '%s' created successfully.\n", filename);
        } else {
            perror("Error creating output file");
        }

        free(filename);
    }
    // Libertar a memória alocada para os arrays na QueryResult
    for (int j = 0; j < result.contador_reservations; j++) {
        g_free(result.id[j]);
        g_free(result.begin_date[j]);
        g_free(result.end_date[j]);
        g_free(result.user_id[j]);
        g_free(result.rating[j]);
    }

    g_free(result.id);
    g_free(result.begin_date);
    g_free(result.end_date);
    g_free(result.user_id);
    g_free(result.rating);
    g_free(result.preco_total);
}

void batch_mode_q9(int N, Q9 result, int formato, const char* prefix, int ficheiroVazio) {
    const char* filename_base = "../trabalho-pratico/Resultados/commandXYZ_output.txt";
    size_t file_size = strlen(filename_base) + 1;  // + '\0'
    char* filename = malloc(file_size);
    snprintf(filename, file_size, "../trabalho-pratico/Resultados/command%d_output.txt", N);

    FILE* foutput = fopen(filename, "w");

    if (ficheiroVazio == 1) {
        fclose(foutput);
    } else {
        if (foutput != NULL) {
            if (result.contador > 0) {
                // Dar print no ficheiro
                for (int i = 0; i < result.contador; i++) {
                    if (formato == 1) {
                        fprintf(foutput, "%s;%s\n", result.id[i], result.name[i]);
                    } else if (formato == 2) {
                        if(i == result.contador - 1) fprintf(foutput, "--- %d ---\nid: %s\nname: %s\n", i + 1, result.id[i], result.name[i]);
                        else fprintf(foutput, "--- %d ---\nid: %s\nname: %s\n\n", i + 1, result.id[i], result.name[i]);
                    }
                }
            } else {
                
            }

            // Fechar o ficheiro de output
            fclose(foutput);
            printf("File '%s' created successfully.\n", filename);
        } else {
            perror("Error creating output file");
        }

        free(filename);
    }

    // Liberar a memória alocada para os arrays na QueryResult
    for (int j = 0; j < result.contador; j++) {
        g_free(result.id[j]);
        g_free(result.name[j]);
    }

    g_free(result.id);
    g_free(result.name);
}

void batch_mode_q7(int N, Q7 result, int formato, int ficheiroVazio) {
    const char* filename_base = "../trabalho-pratico/Resultados/commandXYZ_output.txt";
    size_t file_size = strlen(filename_base) + 1;  // + '\0'
    char* filename = malloc(file_size);
    snprintf(filename, file_size, "../trabalho-pratico/Resultados/command%d_output.txt",N);

    FILE* foutput = fopen(filename, "w");

    if (ficheiroVazio == 1) {
        fclose(foutput);
    } else {
        if (foutput != NULL) {
            if (result.contador > 0) {
                // Dar print no ficheiro
                for (int i = 0; i < result.contador; i++) {
                    if (formato == 1) {
                        fprintf(foutput, "%s;%d\n", result.origin[i],result.median[i]);
                    } else if (formato == 2) {
                        if(i == result.contador - 1) fprintf(foutput, "--- %d ---\nname: %s\nmedian: %d\n", i + 1, result.origin[i],result.median[i]);
                        else fprintf(foutput, "--- %d ---\nname: %s\nmedian: %d\n\n", i + 1, result.origin[i],result.median[i]);
                    }
                }
            } else {
                fprintf(foutput, "No results to display.\n");
            }

            // Fechar o ficheiro de output
            fclose(foutput);
            printf("File '%s' created successfully.\n", filename);
        } else {
            perror("Error creating output file");
        }

        free(filename);
    }

    // Libertar a memória alocada para o array result
    for (int j = 0; j < result.contador; j++) {
        g_free(result.origin[j]);
    }

    g_free(result.origin);
    g_free(result.median);
}

void testsoutput(double testarray[], long QMem[])
{
    FILE *file_output_tests;
    file_output_tests = fopen("../trabalho-pratico/Resultados/testes.txt", "w");

    for(int i = 0; i < 10; i++)
    {
        fprintf(file_output_tests,"---- Query %d ----\n", i+1);
        fprintf(file_output_tests,"Time taken: %.3f\n",testarray[i]);
        fprintf(file_output_tests,"Used Memory: %ld KBC\n\n", QMem[i]);
    }
   fclose(file_output_tests);
}
