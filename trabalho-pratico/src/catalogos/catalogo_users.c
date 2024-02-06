#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/catalogos/catalogo_users.h"
#include "../include/tipos/users.h"

#include <ctype.h>
#include <strings.h>
#include <locale.h>

//no parser vou chamar as funçoes dos catalogos e cada função só vai ser executada numa linha e o ciclo while vai tar só no parser

struct users{
    GHashTable* users_hash_table;
    UsersTree* users_tree;
    //podemos definir outras estruturas
};


// Função para criar um novo nó
static Node* create_node(UserDetails* user) { //se criar uma struct so para isto dá para otimizar o tempo e a mem
    Node* new_node = malloc(sizeof(Node));
    if (new_node != NULL) {
        new_node->user = user;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}

// Função de comparação para a árvore de busca binária
static int compare_users(const UserDetails* a, const UserDetails* b) {
    setlocale(LC_COLLATE, "en_US.UTF-8");
    int name_comparison = strcoll(get_user_name(a), get_user_name(b));

    if (name_comparison == 0) {
        return strcoll(get_user_id(a), get_user_id(b));
    } else {
        return name_comparison;
    }
}

// Função para adicionar um user à árvore
static Node* insert_user(Node* root, UserDetails* new_user) {
    if (root == NULL) {
        return create_node(new_user);
    }

    int comparison_result = compare_users(new_user, root->user);

    if (comparison_result < 0) {
        root->left = insert_user(root->left, new_user);
    } else if (comparison_result > 0) {
        root->right = insert_user(root->right, new_user);
    }

    return root;
}



Catalogo_Users* create_users_catalog() {
    Catalogo_Users* catalog = g_malloc(sizeof(struct users));
    catalog->users_hash_table = g_hash_table_new(g_str_hash, g_str_equal);
    catalog->users_tree = malloc(sizeof(UsersTree));
    catalog->users_tree->root = NULL;
    return catalog;
}

// Função para adicionar um User à HT do catalogo dos users
void add_user_to_catalog(Catalogo_Users* catalog, const char* user_id, UserDetails* new_user) {
    g_hash_table_insert(catalog->users_hash_table, g_strdup(user_id), new_user);
}

// Função para dar get de um User da HT, organizada pelo id
UserDetails* get_user_from_catalog(Catalogo_Users* catalog, const char* user_id) {
    return g_hash_table_lookup(catalog->users_hash_table, user_id);
}

// Função para libertar a memória da árvore de busca binária
static void free_users_tree_recursive(Node* root) {
    if (root != NULL) {
        free_users_tree_recursive(root->left);
        free_users_tree_recursive(root->right);
        free_users_tree(root->user);  // Liberta memória do UserDetails
        free(root);
    }
}

// Função para libertar os users do catálogo e o catálogo
void free_users_catalog(Catalogo_Users* catalog) {
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, catalog->users_hash_table);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        // key é a string alocada com g_strdup, e value é UserDetails*
        g_free(key);  // Libertar a chave (user_id)
        free_users(value);  // Libertar o UserDetails
    }

    g_hash_table_destroy(catalog->users_hash_table);

    free_users_tree_recursive(catalog->users_tree->root);
    free(catalog->users_tree);

    g_free(catalog);
}


// Função para adicionar um user com o account_status active à árvore
void add_active_user(Catalogo_Users* catalog, UserDetails* new_user) {
    if (strcasecmp(get_user_account_status(new_user), "active\n") == 0) {
        catalog->users_tree->root = insert_user(catalog->users_tree->root, new_user);
    } else {
        free_users(new_user); // Libertar a memória para users inactive
    }
}

void add_users_to_catalog(Catalogo_Users* catalog, char** tokens) {

    // Converter os tokens em UserDetails
    UserDetails* new_user_by_id = build_user(tokens);
    UserDetails* new_user_tree = build_user_tree(tokens);

    add_user_to_catalog(catalog, get_user_id(new_user_by_id), new_user_by_id);
    add_active_user(catalog, new_user_tree);
}

// Função para dar get da tree
Node* get_users_tree(const Catalogo_Users* catalog) {
    if (catalog == NULL) {
        return NULL;
    }
    return catalog->users_tree->root;
}