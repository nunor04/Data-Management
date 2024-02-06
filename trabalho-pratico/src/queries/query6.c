// #include <stdio.h>
// #include <string.h>
// #include "../include/structs/flights.h"

// int appearCount(char *origin, char **origins, int *countpo, int count)      //guarda o nome de origem numa lista e a contagem de cada nome se já aparecer
// {
//         int i;
//     for (i = 0; i <= count; i++)
//     {
//         if(strcmp(origin,origins[i]))       //caso já existe aumenta o nr de ocorrencias
//             countpo[i]++;
//         else
//         {
//             count++;        //aumenta o nr de elementos na lista
//                 countpo = realloc(sizeof(int)* count);      //tenho de alocar memória para as ocorrências
//             countpo[i] = 1;     //a primeira aparição
//                 origins = realloc(4 * sizeof(char) * count);       //alocar memória para as origens
//             strcpy(origin, origins[i]);     //meter o novo local na lista

//             break;      //n quero que, por aumentar o count, percorra outra vez a lista e meta a mesma entrada 2 vezes
//         }
//     }
//     return count;       //assim posso incrementa-la com esta função
// }

// void swap(int *xp, int *yp)     //troca simples para o sort
// {
//         int temp = *xp;
//     *xp = *yp;
//     *yp = temp;
// }

// void swapString(char *xp, char *yp)
// {
//         char temp = *xp;        //com apontadores funciona certo?
//     *xp = *yp;
//     *yp = temp;
// }

// void order(int **origins, int *countpo, int count)
// {
//         int i, j,
//             tiebreaker;
//     for (i = 0; i < count - 1; i++) 
//     {
//         for (j = 0; j < count - i - 1; j++)
//         {
//             if (countpo[j] < countpo[j+1])
//             {
//                 swap(countpo[j], countpo[j+1]);     //menor indice tem de ter mais voos
//                 swapString(origins[j],origins[j+1]);
//             }
//             if (countpo[j] == countpo[j+1])
//             {
//                 tiebreaker = strcmp(origins[j],origins[j+1]);       //caso de empate, vai pelo nome, por ordem crescente (assumo alfabética)
//                 if(tiebreaker < 0)
//                 {
//                     swap(countpo[j], countpo[j+1]);
//                     swapString(origins[j],origins[j+1]);
//                 }
//             }
//         }
//     }
// }

// void query6(char *info)     //"ano N"
// {
//         char *year,
//              **origins;     //array que armazena os locais de partida
//         int i,
//             count = 0,
//             *countpo,       //nr apariçoes por origem
//             N;
//     year = strtok(info, " ");       //pega no ano

//     for (i = 0; i < global_flight_count; i++)
//     {
//         if(strstr(global_flight_data[i].schedule_departure_date, year) != NULL)         //se a data de partida for do mesmo ano
//         {
//             count = appearCount(global_flight_data[i].origin, origins, countpo, count);     //introduz os dados necessários
//         }
//     }

//         //agora falta ordenar as origens e pegar nas N primeiras
//     N = strtok(NULL, "") - '0';     //pega só no caractere N

//     order(origins, countpo, count);
//         //agora ordenado falta dar prints, dando o mesmo índice de array de nome e o nr de voos que tem (origins[i];countpo[i])
//         //n vou dar porque nao queremos prints para o nada

//         //por último, libertar a memória alocada:
//     free(year);
//     free(origins);
//     free(countpo);
// }