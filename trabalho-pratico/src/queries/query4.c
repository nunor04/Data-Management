// /*Q4: Listar as reservas de um hotel, ordenadas por data de início (da mais recente para a mais
// antiga). Caso duas reservas tenham a mesma data, deve ser usado o identificador da reserva como
// critério de desempate (de forma crescente)*/

#include "../include/queries/query4.h"

int nnoites(const char *begin, const char *end)
{
        int begin_date = (begin[8] - '0')*10 + (begin[9] - '0');        //primeiro as decimas do dia + as unidades
        int end_date = (end[8] - '0')*10 + (end[9] - '0');
    return(end_date - begin_date);
}

// Função auxiliar para comparar duas reservas por data de início (mais recente para mais antiga)
static gint compare_reservations(gconstpointer a, gconstpointer b) {
    ReservationDetails *reservation_a = (ReservationDetails *)a;
    ReservationDetails *reservation_b = (ReservationDetails *)b;

    // Comparar as datas por ordem decrescente
    int comparacao_data_inicio = strcmp(get_reservation_begin_date(reservation_b), get_reservation_begin_date(reservation_a));

    // Se forem diferentes
    if (comparacao_data_inicio != 0) {
        return comparacao_data_inicio;
    }

    // Se forem iguais, vai haver desempate através do ID em ordem crescente
    return strcmp(get_reservation_id(reservation_a), get_reservation_id(reservation_b));
}


QueryResult query4(Catalogs_Manager *manager, const char *hotel_id) {
    QueryResult result;
    result.contador_reservations = 0;
    result.id = NULL;
    result.begin_date = NULL;
    result.end_date = NULL;
    result.user_id = NULL;
    result.rating = NULL;
    result.preco_total = NULL;

    // Obtém a lista de reservas para o hotel_id
    GList *hotel_reservations_list = get_reservations_by_hotel_id(manager->catalog_reservations, hotel_id);

    // Conta o número de reservas
    result.contador_reservations = g_list_length(hotel_reservations_list);
    
    // Alocar espaço para os arrays
    result.id = g_malloc(result.contador_reservations * sizeof(char *));
    result.begin_date = g_malloc(result.contador_reservations * sizeof(char *));
    result.end_date = g_malloc(result.contador_reservations * sizeof(char *));
    result.user_id = g_malloc(result.contador_reservations * sizeof(char *));
    result.rating = g_malloc(result.contador_reservations * sizeof(char *));
    result.preco_total = g_malloc(result.contador_reservations * sizeof(double));

    // Ordena o array usando quick sort
    hotel_reservations_list = g_list_sort(hotel_reservations_list, compare_reservations);

    // Itera sobre as reservas ordenadas
    int i = 0;
    for (GList *iter = hotel_reservations_list; iter != NULL; iter = g_list_next(iter), i++) {
        ReservationDetails *current_reservation = iter->data;

        // Calcula o número de noites
        int num_noites = nnoites(get_reservation_begin_date(current_reservation), get_reservation_end_date(current_reservation));

        // Calcula o total_price
        result.preco_total[i] = atof(get_reservation_price_per_night(current_reservation)) * num_noites +
                                (atof(get_reservation_price_per_night(current_reservation)) * num_noites) / 100.0 * atof(get_reservation_city_tax(current_reservation));

        // Alocar espaço para as strings de output
        result.id[i] = g_strdup(get_reservation_id(current_reservation));
        result.begin_date[i] = g_strdup(get_reservation_begin_date(current_reservation));
        result.end_date[i] = g_strdup(get_reservation_end_date(current_reservation));
        result.user_id[i] = g_strdup(get_reservation_user_id(current_reservation));
        result.rating[i] = g_strdup(get_reservation_rating(current_reservation));
    }

    // Liberta a memória alocada
    g_list_free(hotel_reservations_list);   

    return result;
}