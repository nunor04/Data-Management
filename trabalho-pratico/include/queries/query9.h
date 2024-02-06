#ifndef QUERY9_H
#define QUERY9_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/catalogos/catalogos_manager.h"
#include "../include/catalogos/catalogo_users.h"
#include "../include/tipos/users.h"

typedef struct query9{
    int contador;
    char** id;
    char** name;
} Q9;

Q9 query9(Catalogs_Manager* catalog, const char* prefix);

#endif