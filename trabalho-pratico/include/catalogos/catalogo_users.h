#ifndef CATALOGO_USERS_H
#define CATALOGO_USERS_H

#include "../tipos/users.h"

#include <glib.h>

typedef struct Node {
    UserDetails* user;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct {
    Node* root;
} UsersTree;

// Declaração da struct dos catálogos
typedef struct users Catalogo_Users;

// Função para inicializar o catálogo
Catalogo_Users* create_users_catalog();

// Função para adicionar um user ao catálogo
void add_user_to_catalog(Catalogo_Users* catalog, const char* user_id, UserDetails* new_user);

UserDetails* get_user_from_catalog(Catalogo_Users* catalog, const char* user_id);

// Função para libertar memória do catálogo
void free_users_catalog(Catalogo_Users* catalog);

void add_active_user(Catalogo_Users* catalog, UserDetails* new_user);
Node* get_users_tree(const Catalogo_Users* catalog);

void add_users_to_catalog(Catalogo_Users* catalog, char** tokens);


#endif
