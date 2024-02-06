#include "../include/queries/query9.h"

// Função auxiliar para percorrer a árvore e encontrar usuários com o prefixo fornecido
static void find_users_with_prefix(Node* root, const char* prefix, Q9* result) {
    if (root == NULL) {
        return;
    }

    find_users_with_prefix(root->left, prefix, result);

    // Verifica se o nome do usuário contém o prefixo
    if ((prefix[0] == '"' &&
        strncmp(get_user_name(root->user), prefix + 1, strlen(prefix) - 2) == 0) || (strncmp(get_user_name(root->user), prefix, strlen(prefix)) == 0)){
        result->contador++;

        // Realoca memória para elementos adicionais nos arrays
        result->id = realloc(result->id, result->contador * sizeof(char*));
        result->name = realloc(result->name, result->contador * sizeof(char*));

        // Copia o ID e o nome do usuário
        result->id[result->contador - 1] = strdup(get_user_id(root->user));
        result->name[result->contador - 1] = strdup(get_user_name(root->user));
    }

    find_users_with_prefix(root->right, prefix, result);
}

Q9 query9(Catalogs_Manager* manager, const char* prefix) {
    Q9 result;
    result.contador = 0;
    result.id = NULL;
    result.name = NULL;

    // Obtém toda a árvore de usuários
    Node* users_tree = get_users_tree(manager->catalog_users);

    // Encontra usuários com o prefixo fornecido
    find_users_with_prefix(users_tree, prefix, &result);

    return result;
}









// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>
// #include <locale.h>
// #include "../include/structs/users.h"
// #include "../include/structs/passengers.h"
// #include "../include/structs/reservations.h"
// #include "../include/structs/flights.h"
// #include "../include/allqueries.h"



// // Input : Prefixo do id
// // Output: id;name de todos os utilizadores com esse prefixo por ordem de nome(crescente), desempate com o id.

// // Função de comparação para qsort (ignorando maiúsculas, minúsculas e acentos)

// int compare_strings(const void* a, const void* b) 
// {
//     int name_comparison = strcoll(((Q9users*)a)->name, ((Q9users*)b)->name);
    
//     // If names are equal, compare by IDs
//     if (name_comparison == 0) 
//     {
//         return strcoll(((Q9users*)a)->id, ((Q9users*)b)->id);
//     } 
//     else 
//     {
//         return name_comparison;
//     }
// }


// Q9users* query9(char* prefix) 
// {
//     size_t prefix_size = strlen(prefix);

//     Q9users* output = (Q9users*)malloc(sizeof(Q9users));
//     int nusers = 0;

//     setlocale(LC_COLLATE, "en_US.UTF-8");

//     for (int i = 0; i < global_user_count; i++) {
//         if (strncmp(global_user_data[i].name, prefix, prefix_size) == 0) {
//             if (strcasecmp(global_user_data[i].account_status, "inactive\n") == 0) 
//             {
//                 continue;
//             } 
//             else 
//             {
//                 output = (Q9users*)realloc(output, (nusers + 1) * sizeof(Q9users));
//                 output[nusers].id = strdup(global_user_data[i].id);
                
//                 output[nusers].name = strdup(global_user_data[i].name);
//                 nusers++;
//             }
//         }
//     }

//    if(nusers > 0) qsort(output, nusers, sizeof(Q9users), compare_strings);

//     output[0].contador = nusers;

//     return output;
// }