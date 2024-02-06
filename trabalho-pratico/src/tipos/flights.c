#include "../include/tipos/flights.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct AirportStats {
    GList* delays;  // Lista ligada para guardar os atrasos de cada aeroporto
};

AirportStats* create_airport_stats() {
    AirportStats* stats = g_malloc(sizeof(struct AirportStats));
    stats->delays = NULL;
    return stats;
}

void update_airport_stats(AirportStats* stats, int delay) {
    stats->delays = g_list_append(stats->delays, GINT_TO_POINTER(delay));
}

GList* get_airport_delays(const AirportStats* stats) {
    return stats->delays;
}


// Struct para representar cada passenger
struct passenger {
    char* flight_id;
    char* user_id;
    PassengerDetails* next; // Pointer para o proximo passenger na lista
};

struct flight{
    char* id;
    char* airline;
    char* plane_model;
    char* total_seats;
    char* origin;
    char* destination;
    char* schedule_departure_date; 
    char* schedule_arrival_date;
    char* real_departure_date;
    char* real_arrival_date;
    PassengerDetails* passengers; //lista ligada associada a cada voo
    AirportStats* airport_stats;
};

// Função para criar uma nova struct de FlightDetails
FlightDetails* create_flight(){
    FlightDetails* new_flight = g_malloc(sizeof(struct flight));

    // Inicializar todos os valores a 0 para ser mais fácil lidar com eventuais erros
    new_flight->id = NULL;
    new_flight->airline = NULL;
    new_flight->plane_model = NULL;
    new_flight->total_seats = NULL;
    new_flight->origin = NULL;
    new_flight->destination = NULL;
    new_flight->schedule_departure_date = NULL;
    new_flight->schedule_arrival_date = NULL;
    new_flight->real_departure_date = NULL;
    new_flight->real_arrival_date = NULL;
    new_flight->airport_stats = create_airport_stats();

    return new_flight;
}

// Função para atribuir os tokens aos parâmetros respetivos
FlightDetails* build_flight(char** tokens) {
    FlightDetails* new_flight = create_flight();

    set_flight_id(new_flight, tokens[0]);
    set_flight_airline(new_flight, tokens[1]);
    set_flight_plane_model(new_flight, tokens[2]);
    set_flight_total_seats(new_flight, tokens[3]);
    set_flight_origin(new_flight, tokens[4]);
    set_flight_destination(new_flight, tokens[5]);
    set_flight_schedule_departure_date(new_flight, tokens[6]);
    set_flight_schedule_arrival_date(new_flight, tokens[7]);
    set_flight_real_departure_date(new_flight, tokens[8]);
    set_flight_real_arrival_date(new_flight, tokens[9]);

    return new_flight;
}

// Função para adicionar um passageiro a um voo
void set_passenger(FlightDetails* flight, const char* flight_id,const char* user_id) {
    // Alocar memória para o novo passageiro
    PassengerDetails* new_passenger = g_malloc(sizeof(PassengerDetails));
    new_passenger->flight_id = g_strdup(flight_id);
    new_passenger->user_id = g_strdup(user_id);
    new_passenger->next = NULL;

    // Adicionar o passageiro à lista ligada
    if (flight->passengers == NULL) {
        flight->passengers = new_passenger;
    } else {
        PassengerDetails* current_passenger = flight->passengers;
        while (current_passenger->next != NULL) {
            current_passenger = current_passenger->next;
        }
        current_passenger->next = new_passenger;
    }
}


// Função para dar set do ID do novo flight
void set_flight_id(FlightDetails* flight, const char* value){
    flight->id = g_strdup(value);
}

// Igual para as outras funções, o que muda é só o parâmetro
void set_flight_airline(FlightDetails* flight, const char* value) {
    flight->airline = g_strdup(value);
}

void set_flight_plane_model(FlightDetails* flight, const char* value) {
    flight->plane_model = g_strdup(value);
}

void set_flight_total_seats(FlightDetails* flight, const char* value) {
    flight->total_seats = g_strdup(value);
}

void set_flight_origin(FlightDetails* flight, const char* value) {
    flight->origin = g_strdup(value);

    // Converter a string para maiúsculas
    for (int i = 0; flight->origin[i]; i++) {
        flight->origin[i] = toupper(flight->origin[i]);
    }
}

void set_flight_destination(FlightDetails* flight, const char* value) {
    flight->destination = g_strdup(value);
}

void set_flight_schedule_departure_date(FlightDetails* flight, const char* value) {
    flight->schedule_departure_date = g_strdup(value);
}

void set_flight_schedule_arrival_date(FlightDetails* flight, const char* value) {
    flight->schedule_arrival_date = g_strdup(value);
}

void set_flight_real_departure_date(FlightDetails* flight, const char* value) {
    flight->real_departure_date = g_strdup(value);
}

void set_flight_real_arrival_date(FlightDetails* flight, const char* value) {
    flight->real_arrival_date = g_strdup(value);
}

/*
    Nas funções get temos 2 opções:
    
        - Fazer uma cópia (strdup) do id p.e. e dar get disso 
            _ou_
        - Usar const

    Desta maneira não é possível alterar os dados da struct a partir de outro módulo (daria erro)
*/


// Funções para dar get dos parâmetros dos passengers e das structs respetivas
const char* get_passenger_flight_id(const PassengerDetails* passenger) {
    return passenger->flight_id;
}

const char* get_passenger_user_id(const PassengerDetails* passenger) {
    return passenger->user_id;
}

const PassengerDetails* get_first_passenger(const FlightDetails* flight) {
    return flight->passengers;
}

const PassengerDetails* get_next_passenger(const PassengerDetails* passenger) {
    return passenger->next;
}


// Função para dar get do id do novo flight
const char* get_flight_id(const FlightDetails* flight) {
    return flight->id;
}

// Igual para as outras funções, o que muda é só o parâmetro
const char* get_flight_airline(const FlightDetails* flight) {
    return flight->airline;
}

const char* get_flight_plane_model(const FlightDetails* flight) {
    return flight->plane_model;
}

const char* get_flight_total_seats(const FlightDetails* flight) {
    return flight->total_seats;
}

const char* get_flight_origin(const FlightDetails* flight) {
    return flight->origin;
}

const char* get_flight_destination(const FlightDetails* flight) {
    return flight->destination;
}

const char* get_flight_schedule_departure_date(const FlightDetails* flight) {
    return flight->schedule_departure_date;
}

const char* get_flight_schedule_arrival_date(const FlightDetails* flight) {
    return flight->schedule_arrival_date;
}

const char* get_flight_real_departure_date(const FlightDetails* flight) {
    return flight->real_departure_date;
}

const char* get_flight_real_arrival_date(const FlightDetails* flight) {
    return flight->real_arrival_date;
}

// void free_passengers(PassengerDetails* passengers) {
//     g_list_free(passengers->flight_id);
//     g_list_free(passengers->user_id);
//     g_free(passengers);
// }

void free_airport_stats(AirportStats* stats) {
    g_list_free(stats->delays);  // Liberta a lista-ligada
    g_free(stats);  // Liberta a struct
}

//Função para libertar a memória associada ao novo flight (Não sei se é necessário fazer isto)
void free_flight(FlightDetails* flight) {
    g_free(flight->id);
    g_free(flight->airline);
    g_free(flight->plane_model);
    g_free(flight->total_seats);
    g_free(flight->origin);
    g_free(flight->destination);
    g_free(flight->schedule_departure_date);
    g_free(flight->schedule_arrival_date);
    g_free(flight->real_departure_date);
    g_free(flight->real_arrival_date);
    g_free(flight->airport_stats);
    // free_passengers(flight->passengers);
    g_free(flight);
}
