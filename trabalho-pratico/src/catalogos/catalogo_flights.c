#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/catalogos/catalogo_flights.h"
#include "../include/tipos/flights.h"

#include "../include/statistics.h"

#include <ctype.h>

//no parser vou chamar as funçoes dos catalogos e cada função só vai ser executada numa linha e o ciclo while vai tar só no parser

//id;airline;plane_model;total_seats;origin;destination;schedule_departure_date;schedule_arrival_date;real_departure_date;real_arrival_date;pilot;copilot;notes

struct flights{
    GHashTable* flights_hash_table;
    GHashTable* airports_stats;
    //podemos definir outras estruturas
};


// Funções para dar get do parâmetro que nós queremos
// IMP: >Não esquecer de definir o flight_origins na função parser/ou nas queries

Catalogo_Flights* create_flights_catalog() {
    Catalogo_Flights* catalog = g_malloc(sizeof(struct flights));
    catalog->flights_hash_table = g_hash_table_new(g_str_hash, g_str_equal);
    catalog->airports_stats = g_hash_table_new(g_str_hash, g_str_equal);
    return catalog;
}

int calculate_flight_delay(FlightDetails* flight) {
    return calculate_delay_in_seconds(get_flight_schedule_departure_date(flight), get_flight_real_departure_date(flight));
}

// Função para adicionar um flight à HT do catalogo dos flights
void add_flight_to_catalog(Catalogo_Flights* catalog, char** tokens) {
    FlightDetails* new_flight = build_flight(tokens);
    const char* flight_id = get_flight_id(new_flight);
    const char* flight_origin = get_flight_origin(new_flight);

    // Adicionar um flight à HT organizada por flight_id
    g_hash_table_insert(catalog->flights_hash_table, g_strdup(flight_id), new_flight);

    int flight_delay = calculate_flight_delay(new_flight);
    AirportStats* stats = g_hash_table_lookup(catalog->airports_stats, flight_origin);
    if (!stats) {
        stats = create_airport_stats();
        g_hash_table_insert(catalog->airports_stats, g_strdup(flight_origin), stats);
    }

    // Dar update à lista
    update_airport_stats(stats,flight_delay);
}

AirportStats* get_airport_stats_by_origin(Catalogo_Flights* catalog, const char* flight_origin) {
    return g_hash_table_lookup(catalog->airports_stats, flight_origin);
}

// Função para dar get de um flight da HT, organizada pela origem
FlightDetails* get_flight_from_catalog(Catalogo_Flights* catalog, const char* id) {
    return g_hash_table_lookup(catalog->flights_hash_table, id);
}

GHashTable* get_airport_data(Catalogo_Flights* catalog) {
    return catalog->airports_stats;
}


// Função para libertar os flights do catálogo e o catálogo
void free_flights_catalog(Catalogo_Flights* catalog) {
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, catalog->flights_hash_table);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        // key é a string alocada com g_strdup, e value é UserDetails*
        g_free(key);  // Libertar a chave (user_id)
        free_flight(value);  // Libertar o UserDetails
    }

    g_hash_table_destroy(catalog->flights_hash_table);

    g_hash_table_iter_init(&iter, catalog->airports_stats);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        g_free(key); 
        free_airport_stats(value);  
    }
    g_hash_table_destroy(catalog->airports_stats);


    g_free(catalog);
}
