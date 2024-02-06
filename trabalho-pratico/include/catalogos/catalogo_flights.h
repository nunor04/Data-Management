#ifndef CATALOGO_FLIGHTS_H
#define CATALOGO_FLIGHTS_H

#include "../tipos/flights.h"

#include <glib.h>
#include <stdbool.h>

// Declaração da struct dos catálogos
typedef struct flights Catalogo_Flights;

// Função para inicializar o catálogo
Catalogo_Flights* create_flights_catalog();

// Função para adicionar um flight ao catálogo
void add_flight_to_catalog(Catalogo_Flights* catalog, char** tokens);

void update_airport_delays(Catalogo_Flights* catalog, const char* flight_origin, int delay);

void update_airport_delays_hash_table(Catalogo_Flights* catalog);

// Funções para dar get do parâmetro que nós queremos
FlightDetails* get_flight_from_catalog(Catalogo_Flights* catalog, const char* id);

// Função para dar get da lista de delays do flight
FlightDetails* get_airport_delays_list(Catalogo_Flights* catalog, const char* flight_origin);

// Função para dar get da hash_table dos airports
GHashTable* get_airport_data(Catalogo_Flights* catalog);

// Função para libertar memória do catálogo
void free_flights_catalog(Catalogo_Flights* catalog);

// bool is_uppercase(const char* str);


#endif

