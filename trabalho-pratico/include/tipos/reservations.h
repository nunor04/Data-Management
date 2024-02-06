#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#include <glib.h>

typedef struct reservation ReservationDetails;

// Função para criar a nova HT das reservations
ReservationDetails *create_reservation();

// Função para preencher essa HT com os tokens
ReservationDetails *build_reservation_hotel_id_HT(char** tokens);
ReservationDetails *build_reservation_reservation_id_q4(char** tokens);

// Funções para dar set a cada um dos parâmetros (usadas na build_reservation)
void set_reservation_id(ReservationDetails* reservation, const char* value);
void set_reservation_user_id(ReservationDetails* reservation, const char* value);
void set_reservation_hotel_id(ReservationDetails* reservation, const char* value);
void set_reservation_hotel_name(ReservationDetails* reservation, const char* value);
void set_reservation_hotel_stars(ReservationDetails* reservation, const char* value);
void set_reservation_city_tax(ReservationDetails* reservation, const char* value);
void set_reservation_begin_date(ReservationDetails* reservation, const char* value);
void set_reservation_end_date(ReservationDetails* reservation, const char* value);
void set_reservation_price_per_night(ReservationDetails* reservation, const char* value);
void set_reservation_rating(ReservationDetails* reservation, const char* value);

// Funções para dar get a cada um dos parâmetros necessários
const char* get_reservation_id(const ReservationDetails* reservation);
const char* get_reservation_user_id(const ReservationDetails* reservation);
const char* get_reservation_hotel_id(const ReservationDetails* reservation);
const char* get_reservation_hotel_name(const ReservationDetails* reservation);
const char* get_reservation_hotel_stars(const ReservationDetails* reservation);
const char* get_reservation_city_tax(const ReservationDetails* reservation);
const char* get_reservation_begin_date(const ReservationDetails* reservation);
const char* get_reservation_end_date(const ReservationDetails* reservation);
const char* get_reservation_price_per_night(const ReservationDetails* reservation);
const char* get_reservation_rating(const ReservationDetails* reservation);

void free_reservation_hotel_id_HT(ReservationDetails* reservation);
void free_reservation_reservation_id_q4(ReservationDetails* reservation);

#endif
