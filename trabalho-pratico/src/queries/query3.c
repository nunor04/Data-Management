#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/queries/query3.h"
#include "../include/tipos/reservations.h"

Query3 query3(Catalogs_Manager *manager, const char *hotelID)
{
    Query3 result;

    // Inicializar a struct
    result.media = 0;

    // Obter a informação do rating para o HotelID
    RatingInfo rating_info = get_hotel_rating_info(manager->catalog_reservations, hotelID);

    // Obter o contador para o HotelID
    int counter = rating_info.counter;

    if (counter > 0)
    {
        result.media = rating_info.rating_sum / counter;
    }

    return result;
}

