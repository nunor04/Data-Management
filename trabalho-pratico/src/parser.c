#include <stdio.h>
#include <stdlib.h>
#include <verificar.h>

#include "../include/parser.h"
#include "../include/catalogos/catalogos_manager.h"


//adicionar o resto dos catálogos

/*  
    Neste módulo vai ser feita a preparação dos dados para posteriormente serem armazenados nos catálogos

    Vamos ler as linhas todas de cada ficheiro .CSV e ao mesmo tempo, verificamos se cada linha é válida:
        Se a linha for inválida, vai ser escrita num ficheiro chamado ..._errors.CSV
        Se a linha for válida, vamos chamar a função do catálogo respetivo


    Dúvida:
        Será melhor usar strsep para ler cada linha até aos ';' e depois usar a função dos catálogos?
            ou
        Será melhor usar strtok para partir cada linha em tokens, e usá-los na função dos catálogos
        para não ter de percorrer a lista 2 vezes?
*/


// Verificar linha a linha se os flights são válidos e caso forem, usamos arrays de tokens para preencher as structs

// O func é para não termos de fazer 4 funções diferentes e apenas alteramos o argumento (flights,userdiz mes,etc)
void parsing_dos_users(char *path, Catalogs_Manager *manager)
 {
    /*
        1º Abrimos os CSV's

        2º Ver se a linha é válida
            se for válida, chamar catálogo respetivo
            senão, dar fprintf no errors.csv   
    
    */
    char *linha = NULL;
    size_t len = 0;
    
    FILE *file_saida_erros; // ficheiro onde vao ser colocados os erros
    FILE *file_entrada; // ficheiro onde se vao ler os dados


    // Abre o arquivo CSV para leitura e os arquivos CSV para escrita
    char *aux = malloc(strlen(path) + strlen("/users.csv") + 1);

    // É mais seguro do que strcat
    snprintf(aux, strlen(path) + strlen("/users.csv") + 1, "%s/users.csv", path);

    // Abrir o ficheiro com o caminho desejado
    file_entrada = fopen(aux, "r");

    // Verificar se o ficheiro foi aberto com sucesso
    if (file_entrada == NULL) 
     { 
        perror("Erro ao abrir o ficheiro");
        free(aux); 
        return;
     }
    
    file_saida_erros = fopen("../trabalho-pratico/Resultados/users_errors.csv", "w");
    

    while(getline(&linha,&len,file_entrada) != -1)
     {
        char* string = strdup(linha); // usada para armazenar a linha original
        char* tokens[12];
        if(validar_users(string,tokens) == 0)// se a linha for válida
         {  
            add_users_to_catalog(manager->catalog_users,tokens);
         } 
        else 
         {
                        
            fputs(linha,file_saida_erros); // escrever a linha no ficheiro dos errors

         }
        free(string);
        
        
     }
    fclose(file_entrada);
    fclose(file_saida_erros);
    free(linha);
    free(aux);
 }   

// void parsing_dos_flights(char *path, Catalogo_Users *catalog)
//  {

//     char *linha_f = NULL;
//     char *linha_p = NULL;
//     size_t len_f = 0;
//     size_t len_p = 0;
    
//     FILE *file_saida_erros_f;
//     FILE *file_saida_erros_p; // ficheiro onde vao ser colocados os erros
//     FILE *file_entrada_f;
//     FILE *file_entrada_p; // ficheiro onde se vao ler os dados

void parsing_dos_flights(char *path, Catalogs_Manager *manager){
        /*
        1º Abrimos os CSV's

        2º Ver se a linha é válida
            se for válida, chamar catálogo respetivo
            senão, dar fprintf no errors.csv   
    
    */
    char *linha_f = NULL;
    char *linha_p = NULL;
    
    size_t len_f = 0;
    size_t len_p = 0;

    FILE *file_saida_erros_f; // ficheiro onde vao ser colocados os erros
    //FILE *file_saida_erros_p; 
   
    FILE *file_entrada_f;
    FILE *file_entrada_p;


    // Abre o arquivo CSV para leitura e os arquivos CSV para escrita
    char *aux_f = malloc(strlen(path) + strlen("/flights.csv") + 1);
    char *aux_p = malloc(strlen(path) + strlen("/passengers.csv") + 1);

    // É mais seguro do que strcat
    snprintf(aux_f, strlen(path) + strlen("/flights.csv") + 1, "%s/flights.csv", path);
    snprintf(aux_p, strlen(path) + strlen("/passengers.csv") + 1, "%s/passengers.csv", path);

    // Abrir o ficheiro com o caminho desejado
    file_entrada_f = fopen(aux_f, "r");
    file_entrada_p = fopen(aux_p, "r");

    // Verificar se o ficheiro foi aberto com sucesso
    if (file_entrada_f == NULL) 
    { 
        perror("Erro ao abrir o ficheiro");
        free(aux_f);
        free(aux_p); 
        return;
    }
    
    if (file_entrada_p == NULL) 
    { 
        perror("Erro ao abrir o ficheiro");
        free(aux_p); 
        return;
    }
    
    file_saida_erros_f = fopen("../trabalho-pratico/Resultados/flights_errors.csv", "w");

    while(getline(&linha_f,&len_f,file_entrada_f) != -1){
        char* string = strdup(linha_f); // usada para armazenar a linha original
        char* tokens[14];
        int passenger_count = 0;
        
        char* linha_copy = strdup(linha_f);
        char* flight_id = strtok(linha_copy, ";");
        

        while (getline(&linha_p, &len_p, file_entrada_p) != -1) 
         {
          // Fazer uma cópia da linha para preservar a original
          char* tok = strtok(linha_p, ";");

          if (strcmp(flight_id, tok) != 0 && tok[0] == '0') 
           {
             break;
           }

          passenger_count++;
        }
        passenger_count++;

        if(validar_flights(string,tokens) == 0)
         {  // se a linha for válida

             int seats = 0;             
             sscanf(tokens[3],"%d",&seats);
             if(passenger_count <= seats)
             {
                  add_flight_to_catalog(manager->catalog_flights,tokens);
             }
             else  fputs(linha_f,file_saida_erros_f);
         } 
        else 
         {            
            fputs(linha_f,file_saida_erros_f); // escrever a linha no ficheiro dos errors
         }
        free(string);
        free(linha_copy);
    }
    fclose(file_entrada_f);
    fclose(file_entrada_p);
    fclose(file_saida_erros_f);
    free(linha_f);
    free(linha_p);
    free(aux_f);
    free(aux_p);
}


void parsing_das_reservations(char *path, Catalogs_Manager *manager)
 {
    /*
        1º Abrimos os CSV's

        2º Ver se a linha é válida
            se for válida, chamar catálogo respetivo
            senão, dar fprintf no errors.csv   
    
    */
    char *linha = NULL;
    size_t len = 0;
    
    FILE *file_saida_erros; // ficheiro onde vao ser colocados os erros
    FILE *file_entrada; // ficheiro onde se vao ler os dados


    // Abre o arquivo CSV para leitura e os arquivos CSV para escrita
    char *aux = malloc(strlen(path) + strlen("/reservations.csv") + 1);

    // É mais seguro do que strcat
    snprintf(aux, strlen(path) + strlen("/reservations.csv") + 1, "%s/reservations.csv", path);

    // Abrir o ficheiro com o caminho desejado
    file_entrada = fopen(aux, "r");

    // Verificar se o ficheiro foi aberto com sucesso
    if (file_entrada == NULL) 
     { 
        perror("Erro ao abrir o ficheiro");
        free(aux); 
        return;
     }
    
    file_saida_erros = fopen("../trabalho-pratico/Resultados/reservations_errors.csv", "w");
    
    int i = 0;

    while(getline(&linha,&len,file_entrada) != -1)
     {
        char* string = strdup(linha); // usada para armazenar a linha original
        char* tokens[14];


        if(validar_reservations(string,tokens) == 0)// se a linha for válida
         {       

            if(get_user_from_catalog(manager->catalog_users,tokens[1]) == NULL)
             {
               fputs(linha,file_saida_erros); 
             } else {
               // if(strcmp(tokens[2],"HTL1001") == 0) printf("%s\n",tokens[12]); //Aqui os ratings estão certos
               add_reservation_to_catalog_by_hotel_id_HT(manager->catalog_reservations,tokens[2],tokens);
               add_reservation_to_catalog_by_id_q4(manager->catalog_reservations,tokens[0],tokens); 
             }
         } else {                      
               fputs(linha,file_saida_erros); // escrever a linha no ficheiro dos errors
         }
        free(string);
        i++;
      
     }
    fclose(file_entrada);
    fclose(file_saida_erros);
    free(linha);
    free(aux);
 } 

void parsing_dos_passengers(char *path, Catalogs_Manager *manager)
 {
    /*
        1º Abrimos os CSV's

        2º Ver se a linha é válida
            se for válida, chamar catálogo respetivo
            senão, dar fprintf no errors.csv   
    
    */
    

    char *linha = NULL;
    size_t len = 0;
    
    FILE *file_saida_erros; // ficheiro onde vao ser colocados os erros
    FILE *file_entrada; // ficheiro onde se vao ler os dados


    // Abre o arquivo CSV para leitura e os arquivos CSV para escrita
    char *aux = malloc(strlen(path) + strlen("/passengers.csv") + 1);

    // É mais seguro do que strcat
    snprintf(aux, strlen(path) + strlen("/passengers.csv") + 1, "%s/passengers.csv", path);

    // Abrir o ficheiro com o caminho desejado
    file_entrada = fopen(aux, "r");

    // Verificar se o ficheiro foi aberto com sucesso
    if (file_entrada == NULL) 
     { 
        perror("Erro ao abrir o ficheiro");
        free(aux); 
        return;
     }
    
    file_saida_erros = fopen("../trabalho-pratico/Resultados/passengers_errors.csv", "w");
    

    while(getline(&linha,&len,file_entrada) != -1)
     {
        char* string = strdup(linha); // usada para armazenar a linha original
        char* tokens[4];
        
        // void add_user_to_catalog(Catalogo_Users* catalog, const char* user_id, const char* tokens[])
        if(validar_passengers(string,tokens) == 0)// se a linha for válida
         {  
             if(get_user_from_catalog(manager->catalog_users,tokens[1]) == NULL)
              {
                 fputs(linha,file_saida_erros);
              }
             else if(get_flight_from_catalog(manager->catalog_flights,tokens[0]) == NULL)
             {
               fputs(linha,file_saida_erros); 
             }
         } 
        else 
         {                      
            fputs(linha,file_saida_erros); // escrever a linha no ficheiro dos errors
         }
        free(string);
        
        
     }
    fclose(file_entrada);
    fclose(file_saida_erros);
    free(linha);
    free(aux);
 }
