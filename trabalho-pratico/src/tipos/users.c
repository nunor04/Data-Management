#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/tipos/users.h"

//id;name;email;phone_number;birth_date;sex;passport;country_code;address;account_creation;pay_method;account_status
struct user{
    char* id;
    char* name;
    char* sex;
    char* passport;
    char* country_code;
    char* address;
    char* account_creation;   //mesma cena do birth_date
    char* account_status;   //"active ou inactive"
    char* age;
};

// Função para criar uma nova struct do user
UserDetails *create_user() {
    UserDetails *new_user = g_malloc(sizeof(struct user));

    // Inicializar todos os valores a NULL para ser mais fácil encontrar erros
    new_user->id = NULL;
    new_user->name = NULL;
    new_user->sex = NULL;
    new_user->passport = NULL;
    new_user->country_code = NULL;
    new_user->address = NULL;
    new_user->account_creation = NULL;
    new_user->account_status = NULL;

    return new_user;
}

// Função para construir a struct do user
UserDetails *build_user(char** tokens) {
    UserDetails *new_user = create_user();

    set_user_id(new_user, tokens[0]);
    set_user_name(new_user, tokens[1]);
    set_user_sex(new_user, tokens[5]);
    set_user_passport(new_user, tokens[6]);
    set_user_country_code(new_user, tokens[7]);
    set_user_address(new_user, tokens[8]);
    set_user_account_creation(new_user, tokens[9]);
    set_user_account_status(new_user, tokens[11]);

    return new_user;
}

UserDetails *build_user_tree(char** tokens){
    UserDetails *new_user = create_user();

    set_user_id(new_user, tokens[0]);
    set_user_name(new_user, tokens[1]);
    set_user_account_status(new_user, tokens[11]);

    return new_user;
}

// Funções para dar set a cada um dos parâmetros 
void set_user_id(UserDetails *user, const char *value) {
    user->id = g_strdup(value);
}

void set_user_name(UserDetails *user, const char *value) {
    user->name = g_strdup(value);
}

void set_user_sex(UserDetails *user, const char *value) {
    user->sex = g_strdup(value);
}

void set_user_passport(UserDetails *user, const char *value) {
    user->passport = g_strdup(value);
}

void set_user_country_code(UserDetails *user, const char *value) {
    user->country_code = g_strdup(value);
}

void set_user_address(UserDetails *user, const char *value) {
    user->address = g_strdup(value);
}

void set_user_account_creation(UserDetails *user, const char *value) {
    user->account_creation = g_strdup(value);
}

void set_user_account_status(UserDetails *user, const char *value) {
    user->account_status = g_strdup(value);
}

// Funções para dar get a cada um dos parâmetros
const char *get_user_id(const UserDetails *user) {
    return user->id;
}

const char* get_user_name(const UserDetails* user) {
    return user->name;  
}

const char *get_user_sex(const UserDetails *user) {
    return user->sex;
}

const char *get_user_passport(const UserDetails *user) {
    return user->passport;
}

const char *get_user_country_code(const UserDetails *user) {
    return user->country_code;
}

const char *get_user_address(const UserDetails *user) {
    return user->address;
}

const char *get_user_account_creation(const UserDetails *user) {
    return user->account_creation;
}

const char *get_user_account_status(const UserDetails *user) {
    return user->account_status;
}
//id;name;email;phone_number;birth_date;sex;passport;country_code;address;account_creation;pay_method;account_status
void free_users(UserDetails* user) {
    g_free(user->id);
    g_free(user->name);
    g_free(user->sex);
    g_free(user->passport);
    g_free(user->country_code);
    g_free(user->address);
    g_free(user->account_creation);
    g_free(user->account_status);
    g_free(user);
}

void free_users_tree(UserDetails* user) {
    g_free(user->id);
    g_free(user->name);
    g_free(user->account_status);
    g_free(user);
}


