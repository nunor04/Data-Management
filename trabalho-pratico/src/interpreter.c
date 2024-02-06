/*
    Módulo responsável por indicar (dependendo do nº da query),
        qual query executar
*/

#include <stdio.h>
#include <stdlib.h>

#include "../include/interpreter.h"
#include <sys/resource.h>


void interpreter(char *path, Catalogs_Manager *manager, int test) {
    FILE *finput;
    char *linha = NULL;
    size_t line_buffer_size = 0;
    __ssize_t characters_read;

    char *aux = malloc(strlen(path) + 1);

    if (aux == NULL) {
        fprintf(stderr, "Error allocating memory for file path\n");
        return;
    }

    snprintf(aux, strlen(path) + 1, "%s", path);
    finput = fopen(aux, "r");
    if (finput == NULL) {
        perror("Erro ao abrir o ficheiro(allqueries)");
        free(aux);
        return;
    }
    
    double testarray[10];
    long QMem[10];
    
    if(test == 1)
    {
      for(int i = 0; i < 10; i++) testarray[i] = 0;
      for(int i = 0; i < 10; i++) QMem[i] = 0;
    } 

    //int n_total_linhas = conta_linhas_ficheiro(aux);
    int contador_linhas = 1;
    int formato; //1 ou 1F (por exemplo)
    
    /*
        Colocar uma cena para escolher se queremos modo batch ou interativo
    */
    char hotel_id[7];
   
    while((characters_read = getline(&linha, &line_buffer_size, finput)) != -1){
        char query_number[3]; //2 + '\0
            if (sscanf(linha, "%s", query_number) == 1) {
                // Queries
                switch (query_number[0]) {
                    //  case '1':
                    // //     query1();
                    //      testarray[0] = 0;
                    //      break;
                    // case '2':
                    // //     query2();
                    //      testarray[1] = 0;
                    //      break;
                    case '3':
                     if(test != 1)
                       {  
                        if (query_number[1] == 'F') {
                            formato = 2;
                        } else {
                            formato = 1;
                        }

                        Query3 result;
    
                        if (sscanf(linha, "%*s %s", hotel_id) == 1) {
                            // Initialize o result com o hotel_id
                            result = query3(manager, hotel_id);
                            batch_mode_q3(contador_linhas, result, formato, hotel_id, 0);
                        } else {
                            // Inicializa o result sem o hotel_id
                            result = query3(manager, "");
                            batch_mode_q3(contador_linhas, result, formato, hotel_id, 1);
                        }
                        break;
                       }
                      else
                       {
                         struct rusage inicio, fim;
                         clock_t start_time = clock();

                         getrusage(RUSAGE_SELF, &inicio);
 
                         if (query_number[1] == 'F') {
                            formato = 2;
                        } else {
                            formato = 1;
                        }

                        Query3 result;
    
                        if (sscanf(linha, "%*s %s", hotel_id) == 1) {
                            // Initialize o result com o hotel_id
                            result = query3(manager, hotel_id);
                            batch_mode_q3(contador_linhas, result, formato, hotel_id, 0);
                        } else {
                            // Inicializa o result sem o hotel_id
                            result = query3(manager, "");
                            batch_mode_q3(contador_linhas, result, formato, hotel_id, 1);
                        }
                        clock_t end_time = clock();
                        double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
                        testarray[2]+= elapsed_time;

                        getrusage(RUSAGE_SELF, &fim);

                        long diff_mem = fim.ru_maxrss - inicio.ru_maxrss;
                        QMem[2]+= diff_mem;

                        break;
                       }
                    
                    case '4':
                      if(test != 1) 
                      {  
                        if (query_number[1] == 'F') {
                            formato = 2;
                        } else {
                            formato = 1;
                        }

                        QueryResult q4;

                        if (sscanf(linha, "%*s %s", hotel_id) == 1) {
                            // Initialize o result com o hotel_id
                            q4 = query4(manager, hotel_id);
                            batch_mode_q4(contador_linhas, q4, formato, hotel_id, 0);
                        } else {
                            // Inicializa o result sem o hotel_id
                            q4 = query4(manager, "");
                            batch_mode_q4(contador_linhas, q4, formato, hotel_id, 1);
                        }                       
                        break;
                      }
                      else
                      {
                        struct rusage inicio, fim;
                        clock_t start_time = clock();

                        getrusage(RUSAGE_SELF, &inicio);

                        if (query_number[1] == 'F') {
                            formato = 2;
                        } else {
                            formato = 1;
                        }

                        QueryResult q4;

                        if (sscanf(linha, "%*s %s", hotel_id) == 1) {
                            // Initialize o result com o hotel_id
                            q4 = query4(manager, hotel_id);
                            batch_mode_q4(contador_linhas, q4, formato, hotel_id, 0);
                        } else {
                            // Inicializa o result sem o hotel_id
                            q4 = query4(manager, "");
                            batch_mode_q4(contador_linhas, q4, formato, hotel_id, 1);
                        }
                        clock_t end_time = clock();
                        
                        double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
                        testarray[3] += elapsed_time;

                        getrusage(RUSAGE_SELF, &fim);

                        long diff_mem = fim.ru_maxrss - inicio.ru_maxrss;
                        QMem[3]+= diff_mem;
                        break;
                      }
                    //  case '5':
                    // //     query5();
                    //      testarray[4] = 0;
                    //      break;
                    //  case '6':
                    // //     query6();
                    //      testarray[5] = 0;
                    //      break;
                    case '7':
                      if(test != 1) 
                       {
                        if (query_number[1] == 'F') {
                            formato = 2;
                        } else {
                            formato = 1;
                        }

                        Q7 q7;
                        char N[10];

                        if (sscanf(linha, "%*s %s", N) == 1) {
                            // printf("Prefix: '%s'\n", prefix);
                            // Initialize o result com o hotel_id
                            q7 = query7(manager, N);
                            batch_mode_q7(contador_linhas, q7, formato, 0);
                        } else {
                            // Inicializa o result sem o hotel_id
                            q7 = query7(manager, "");
                            batch_mode_q7(contador_linhas, q7, formato, 1);
                        }
                        break;
                       }
                       else
                       {
                         struct rusage inicio, fim;
                         clock_t start_time = clock();

                         getrusage(RUSAGE_SELF, &inicio);

                         if (query_number[1] == 'F') {
                            formato = 2;
                        } else {
                            formato = 1;
                        }

                        Q7 q7;
                        char N[10];

                        if (sscanf(linha, "%*s %s", N) == 1) {
                            // printf("Prefix: '%s'\n", prefix);
                            // Initialize o result com o hotel_id
                            q7 = query7(manager, N);
                            batch_mode_q7(contador_linhas, q7, formato, 0);
                        } else {
                            // Inicializa o result sem o hotel_id
                            q7 = query7(manager, "");
                            batch_mode_q7(contador_linhas, q7, formato, 1);
                        }
                        
                        clock_t end_time = clock();
                        double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
                        testarray[6] += elapsed_time;

                        getrusage(RUSAGE_SELF, &fim);

                        long diff_mem = fim.ru_maxrss - inicio.ru_maxrss;
                        QMem[6]+= diff_mem;
                        
                        break;
                       }
                    // case '8':
                    // //     query8();
                    //      testarray[7] = 0;
                    //      break;
                    case '9':
                       if(test != 1) 
                       {
                        if (query_number[1] == 'F') {
                            formato = 2;
                        } else {
                            formato = 1;
                        }

                        Q9 q9;
                        char prefix[20];

                        if (sscanf(linha, "%*s %[^\n]", prefix) == 1) {
                            // printf("Prefix: '%s'\n", prefix);
                            // Initialize o result com o hotel_id
                            q9 = query9(manager, prefix);
                            batch_mode_q9(contador_linhas, q9, formato, prefix, 0);
                        } else {
                            // Inicializa o result sem o hotel_id
                            q9 = query9(manager, "");
                            batch_mode_q9(contador_linhas, q9, formato, prefix, 1);
                        }
                        break;
                       }
                       else
                       {
                        struct rusage inicio, fim;
                        clock_t start_time = clock();
                         
                        getrusage(RUSAGE_SELF, &inicio); 

                        if (query_number[1] == 'F') {
                            formato = 2;
                        } else {
                            formato = 1;
                        }

                        Q9 q9;
                        char prefix[20];

                        if (sscanf(linha, "%*s %[^\n]", prefix) == 1) {
                            // printf("Prefix: '%s'\n", prefix);
                            // Initialize o result com o hotel_id
                            q9 = query9(manager, prefix);
                            batch_mode_q9(contador_linhas, q9, formato, prefix, 0);
                        } else {
                            // Inicializa o result sem o hotel_id
                            q9 = query9(manager, "");
                            batch_mode_q9(contador_linhas, q9, formato, prefix, 1);
                        }
                        clock_t end_time = clock();
                        double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
                        testarray[8] += elapsed_time;
                        
                        getrusage(RUSAGE_SELF, &fim);

                        long diff_mem = fim.ru_maxrss - inicio.ru_maxrss;
                        QMem[8]+= diff_mem;
                        //printf("%.3f\n", elapsed_time);
                        break;
                       }
                    //  case '10':
                    // //     query10();
                    //      testarray[9] = 0;
                    //      break;
                    default:
                        break;
                }
            }
        contador_linhas++;
    }
    if(test == 1) testsoutput(testarray,QMem);
    free(linha);
    fclose(finput);
    free(aux);
}