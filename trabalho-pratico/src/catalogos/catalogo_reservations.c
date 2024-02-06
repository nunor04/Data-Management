#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/catalogos/catalogo_reservations.h"
#include "../include/tipos/reservations.h"

struct rating_details{
    double rating_sum;
    int counter;
};

struct reservations {
    GHashTable* reservations_hash_table_by_hotel_id_q3;
    GHashTable* reservations_hash_table_by_id_q4;
    GHashTable* hotel_ratings_sum;
};

Catalogo_Reservations* create_reservations_catalog() {
    Catalogo_Reservations* catalog = g_malloc(sizeof(struct reservations));
    catalog->reservations_hash_table_by_hotel_id_q3 = g_hash_table_new(g_str_hash, g_str_equal);
    catalog->reservations_hash_table_by_id_q4 = g_hash_table_new(g_str_hash, g_str_equal);
    catalog->hotel_ratings_sum = g_hash_table_new(g_str_hash, g_str_equal);
    return catalog;
}

// Função para adicionar uma reservation à HT do catalogo das reservations
void add_reservation_to_catalog_by_id_q4(Catalogo_Reservations* catalog, const char* reservation_id, char** tokens) {
    ReservationDetails* new_reservation = build_reservation_reservation_id_q4(tokens);
    g_hash_table_insert(catalog->reservations_hash_table_by_id_q4, g_strdup(reservation_id), new_reservation);
}

void add_reservation_to_catalog_by_hotel_id_HT(Catalogo_Reservations* catalog, const char* hotel_id, char** tokens) {
    ReservationDetails* new_reservation = build_reservation_hotel_id_HT(tokens);

    // Verifica se existe algum hotel_ID na HT igual ao target
    gpointer existing_key;
    gpointer existing_value;

    if (g_hash_table_lookup_extended(catalog->reservations_hash_table_by_hotel_id_q3, hotel_id, &existing_key, &existing_value)) {
        // Se existir liberta a memmória da reservation existente
        ReservationDetails* existing_reservation = (ReservationDetails*)existing_value;
        free_reservation_hotel_id_HT(existing_reservation);

        // Substituir a reservation pela nova
        g_hash_table_replace(catalog->reservations_hash_table_by_hotel_id_q3, existing_key, new_reservation);
    } else {
        // Não existe reservation então insere uma nova
        g_hash_table_insert(catalog->reservations_hash_table_by_hotel_id_q3, g_strdup(hotel_id), new_reservation);
    }

    // Calcular a soma dos ratings para cada hotel das reservas
    const char* rating_string = get_reservation_rating(new_reservation);
    double rating_double = atof(rating_string);

    // Procura a soma e o contador existentes na HT
    gpointer existing_sum_ptr = g_hash_table_lookup(catalog->hotel_ratings_sum, hotel_id);

    if (existing_sum_ptr != NULL) {
        // O hotel_id já existe na HT da soma dos ratings
        double* existing_sum = (double*)existing_sum_ptr;
        *existing_sum += rating_double;

        // Incrementar o contador
        gchar* counter_key = g_strconcat(hotel_id, "_counter", NULL);
        int* counter = g_hash_table_lookup(catalog->hotel_ratings_sum, counter_key); // O strconcat é usado para dar nome à variável (HTL1001_counter p.e.)
        (*counter)++;

        g_free((gpointer)counter_key); 

    } else {
        // O hotel_id é encontrado pela primeira vez
        double* new_sum = g_malloc(sizeof(double));
        *new_sum = rating_double;
        g_hash_table_insert(catalog->hotel_ratings_sum, g_strdup(hotel_id), new_sum);

        // Inicializar o contador
        int* counter = g_malloc(sizeof(int));
        *counter = 1;
        g_hash_table_insert(catalog->hotel_ratings_sum, g_strconcat(hotel_id, "_counter", NULL), counter);
    }
}

GHashTable* get_hotel_ratings_sum_HT(const Catalogo_Reservations *catalog) {
    return catalog->hotel_ratings_sum;
}

RatingInfo get_hotel_rating_info(Catalogo_Reservations* catalog, const char* hotel_id) {
    GHashTable* hotel_ratings_sum = get_hotel_ratings_sum_HT(catalog);

    RatingInfo result;
    result.rating_sum = 0.0;
    result.counter = 0;

    // Procura-se a soma dos ratings e o contador associado ao hotel_id
    gpointer sum_ptr = g_hash_table_lookup(hotel_ratings_sum, hotel_id);

    // Se for encontrado
    if (sum_ptr != NULL) {
        double* rating_sum = (double*)sum_ptr;

        // Usa-se o strconcat para criar uma key para armazenar o contador de cada hotel_id
        const char* counter_key = g_strconcat(hotel_id, "_counter", NULL);
        int* counter = g_hash_table_lookup(hotel_ratings_sum, counter_key);
        g_free((gpointer)counter_key);

        if (counter != NULL) {
            result.rating_sum = *rating_sum;
            result.counter = *counter;
        }
    }
    
    return result;
}

GList* get_reservations_by_hotel_id(const Catalogo_Reservations* catalog, const char* hotel_id) {
    // Inicializa o iterator
    GHashTableIter iter;
    gpointer key, value;

    // Cria uma nova lista para armazenar as reservas filtradas (com o target hotel_id)
    GList* filtered_list = NULL;

    // Itera sobre a HT
    g_hash_table_iter_init(&iter, catalog->reservations_hash_table_by_id_q4);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        // Verifica se o hotel_id corresponde ao target
        if (strcmp(get_reservation_hotel_id((ReservationDetails*)value), hotel_id) == 0) {
            // Converte diretamente o valor para GList*
            filtered_list = g_list_append(filtered_list, value);
        }
    }
    // Se o hotel_id não for encontrado na tabela hash, retorna uma lista vazia ou trata conforme necessário
    return filtered_list;
}



// Função para libertar as reservas do catálogo e o catálogo
void free_reservations_catalog(Catalogo_Reservations* catalog) {
    GHashTableIter iter;
    gpointer key, value;

    // Libertar os campos da HT e a HT
    g_hash_table_iter_init(&iter, catalog->reservations_hash_table_by_hotel_id_q3);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        g_free(key);
        free_reservation_hotel_id_HT(value);
    }

    g_hash_table_destroy(catalog->reservations_hash_table_by_hotel_id_q3);

    // Libertar a memória da HT da soma dos ratings
    g_hash_table_iter_init(&iter, catalog->hotel_ratings_sum);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        g_free(key);
        g_free(value); // Free the double* or int* values
    }
    // Destruir a HT
    g_hash_table_destroy(catalog->hotel_ratings_sum);

    g_hash_table_iter_init(&iter, catalog->reservations_hash_table_by_id_q4);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        g_free(key);
        free_reservation_reservation_id_q4(value);
    }

    g_hash_table_destroy(catalog->reservations_hash_table_by_id_q4);


    // Libertar o catálogo
    g_free(catalog);
}