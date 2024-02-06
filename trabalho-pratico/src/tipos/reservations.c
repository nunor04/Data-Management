#include "../include/tipos/reservations.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

struct reservation {
    char* id;
    char* user_id;
    char* hotel_id;
    char* hotel_name;
    char* hotel_stars;
    char* city_tax;
    char* begin_date;
    char* end_date;
    char* price_per_night;
    char* rating;
    double total_price;
};

// Função para criar a nova struct de reservations
ReservationDetails* create_reservation() {
    ReservationDetails* new_reservation = g_malloc(sizeof(struct reservation));

    // Inicializar todos os valores a NULL para ser mais fácil encontrar erros
    new_reservation->id = NULL;
    new_reservation->user_id = NULL;
    new_reservation->hotel_id = NULL;
    new_reservation->hotel_name = NULL;
    new_reservation->hotel_stars = NULL;
    new_reservation->city_tax = NULL;
    new_reservation->begin_date = NULL;
    new_reservation->end_date = NULL;
    new_reservation->price_per_night = NULL;
    new_reservation->rating = NULL;
    new_reservation->total_price = 0.0;

    return new_reservation;
}

ReservationDetails* build_reservation_reservation_id_q4(char** tokens) {
    ReservationDetails* new_reservation = create_reservation();

    set_reservation_id(new_reservation, tokens[0]); 
    set_reservation_user_id(new_reservation, tokens[1]);
    set_reservation_hotel_id(new_reservation, tokens[2]);
    set_reservation_city_tax(new_reservation, tokens[5]);
    set_reservation_begin_date(new_reservation, tokens[7]);
    set_reservation_end_date(new_reservation, tokens[8]);
    set_reservation_price_per_night(new_reservation, tokens[9]);
    set_reservation_rating(new_reservation, tokens[12]);
    // total price = preço_por_noite × número_de_noites + (preço_por_noite×número_de_noites)/100 × imposto_da_cidade

    return new_reservation;
}

ReservationDetails* build_reservation_hotel_id_HT(char** tokens) {
    ReservationDetails* new_reservation = create_reservation();

    set_reservation_hotel_id(new_reservation, tokens[2]);
    set_reservation_rating(new_reservation, tokens[12]);

    return new_reservation;
}

// Funções para dar set a cada um dos parâmetros
void set_reservation_id(ReservationDetails* reservation, const char* value) {
    reservation->id = g_strdup(value);
}

void set_reservation_user_id(ReservationDetails* reservation, const char* value) {
    reservation->user_id = g_strdup(value);
}

void set_reservation_hotel_id(ReservationDetails* reservation, const char* value) {
    reservation->hotel_id = g_strdup(value);
}

void set_reservation_hotel_name(ReservationDetails* reservation, const char* value) {
    reservation->hotel_name = g_strdup(value);
}

void set_reservation_hotel_stars(ReservationDetails* reservation, const char* value) {
    reservation->hotel_stars = g_strdup(value);
}

void set_reservation_city_tax(ReservationDetails* reservation, const char* value) {
    reservation->city_tax = g_strdup(value);
}

void set_reservation_begin_date(ReservationDetails* reservation, const char* value) {
    reservation->begin_date = g_strdup(value);
}

void set_reservation_end_date(ReservationDetails* reservation, const char* value) {
    reservation->end_date = g_strdup(value);
}

void set_reservation_price_per_night(ReservationDetails* reservation, const char* value) {
    reservation->price_per_night = g_strdup(value);
}

void set_reservation_rating(ReservationDetails* reservation, const char* value) {
    reservation->rating = g_strdup(value);
}

void set_reservation_total_price(ReservationDetails* reservation, double total_price) {
    reservation->total_price = total_price;
}


// Funções para dar get a cada um dos parâmetros
const char* get_reservation_id(const ReservationDetails* reservation) {
    return reservation->id;
}

const char* get_reservation_user_id(const ReservationDetails* reservation) {
    return reservation->user_id;
}

const char* get_reservation_hotel_id(const ReservationDetails* reservation) {
    return reservation->hotel_id;
}

const char* get_reservation_hotel_name(const ReservationDetails* reservation) {
    return reservation->hotel_name;
}

const char* get_reservation_hotel_stars(const ReservationDetails* reservation) {
    return reservation->hotel_stars;
}

const char* get_reservation_city_tax(const ReservationDetails* reservation) {
    return reservation->city_tax;
}

// const char* get_reservation_address(const ReservationDetails* reservation) {
//     return reservation->address;
// }

const char* get_reservation_begin_date(const ReservationDetails* reservation) {
    return reservation->begin_date;
}

const char* get_reservation_end_date(const ReservationDetails* reservation) {
    return reservation->end_date;
}

const char* get_reservation_price_per_night(const ReservationDetails* reservation) {
    return reservation->price_per_night;
}


const char* get_reservation_rating(const ReservationDetails* reservation) {
    return reservation->rating;
}

// mem da query3
void free_reservation_hotel_id_HT(ReservationDetails* reservation) {
    g_free(reservation->hotel_id);
    g_free(reservation->rating);
    g_free(reservation);
}

// mem da query4
void free_reservation_reservation_id_q4(ReservationDetails* reservation){
    g_free(reservation->id);
    g_free(reservation->user_id);
    g_free(reservation->hotel_id);
    g_free(reservation->city_tax);
    g_free(reservation->begin_date);
    g_free(reservation->end_date);
    g_free(reservation->price_per_night);
    g_free(reservation->rating);
    g_free(reservation);
}
