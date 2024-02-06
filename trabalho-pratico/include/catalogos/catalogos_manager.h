#ifndef CATALOGOS_MANAGER_H
#define CATALOGOS_MANAGER_H

#include "../include/catalogos/catalogo_flights.h"
#include "../include/tipos/flights.h"

#include "../include/catalogos/catalogo_users.h"
#include "../include/tipos/users.h"

#include "../include/catalogos/catalogo_reservations.h"
#include "../include/tipos/reservations.h"

typedef struct manager Catalogs_Manager;

struct manager{
    Catalogo_Flights *catalog_flights;
    Catalogo_Users *catalog_users;
    Catalogo_Reservations *catalog_reservations;
    // struct pacatalogo_passengers
    // catalogo_users
    // catalogo_reservations
};

#endif