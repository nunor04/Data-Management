#ifndef QUERY7_H
#define QUERY7_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "../include/tipos/flights.h"
#include "../include/catalogos/catalogo_flights.h" 
#include "../include/catalogos/catalogos_manager.h" 

typedef struct query7{
    int contador;
    char** origin;
    int* median;
} Q7;

Q7 query7(Catalogs_Manager* manager, const char* N);

#endif