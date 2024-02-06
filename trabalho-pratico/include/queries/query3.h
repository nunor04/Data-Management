#ifndef QUERY3_H
#define QUERY3_H
#include "../include/catalogos/catalogos_manager.h"
#include "../include/catalogos/catalogo_reservations.h"
#include <glib.h>

typedef struct q3 {        
    double media;
} Query3;

struct rating_details{
    double rating_sum;
    int counter;
};

Query3 query3(Catalogs_Manager* manager,const char* hotelID);

#endif  