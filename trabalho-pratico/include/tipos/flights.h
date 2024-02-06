#ifndef FLIGHTS_H
#define FLIGHTS_H

#include <glib.h>

// Declaração da struct dos stats de cada airport
typedef struct AirportStats AirportStats;

// Função para criar a struct dos stats para um aeroporto
AirportStats* create_airport_stats();
// Função para dar update dos stats
void update_airport_stats(AirportStats* stats, int delay);
// Função para armazenar a lista dos delays para um determinado aeroporto
GList* get_airport_delays(const AirportStats* stats);


// Declaração da struct dos passenger_details
typedef struct passenger PassengerDetails;

// Declaração da struct dos flight_details
typedef struct flight FlightDetails;


// Função para criar a struct do flight
FlightDetails* create_flight();

// Função para construir struct onde vão ser guardados os valores
FlightDetails* build_flight(char** tokens);

// Funções para dar set de cada parâmetro do flight
void set_flight_id(FlightDetails* flight, const char* value);
void set_flight_airline(FlightDetails* flight, const char* value);
void set_flight_plane_model(FlightDetails* flight, const char* value);
void set_flight_total_seats(FlightDetails* flight, const char* value);
void set_flight_origin(FlightDetails* flight, const char* value);
void set_flight_destination(FlightDetails* flight, const char* value);
void set_flight_schedule_departure_date(FlightDetails* flight, const char* value);
void set_flight_schedule_arrival_date(FlightDetails* flight, const char* value);
void set_flight_real_departure_date(FlightDetails* flight, const char* value);
void set_flight_real_arrival_date(FlightDetails* flight, const char* value);

// Funções para dar get de cada parâmetro do flight
const char* get_flight_id(const FlightDetails* flight);
const char* get_flight_airline(const FlightDetails* flight);
const char* get_flight_plane_model(const FlightDetails* flight);
const char* get_flight_total_seats(const FlightDetails* flight);
const char* get_flight_origin(const FlightDetails* flight);
const char* get_flight_destination(const FlightDetails* flight);
const char* get_flight_schedule_departure_date(const FlightDetails* flight);
const char* get_flight_schedule_arrival_date(const FlightDetails* flight);
const char* get_flight_real_departure_date(const FlightDetails* flight);
const char* get_flight_real_arrival_date(const FlightDetails* flight);


// Funções para libertar a memória associada aos passeigeiros e ao flight
void free_passengers(PassengerDetails* passengers);

void free_airport_stats(AirportStats* stats);

void free_flight(FlightDetails* flight);

#endif
