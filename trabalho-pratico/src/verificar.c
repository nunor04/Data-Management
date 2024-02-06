#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// #include "../include/auxiliares.h"


// // Declaração das funções (por causa dos warnings) 
int validar_email(const char* email);
int possui_delimitadores_consecutivos(const char* linha);
int valida_data(char *token);  
int valida_hora(char *hora);
int eInteiro(const char* str);

int validar_users(char* linha, char** tokens) 
{
    int valido = 0;  // usado para identificar se uma linha é valida ou nao depois de todas as verificações
    int token_count = 0; // conta os ; para identificar em que parte da linha está

    if(linha[0] == ';'){
        return 1;
    }

    // if(possui_delimitadores_consecutivos(linha) > 0) // analisa se existem ;; seguidos, sinalizando falta de informação na linha
    // {
    //     valido = 1;
    //     return valido;
    // }

    // Tokeniza a linha usando ';' como delimitador
    char* token = NULL;

    while ((token = strsep(&linha, ";")) != NULL) 
    {    
        tokens[token_count] = token;

        if(strlen(token) < 1) return 1;

        // if(token_count == 1){
        //   if(strlen(token) < 1) return 1;
        // }

        // Identifica quando estamos no segundo token (índice 2) que representa o e-mail
        if (token_count == 2)
        {
            // Verifica se o e-mail possui o formato desejado
            if (validar_email(token) == 0) 
            {
                valido = 1; // invalida a linha
                return valido; // sai do loop pois não é necessária mais verificação
            }
        }

        else if (token_count == 4) // Token da data de nascimento. Verificação da data de nascimento
        {
            if(valida_data(token) == 1) // Verifica o formato da data
            {
                valido = 1; // invalida a linha
                return valido; // sai do loop pois não é necessária mais verificação
            } 
        }

        else if(token_count == 7) // Token da nacionalidade. Verifica a nacionalidade
        {
            if(strlen(token) != 2)  // Verifica se cumpre o comprimento 
            {
                valido = 1;
                return valido;
            } 
        }

        else if(token_count == 9) // Token da account_creation date
        {
            char data[11]; // Para armazenar a data (incluindo o caractere nulo)
            char hora[9];  // Para armazenar a hora (incluindo o caractere nulo)
            sscanf(token, "%10s %8s", data, hora); // retira do token uma string com a data e outra com a hora

            if(valida_data(data) == 1 || valida_hora(hora) == 1) // verifica o formato da data e hora
            {
                valido = 1;
                return valido;
            }
        } 

        else if(token_count == 11) // Account_status
        {
            if(strcasecmp(token,"active\n") != 0 && strcasecmp(token,"inactive\n") != 0)
            {
                valido = 1;
                return valido;
            } 
        }

        token_count++;
    }

    return valido;
}


int validar_flights(char* linha, char** tokens) 
{
    //char* linha = NULL; // string onde sera armazenada a linha 
    int valido; //se for = 1, é inválido, se for = 0 é válido

   // Lê as linhas do arquivo
   
        valido = 0;
        int token_count = 0; // conta os ; para identificar em que parte da linha está
        // Tokeniza a linha usando ';' como delimitador
        char* token = NULL;

        if(linha[0] == ';')  //Verifica se existe id
        {   
          valido = 1;
          return valido;
       }
        // Itera sobre os tokens
        while ((token = strsep(&linha, ";")) != NULL) 
        {    
            tokens[token_count] = token;
            
            char s_d_d[11];
            char s_d_h[9];
            char s_a_d[11];
            char s_a_h[9];
            char r_d_d[11];
            char r_d_h[9];
            char r_a_d[11];
            char r_a_h[9];
            //Quando chegamos ao segundo token (índice 2), que representa o e-mail
            int flight_id;
            
            if(strlen(token) < 1) return 1;

            if ((token_count == 0)) 
            {
              sscanf(token,"%d",&flight_id);
            }
            else if(token_count == 3)
            {
               if(eInteiro(token) == 0)
               {
                 valido = 1;
                 return valido;
               }
            }
            else if (token_count == 4)
            {
              if(strlen(token) > 3)
              {
                 valido = 1;
                 return valido;
              } 
            }
            else if (token_count == 5)
            {
              if(strlen(token) > 3)
              {
                 valido = 1;
                 return valido;
              } 
            }
            else if (token_count == 6) // Token da data. Verificação da data
            {
               sscanf(token, "%10s %8s", s_d_d, s_d_h);

               if(valida_data(s_d_d) == 1 || valida_hora (s_d_h) == 1)
               {
                 valido = 1;
                 return valido;
               }
            }
            else if(token_count == 7) // Token da nacionalidade. Verifica a nacionalidade
            {
               sscanf(token, "%10s %8s", s_a_d, s_a_h);

               if(valida_data(s_a_d) == 1 || valida_hora (s_a_h) == 1)
               {
                 valido = 1;
                 return valido;
               }
            }
            else if(token_count == 8) // Token da birth_date
            {
               sscanf(token, "%10s %8s", r_d_d, r_d_h);

               if(valida_data(r_d_d) == 1 || valida_hora (r_d_h) == 1)
               {
                 valido = 1;
                 return valido;
               }
            }
            else if(token_count == 9)
            {
               if(token[10] != ' ') return 1;
               sscanf(token, "%10s %8s", r_a_d, r_a_h);

               if(valida_data(r_a_d) == 1 || valida_hora (r_d_h) == 1)
               {
                 valido = 1;
                 return valido;
               }
              int s_dd, s_dh, s_ad, s_ah, r_dd, r_dh, r_ad, r_ah;
              int x,y,z;
              sscanf(s_d_d, "%d/%d/%d", &x,&y,&z); // retira os inteiros da string
              s_dd = x*10000+y*100+z; // transforma num inteiro

              sscanf(s_d_h, "%d:%d:%d",&x,&y,&z);
              s_dh = x*10000+y*100+z;
              
              sscanf(s_a_d, "%d/%d/%d", &x,&y,&z); // retira os inteiros da string
              s_ad = x*10000+y*100+z; // transforma num inteiro

              sscanf(s_a_h, "%d:%d:%d",&x,&y,&z);
              s_ah = x*10000+y*100+z;
              
              if(s_dd > s_ad)
              {
                 valido = 1;
                 return valido;
              }
              else if(s_dh > s_ah)
              {
                 valido = 1;
                 return valido;
              }
              sscanf(r_d_d, "%d/%d/%d", &x,&y,&z); // retira os inteiros da string
              r_dd = x*10000+y*100+z; // transforma num inteiro

              sscanf(r_d_h, "%d:%d:%d",&x,&y,&z);
              r_dh = x*10000+y*100+z;
              
              sscanf(r_a_d, "%d/%d/%d", &x,&y,&z); // retira os inteiros da string
              r_ad = x*10000+y*100+z; // transforma num inteiro

              sscanf(r_a_h, "%d:%d:%d",&x,&y,&z);
              r_ah = x*10000+y*100+z;
              
              if(r_dd > r_ad)
              {
                 valido = 1;
                 return valido;
              }
              else if(r_dh > r_ah)
              {
                 if(r_dd == r_ad) 
                 {
                   valido = 1;
                   return valido;
                 }
              }
              

            }
            // Avança para o próximo token

            token_count++;
      }
       
            
    // Libera a memória alocada para a linha
    return valido;
}

int validar_passengers(char* linha, char** tokens) 
{   
   int valido = 0;

   if(linha[0] == ';') 
    {
       valido = 1;
       return valido;
    }
    
    char* token = NULL;
    token = strsep(&linha, ";");

    tokens[0] = token;

    token = strsep(&linha, "\n");
 
    tokens[1] =  token;
    tokens[2] = "\0";
 
 return valido;
    
}

int validar_reservations(char* linha, char** tokens)
{

        int valido = 0;
        int miss = 0;

        // Tokeniza a linha usando ';' como delimitador
        char* token = NULL;

        int token_count =  0;
        
        if(linha[0] == ';')  //Verifica se existe id
        {   
            valido = 1;
            return valido;
        }

        while ((token = strsep(&linha, ";")) != NULL) 
        {    
          tokens[token_count] = token;

          if(strlen(token) < 1 && token_count != 10) return 1;
          
          int data1, data2 = 0;
          if ((token_count == 4)) 
          {
             
             float hotel_stars = 0;
             sscanf(token,"%f",&hotel_stars);
             if((hotel_stars < 1 || hotel_stars > 5) || hotel_stars != (float)((int)hotel_stars))
             {
                valido = 1;
                return valido;
             }
          }         
          else if (token_count == 5)
          {
             float city_tax = 0;
             sscanf(token,"%f",&city_tax);
             if(city_tax < 0 || city_tax != (float)((int)city_tax))
             {
                valido = 1;
                return valido;
             } 
          }
          else if (token_count == 7)
          {
            int ano, mes, dia;
            if(valida_data(token) == 1)
            {
                valido = 1;
                return valido;
            } 
            sscanf(token,"%d/%d/%d", &ano, &mes, &dia);
            data1 = ano*10000+mes*100+dia;
          }
          else if (token_count == 8)
          {
            int ano, mes, dia;
            if(valida_data(token) == 1)
            {
              valido = 1;
              return valido;
            } 
            sscanf(token,"%d/%d/%d", &ano,&mes,&dia);
            data2 = ano*10000+mes*100+dia;
            if(data2 < data1)
            {
                valido = 1;
                return valido;
            } 
          }
          else if(token_count == 9)
          {
             float price = 0;
             sscanf("5","%f",&price);
             if(price < 0 || price != (float)((int)price))
             {
                valido = 1;
                return valido;
             } 
          } 
          else if(token_count == 10)
          {
            if(miss == 0)
            {
               if(strcasecmp(token,"true") != 0 && strcasecmp(token,"false") != 0 && strcasecmp(token,"t") != 0 && strcasecmp(token,"f") != 0 && strlen(token) > 1)  
               {
                 int bin;
                 sscanf(token,"%d", &bin);
                 if(bin != 1 && bin != 0)
                 {
                    valido = 1;
                    return valido;
                 }
               }          
            }
          
          } 
        // Avança para o próximo token
        token_count++;
    }

    return valido;
}

int validar_email(const char* email) 
{
    int at_count = 0; // arrobas
    int dot_count = 0; // pontos
    int chr_count = 0; // caracters
    int count_a = 0; // caracteres ate ao @
    int count_a_p = 0; // caracters do @ ao .
    for (int i = 0; email[i] != '\0'; i++) 
    {
        chr_count++;
        if (email[i] == '@') 
        {
            at_count++;
            count_a = chr_count; // conta os caracteres ate ao arroba
            chr_count = 0;
        } 
        else if (email[i] == '.') 
        {
            count_a_p = chr_count; 
            dot_count++;        // conta os caracteres do '
            chr_count = 0;
        }
    }

    // Verifica se há exatamente um '@' e pelo menos um '.' no email e se os caracteres entre eles estao no numero indicado no formato
    if (at_count == 1 && dot_count >= 1 && count_a >=1  && count_a_p >= 1 && chr_count >1) // chr_count sao os caracteres TDL
    {
        return 1;  // Email válido
    } else {
        return 0;  // Email inválido
    }
}

int possui_delimitadores_consecutivos(const char* linha) 
{
   int delimitadores_consecutivos = 0;
    for (int i = 0; linha[i] != '\0'; i++) 
    {   
        if (linha[i] == ';' && linha[i + 1] == ';') 
        {
            delimitadores_consecutivos++;
        }
        
    }
  return delimitadores_consecutivos;
}

int valida_data(char *token)       //so ativa se o n token for 4, pegando no token criado
{
        int ano = 0;
        int mes = 0;
        int dia = 0;
        int i = 0;

    while(token[i] != '\0')         //ele verifica se os / estao no sitío certo e se é isso que estao a usar
    {
        if (i == 4 &&  token[i] != '/')     //nnnn/nn/nn
            return 1;
        else if (i == 7 &&  token[i] != '/')
            return 1;
        i++;
    }
    if (i!=10)       //se, por acaso, tivemos datas com mais numero de caracteres no fim, corta
        return 1;
    i = 0;   
    
  sscanf(token,"%d/%d/%d",&ano,&mes,&dia);
    
  if(ano > 2023 || ano < 1907 || mes > 12 || dia > 31 || dia < 1 || mes < 1) return 1;
  

      if(ano == 2023)
    {
        if(mes > 10) return 1;
        else if(mes == 10)
        {                                 //Verifica se a data de nascimento e inferior ao presente.
            if(dia > 1) return 1;
        }
    }
  
  return 0;
}

int valida_hora(char *hora)
{
  int horas;
  int minutos;
  int segundos;
  int i = 0;

    while(hora[i] != '\0')         //ele verifica se os : estao no sitío certo e se é isso que estao a usar
    {
        if (i == 2 &&  hora[i] != ':')     //nn:nn:nn
            return 1;
        if (i == 5 &&  hora[i] != ':')
            return 1;
        i++;
    }
    if(i != 8) return 1;
   sscanf(hora,"%d:%d:%d",&horas,&minutos,&segundos); // retira 3 ints da hora, as horas ,os minutos e os segundos
   if(horas > 23 || horas < 0 || minutos > 59 || minutos < 0 || segundos > 59 || segundos < 0) return 1;// verifica se respeitam as unidades
   
   return 0;

}

int eInteiro(const char *str) {
    // Verifica se a string é vazia
    if (str == NULL || *str == '\0') {
        return 0; // Não é um inteiro válido
    }

    // Percorre cada caractere da string
    while (*str) {
        // Verifica se o caractere atual não é um dígito
        if (!isdigit(*str)) {
            return 0; // Não é um inteiro válido
        }

        // Move para o próximo caractere
        str++;
    }

    return 1; // A string é composta apenas por inteiros
}

