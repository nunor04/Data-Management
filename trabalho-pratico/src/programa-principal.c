#include <stdio.h>
#include <stdlib.h>
#include <verificar.h>
#include "../include/parser.h"
// #include <queries.h>

#include "../include/catalogos/catalogos_manager.h"
#include "../include/interpreter.h"

#include "../include/tipos/users.h"
#include "../include/catalogos/catalogo_reservations.h"
#include "../include/catalogos/catalogos_manager.h"

int main(int argc, char* argv[])
{
   
    // Record the start time
    clock_t start_time = clock();
    
      // validar(argv[1]);
     
     int test = 0;

     if(argc >= 4 && strcmp(argv[3],"test") == 0)
     {
         test = 1;
         printf("TEST MODE\n");
     } 
     
    // Alocar o espaço necessário para o manager
    Catalogs_Manager *manager = malloc(sizeof(Catalogs_Manager));
    
    // Inicializar/criar os catálogos ----- afinal acho que nao é preciso estas funçoes de create
     manager->catalog_reservations = create_reservations_catalog();
     manager->catalog_flights = create_flights_catalog();
     manager->catalog_users = create_users_catalog();

    parsing_dos_users(argv[1], manager);
    parsing_das_reservations(argv[1], manager);
    parsing_dos_flights(argv[1], manager);
    parsing_dos_passengers(argv[1],manager);

    interpreter(argv[2], manager, test);

    free_users_catalog(manager->catalog_users); 
    free_reservations_catalog(manager->catalog_reservations);
    free_flights_catalog(manager->catalog_flights);

    // Libertar a memória alocada do manager
    free(manager);

    // Record the end time
    clock_t end_time = clock();

    // Calculate the elapsed time in seconds
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Time taken: %f seconds\n", elapsed_time);

    return 0;
}

