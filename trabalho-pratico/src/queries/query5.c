// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include "../include/structs/flights.h"
// #include "../include/queries.h"


//     //origin begin_date end_date        -> estas ultimas duas podem ou não ter aspas
//     //5 LIS "2021/01/01 00:00:00" "2022/12/31 23:59:59" <- exemplo

// #define MAX_INFO_SIZE 50  // Adjust the size based on your requirements
// #define MAX_DATE_SIZE 20  // Adjust the size based on your requirements

// void removeChar(char *str)  //remove um caracter de uma string, neste caso as aspas
// {
//         char *src, *dst;
//     for (src = dst = str; *src != '\0'; src++)
//     {
//         *dst = *src;
//         if (*dst != '"')
//             dst++;
//     }

//     *dst = '\0';
// }

// void swap(int *xp, int *yp)     //troca simples para o sort
// {
//         int temp = *xp;
//     *xp = *yp;
//     *yp = temp;
// }

// void flightOrder(int *order, int valcount)
// {
//         int i,
//             j,
//             result,
//             tiebreaker;
//     for (i = 0; i < valcount - 1; i++)
//     {
//         for (j = 0; j < valcount - i - 1; j++)
//         {
//             result = strcmp(global_flight_data[order[j]].schedule_departure_date,
//                             global_flight_data[order[j + 1]].schedule_departure_date);
//             if (result < 0)
//                 swap(&order[j], &order[j + 1]);     //comparar as datas e por primeiro a mais antiga
//             if (result == 0)
//             {
//                 tiebreaker = strcmp(global_flight_data[order[j]].id, global_flight_data[order[j + 1]].id);
//                 if (tiebreaker < 0)
//                     swap(&order[j], &order[j + 1]);     //em caso de empate, vai por id de voo
//             }
//         }
//     }
// }

// int query5(char *flightINF, int *order)
// {
//         int i,
//             j,
//             valido,
//             valcount = 0;

//         char *info = NULL;
//         char *dates = NULL;
//         char *begin = NULL;
//         char *end = NULL;

//     info = strdup(strtok(flightINF, " "));       //pegar na origem dos voos que queremos

//          //agora tenho de pegar nas datas na info e torna-las em algo usável
//     //if (flightINF[0] == '"')        
//       //  removeChar(info);       //elimina as aspas nas datas, se presentes

//     dates = strdup(strtok(NULL, ""));        //pega nas datas
//     begin = strndup(dates+1, 19);      //pega no inicio
//     end = strndup(dates+23, 19);   //pega no fim

//     for (i = 0; i < global_flight_count; i++)       //percorrer os voos para ver os que têm origem coincidente
//     {
//         if (strcmp(info, global_flight_data[i].origin) == 0)    // //compara a origem dos voos
//         {
//             valido = 1;

//             for (j = 0; begin[j] != '\0'; j++)
//             {
//                 if (global_flight_data[i].schedule_departure_date[j] > begin[j])        // //os chars na departure tem de ser sempre iguais ou maiores que o begin
//                     break;
//                 if (global_flight_data[i].schedule_departure_date[j] < begin[j])
//                 {
//                     valido = 0;
//                     break;
//                 }
//             }
//             for (j = 0; end[j] != '\0' && valido == 1; j++)     //e sempre menores ou iguais que o end
//             {
//                 if (global_flight_data[i].schedule_departure_date[j] > end[j])
//                 {
//                     valido = 0;
//                     break;
//                 }
//                 if (global_flight_data[i].schedule_departure_date[j] < end[j])
//                     break;
//             }

//                       //se o voo for válido, tem de ser colocado
//             if (valido == 1)
//             {
//                 order = realloc(order, (valcount + 1) * sizeof(int));       //alocar memoria para cada um que for valido
//                 if (order == NULL)
//                     return -1;      //erros
//                 order[valcount] = i;        //armazenada a posição do voo no ficheiro
//                 valcount++;         //numero de voos no espaço de tempo aumenta
//             }
//         }
//     }

//     flightOrder(order, valcount);       //ordenar os voos

//     free(info);
//     free(dates);
//     free(begin);
//     free(end);

//     return valcount;
// }