#ifndef QUERY1_H
#define QUERY1_H

#include <stdio.h>

#include "../include/catalogos/catalogos_manager.h"
#include <glib.h>

typedef struct query1{
    int contador_reservations;
    char** user_data;
    char** flight_data;
    char** reservation_data;
} Q1;

Q1 query1(Catalogs_Manager* manager, const char* id);

#endif