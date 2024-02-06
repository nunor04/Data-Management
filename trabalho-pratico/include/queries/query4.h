#ifndef QUERY4_H
#define QUERY4_H

#include <stdio.h>

#include "../include/catalogos/catalogos_manager.h"
#include "../include/catalogos/catalogo_reservations.h"
#include "../include/tipos/reservations.h"
#include <glib.h>

typedef struct query4{
    int contador_reservations;
    char** id;
    char** begin_date;
    char** end_date;
    char** user_id;
    char** rating;
    double* preco_total;
} QueryResult;

QueryResult query4(Catalogs_Manager* catalog, const char* hotel_id);

#endif