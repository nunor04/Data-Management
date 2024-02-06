#include "../include/queries/query7.h"
#include "../include/statistics.h"

typedef struct airportsQ7{
    char* origin;
    int median;
} AirportsQ7;

int compare_airports(const void* a, const void* b) {
    const AirportsQ7* airport_a = (const AirportsQ7*)a;
    const AirportsQ7* airport_b = (const AirportsQ7*)b;

    // Verificar se as medianas são iguais
    if (airport_a->median == airport_b->median) {
        // Se as medianas são iguais, comparar pelos nomes dos aeroportos
        return strcmp(airport_a->origin, airport_b->origin);
    } else {
        // Se as medianas são diferentes, retornar a diferença de medianas
        return (airport_a->median < airport_b->median) ? 1 : -1;
    }
}

Q7 query7(Catalogs_Manager* manager, const char* N){
    Q7 result;
    result.contador = atoi(N);

    int i = 0;

    // Inicializar para guardar os airports
    result.origin = g_malloc(result.contador * sizeof(char*));
    result.median = g_malloc(result.contador * sizeof(int));

    // Get do catalogo dos flights e da data dos airports
    GHashTable* airports = get_airport_data(manager->catalog_flights);

    // Criar o array para guardar (name,median)
    AirportsQ7* airport_data_array = g_malloc(g_hash_table_size(airports) * sizeof(AirportsQ7));

    // Iterar pela HT (onde tem as listas de delays)
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, airports);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        const char* airport_name = (const char*)key;
        AirportStats* stats = (AirportStats*)value;

        // Dar get da lista de atrasos
        GList* delays = get_airport_delays(stats);

        // Obter o comprimento da lista
        int length = g_list_length(delays);

        // printf("Length: %d\n",length);

        // Alocar um array de inteiros   (Uma possível otimização seria, não precisar de converter em array e fazer a mediana direta na GList)
        int* delays_array = g_malloc(length * sizeof(int));

        // Preencher o array com os dados da lista
        for (int i = 0; i < length; i++) {
            delays_array[i] = GPOINTER_TO_INT(g_list_nth_data(delays, i));
        }

        // Calcular a mediana
        int median_delay = calcularMediana(delays_array, length);

        // Libertar a memória alocada para o array
        g_free(delays_array);


        // Guardar as medianas dos airports num array
        airport_data_array[i].origin = g_strdup(airport_name);
        airport_data_array[i].median = median_delay;
        i++;
    }

    qsort(airport_data_array, i, sizeof(AirportsQ7), compare_airports);

    // Escolher o top N medianas
    int copy_count = result.contador < i ? result.contador : i; //tratar do caso em que o input é maior do que o nº de delays na HT
    for (int j = 0; j < copy_count; j++) {
        result.origin[j] = g_strdup(airport_data_array[j].origin);
        result.median[j] = airport_data_array[j].median;
    }

    for (int l = 0; l < i; l++) {
        g_free(airport_data_array[l].origin);
    }

    // Se result.contador for maior do que i, preencher os restantes com valores padrão o
    if (result.contador > i) {
        for (int j = i; j < result.contador; j++) {
            // Preencher com valores padrão
            result.origin[j] = NULL; 
            result.median[j] = 0;   
        }
    }

    // Libertar a memória alocada para o airport_data_array
    g_free(airport_data_array);

    if (result.contador > i) result.contador = i;

    return result;
}


//  #include <stdio.h>
//  #include <stdlib.h>
//  #include <string.h>
//  #include <ctype.h>
//  #include "../include/queries.h"
// #include "../include/structs/flights.h"
//  #include "../include/allqueries.h"

// int aeroexists(char* searchString, char* stringArray[], int arraySize) 
//  {
//     for (int i = 0; i < arraySize; i++) 
//     {
//         if (strcasecmp(searchString, stringArray[i]) == 0) 
//         {
//             // A string foi encontrada no array
//             return 1;  // Verdadeiro
//         }
//     }
//     // A string não foi encontrada no array
//     return 0;  // Falso
// }

// int compareAtrasos(const void* a, const void* b) {
//     return (*(int*)a - *(int*)b);
// }


// int compareAeroportos(const void *a, const void *b) {
//     // Compara por mediana em ordem decrescente
//     int diferenca = ((AeroportoMediana *)b)->mediana - ((AeroportoMediana *)a)->mediana;

//     // Se as medianas são iguais, desempate por ordem alfabética dos aeroportos
//     if (diferenca == 0) {
//         return strcmp(((AeroportoMediana *)a)->aeroporto, ((AeroportoMediana *)b)->aeroporto);
//     }

//     return diferenca;
// }

// AeroportoMediana* query7(int N) {
//     char** uniqueAirports = (char**)malloc(global_flight_count * sizeof(char*));
//     int uniqueAirportCount = 0;

//     // Loop através dos voos
//     for (int i = 0; i < global_flight_count; i++) {
//         // Verifica se o aeroporto já foi adicionado ao array uniqueAirports
//         if (!aeroexists(global_flight_data[i].origin, uniqueAirports, uniqueAirportCount)) {
//             // Aloca dinamicamente espaço para a string do aeroporto
//             uniqueAirports[uniqueAirportCount] = strdup(global_flight_data[i].origin);
//             for(int j = 0; uniqueAirports[uniqueAirportCount][j] != '\0';j++)
//             {
//                 uniqueAirports[uniqueAirportCount][j] = toupper(uniqueAirports[uniqueAirportCount][j]);
//             }
//             uniqueAirportCount++;
//         }
//     }

//     // Aloca dinamicamente o array de arrays de ints para armazenar os atrasos
//     int** atrasos = (int**)malloc(uniqueAirportCount * sizeof(int*));

//     // Inicializa os arrays de atrasos
//     for (int i = 0; i < uniqueAirportCount; i++) {
//         atrasos[i] = (int*)malloc(global_flight_count * sizeof(int));
//     }

//     int adv = 0;
//     int natraso;


//   AeroportoMediana *aeroportosMedianas = (AeroportoMediana *)malloc(uniqueAirportCount * sizeof(AeroportoMediana));
  
//     while (adv < uniqueAirportCount) 
//     {
//         natraso = 0;

//         for (int i = 0; i < global_flight_count; i++) {
//             if (strcasecmp(uniqueAirports[adv], global_flight_data[i].origin) == 0) {
//                 int diferença = 0;
//                 int x,y,z = 0;
//                 int shoras,sminutos,ssegundos,rhoras,rminutos,rsegundos = 0;
//                 char data[11];
//                 char hora[9];
//                 int sdata,rdata = 0;
//                 sscanf(global_flight_data[i].schedule_departure_date, "%10s %8s", data, hora);
//                 sscanf(hora,"%d:%d:%d",&shoras,&sminutos,&ssegundos);
//                 sscanf(data,"%d/%d/%d",&x,&y,&z);
//                 sdata = x*10000+y*100+z;
                
                
//                 sscanf(global_flight_data[i].real_departure_date, "%10s %8s", data, hora);
//                 sscanf(data,"%d/%d/%d",&x,&y,&z);
//                 rdata = x*10000+y*100+z;
//                 sscanf(hora,"%d:%d:%d",&rhoras,&rminutos,&rsegundos);
//                 if(rdata != sdata)
//                 {
                    
//                 }
//                 else
//                 {
//                     diferença = (rhoras - shoras)*3600+(rminutos-sminutos)*60+(rsegundos-ssegundos);
//                 }
//                 atrasos[adv][natraso] = diferença;
                
//                 natraso++;
//             }
//         }
        
//         qsort(atrasos[adv], natraso, sizeof(int), compareAtrasos);
       
//         if (natraso % 2 == 0) {
//             // Média das duas medianas centrais para tamanho par
//             aeroportosMedianas[adv].mediana =
//                 (atrasos[adv][natraso / 2 - 1] + atrasos[adv][natraso / 2]) / 2;
//         } else {
//             // Mediana para tamanho ímpar
//             aeroportosMedianas[adv].mediana = atrasos[adv][natraso / 2];
//         }
        
//         strcpy(aeroportosMedianas[adv].aeroporto, uniqueAirports[adv]);

//         adv++;
//      }
    
//        qsort(aeroportosMedianas, uniqueAirportCount, sizeof(AeroportoMediana), compareAeroportos);
     
//      aeroportosMedianas[0].n = uniqueAirportCount;
      
     
    
//     for (int i = 0; i < uniqueAirportCount; i++) {
//         free(uniqueAirports[i]);
//         free(atrasos[i]);
//     }
    
//     free(uniqueAirports);
//     free(atrasos);

//     return aeroportosMedianas;
// }