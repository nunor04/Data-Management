#ifndef PARSER_H
#define PARSER_H

#include "../include/catalogos/catalogos_manager.h"

void parsing_dos_users(char *path, Catalogs_Manager *manager);
void parsing_das_reservations(char *path, Catalogs_Manager *manager);
void parsing_dos_flights(char *path, Catalogs_Manager *manager);
void parsing_dos_passengers(char *path, Catalogs_Manager *manager);

#endif