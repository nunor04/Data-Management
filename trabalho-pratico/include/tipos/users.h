#ifndef USERS_H
#define USERS_H

#include <glib.h>

typedef struct user UserDetails;

// Função para criar a struct do user
UserDetails *create_user();

// Função para construir struct onde vão ser guardados os valores
UserDetails *build_user(char** tokens);
UserDetails *build_user_tree(char** tokens);

void free_users(UserDetails* user);
void free_users_tree(UserDetails* user);

// Funções para dar set de cada parâmetro do user
void set_user_id(UserDetails *user, const char *value);
void set_user_name(UserDetails *user, const char *value);
void set_user_email(UserDetails *user, const char *value);
void set_user_phone_number(UserDetails *user, const char *value);
void set_user_birth_date(UserDetails *user, const char *value);
void set_user_sex(UserDetails *user, const char *value);
void set_user_passport(UserDetails *user, const char *value);
void set_user_country_code(UserDetails *user, const char *value);
void set_user_address(UserDetails *user, const char *value);
void set_user_account_creation(UserDetails *user, const char *value);
void set_user_pay_method(UserDetails *user, const char *value);
void set_user_account_status(UserDetails *user, const char *value);

void set_with_glib_user_id(UserDetails *user, const char *value);
void set_with_glib_user_name(UserDetails *user, const char *value);
void set_with_glib_user_email(UserDetails *user, const char *value);
void set_with_glib_user_phone_number(UserDetails *user, const char *value);
void set_with_glib_user_birth_date(UserDetails *user, const char *value);
void set_with_glib_user_sex(UserDetails *user, const char *value);
void set_with_glib_user_passport(UserDetails *user, const char *value);
void set_with_glib_user_country_code(UserDetails *user, const char *value);
void set_with_glib_user_address(UserDetails *user, const char *value);
void set_with_glib_user_account_creation(UserDetails *user, const char *value);
void set_with_glib_user_pay_method(UserDetails *user, const char *value);
void set_with_glib_user_account_status(UserDetails *user, const char *value);

// Funções para dar get de cada parâmetro do user
const char *get_user_id(const UserDetails *user);
const char *get_user_name(const UserDetails *user);
const char *get_user_email(const UserDetails *user);
const char *get_user_phone_number(const UserDetails *user);
const char *get_user_birth_date(const UserDetails *user);
const char *get_user_sex(const UserDetails *user);
const char *get_user_passport(const UserDetails *user);
const char *get_user_country_code(const UserDetails *user);
const char *get_user_address(const UserDetails *user);
const char *get_user_account_creation(const UserDetails *user);
const char *get_user_pay_method(const UserDetails *user);
const char *get_user_account_status(const UserDetails *user);

#endif 
