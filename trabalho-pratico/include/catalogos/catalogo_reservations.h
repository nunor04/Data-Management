#ifndef CATALOGO_RESERVATIONS_H
#define CATALOGO_RESERVATIONS_H

#include "../tipos/reservations.h"

#include <glib.h>


typedef struct reservations Catalogo_Reservations;

typedef struct rating_details RatingInfo;

Catalogo_Reservations* create_reservations_catalog();

void add_reservation_to_catalog_by_id_q4(Catalogo_Reservations* catalog, const char* reservation_id, char** tokens);

void add_reservation_to_catalog_by_hotel_id_HT(Catalogo_Reservations* catalog, const char* reservation_id,char** tokens);

GHashTable* get_hotel_ratings_sum_HT(const Catalogo_Reservations *catalog);

RatingInfo get_hotel_rating_info(Catalogo_Reservations* catalog, const char* hotel_id);

GList* get_reservations_by_hotel_id(const Catalogo_Reservations* catalog, const char* hotel_id);

void free_reservations_catalog(Catalogo_Reservations* catalog);
#endif
