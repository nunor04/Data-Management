// #include "../include/queries/query1.h"

// Q1 query1(Catalogs_Manager* manager, const char* id){
//     UserDetails* user = get_user_from_catalog(manager->catalog_users,id);
//     ReservationDetails* reservation = get_reservation_from_catalog(manager->catalog_reservations,id);
//     FlightDetails* flight = get_flight_from_catalog(manager->catalog_flights,)
// }










// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>
// #include "../include/structs/users.h"
// #include "../include/structs/passengers.h"
// #include "../include/structs/reservations.h"
// #include "../include/structs/flights.h"
// #include "../include/allqueries.h"



// //users: | nome;sexo;idade;código_do_país;passaporte | número_voos | número_reservas;total_gasto
// //                        users                         passengers             reservations

// //voo: | companhia;avião;origem;destino;partida_est;chegada_est; | número_passageiros;| tempo_atraso

// //reserva: id_hotel;nome_hotel;estrelas_hotel;data_início;data_fim;pequeno_almoço;número_de_noites;preço_total

// void capitalizeString(char *str) {
//     // Verifica se a string não está vazia
//     if (str && *str) {
//         // Converte o primeiro caractere para maiúsculo
//         *str = toupper(*str);

//         // Percorre o restante da string e converte para minúsculas
//         for (str++; *str; str++) {
//             *str = tolower(*str);
//         }
//     }
// }

// double calcatrasos(char* inputdata1, char* inputdata2) // Dado duas datas ela calcula a diferença entre elas em segundos
// {

//     double diferença = 0;
//     int x,y,z = 0;
//     int shoras,sminutos,ssegundos,rhoras,rminutos,rsegundos = 0;
//     char data[11];
//     char hora[9];
//     int sdata,rdata = 0;
//     sscanf(inputdata1, "%10s %8s", data, hora);
//     sscanf(hora,"%d:%d:%d",&shoras,&sminutos,&ssegundos);
//     sscanf(data,"%d/%d/%d",&x,&y,&z);
//     sdata = x*10000+y*100+z;


//     sscanf(inputdata2, "%10s %8s", data, hora);
//     sscanf(data,"%d/%d/%d",&x,&y,&z);
//     rdata = x*10000+y*100+z;
//     sscanf(hora,"%d:%d:%d",&rhoras,&rminutos,&rsegundos);
//     if(rdata != sdata)
//     {

//     }
//     else
//     {
//         diferença = ((double)rhoras - (double)shoras)*3600+((double)rminutos-(double)sminutos)*60+((double)rsegundos-(double)ssegundos);
//     }

//     return diferença;              

// }

// double preço_total(char* begindate, char* enddate, int price_per_night, int icity_tax) //Com os dados necessarios, calcula o preço total
// {

//            int ano,mes,dia,bdata,edata,noites,preço_noite,city_tax = 0;
//            double preço_total = 0;

//            preço_noite = price_per_night;
//            city_tax = icity_tax;

//             sscanf(enddate,"%d/%d/%d",&ano,&mes,&dia);
//             edata = 10000*ano+100*mes+dia;

//             sscanf(begindate,"%d/%d/%d",&ano,&mes,&dia);
//             bdata = 10000*ano+100*mes+dia;

//             noites = edata - bdata;

//             preço_total = (double)noites*(double)preço_noite+(((double)preço_noite*(double)noites)/100*(double)city_tax);

//             return preço_total;
// }

// int query1Verifica(char* ID) // Verifica o caso do utilizador ser inactive
// {
//     for(int i = 0; i < global_user_count; i++)
//      {
//         if(strcmp(global_user_data[i].id,ID) == 0)
//         {
//           if(strcasecmp(global_user_data[i].account_status,"inactive\n") == 0)  // Na account_status a string account_status possui um /n no final
//           {
//             return 1;
//           }
//           else break;
//         } 
//      }
//   return 0;
// }    
//   Q1output query1Book(char* ID) //No caso de ser uma Reserva
//   {
//        Q1output output;

//        int encontrado = 0;

//        for(int i = 0; i < global_reservation_count; i++)
//        {
//          if(strcmp(ID,global_reservation_data[i].id) == 0)
//          {
//             encontrado = 1;

//             output.cena1 = global_reservation_data[i].hotel_id;
//             output.cena2 = global_reservation_data[i].hotel_name;
//             output.cena3 = global_reservation_data[i].hotel_stars;
//             output.cena4 = global_reservation_data[i].begin_date;
//             output.cena5 = global_reservation_data[i].end_date;
//             output.cena6 = global_reservation_data[i].includes_breakfast;

//             capitalizeString(output.cena6);

//             int ano,mes,dia,bdata,edata,noites,preço_noite,city_tax = 0;
//             double preço_total = 0;

//             sscanf(global_reservation_data[i].end_date,"%d/%d/%d",&ano,&mes,&dia);
//             edata = 10000*ano+100*mes+dia;

//             sscanf(global_reservation_data[i].begin_date,"%d/%d/%d",&ano,&mes,&dia);
//             bdata = 10000*ano+100*mes+dia;

//             noites = edata - bdata;

//             output.cena7 = noites;

//             sscanf(global_reservation_data[i].price_per_night,"%d",&preço_noite);

//             sscanf(global_reservation_data[i].city_tax,"%d",&city_tax);

//             preço_total = (double)noites*(double)preço_noite+(((double)preço_noite*(double)noites)/100*(double)city_tax);


//             output.cena8 = preço_total;

//          }
//        }
//      if(encontrado == 0) output.cena1 = "NADA";
//       return output;
//     }
//     Q1output query1Flight(char* ID)
//     {
//         Q1output output;

//         int encontrado = 0;
//         for(int i = 0; i < global_flight_count; i++)
//        {
//          if(strcmp(ID,global_flight_data[i].id) == 0)
//          {
//             encontrado = 1;

//             output.cena1 = global_flight_data[i].airline;
//             output.cena2 = global_flight_data[i].plane_model;
//             output.cena3 = global_flight_data[i].origin;
//             output.cena4 = global_flight_data[i].destination;
//             output.cena5 = global_flight_data[i].schedule_departure_date;
//             output.cena6 = global_flight_data[i].schedule_arrival_date;

//             int npassageiros = 0;
//             int encontrado = 0;

//             for(int i = 0; i < global_passenger_count; i++)
//             {
//                 if(strcmp(global_passenger_data[i].flight_id,ID) == 0)
//                 {
//                     npassageiros++;
//                     encontrado = 1;
//                 }
//                 else if(encontrado == 1)
//                 {
//                     break;
//                 }
//             }

//              output.cena7 = npassageiros;

//              output.cena8 = calcatrasos(global_flight_data[i].schedule_departure_date,global_flight_data[i].real_departure_date);

//          }
//        }
//      if(encontrado == 0) output.cena1 = "NADA";
//       return output;
//     }
//      Q1useroutput query1User(char* ID)
//     {
//         Q1useroutput output;
//       int encontrado = 0;
//        for(int i = 0; i < global_user_count; i++)
//        {
//          if(strcmp(ID,global_user_data[i].id) == 0)
//          {
//             encontrado = 1;

//             output.cena1 = global_user_data[i].name;
//             output.cena2 = global_user_data[i].sex;
//             output.cena4 = global_user_data[i].country_code;
//             output.cena5 = global_user_data[i].passport;

//             int age = 0;
//             int ano, mes, dia = 0;

//             sscanf(global_user_data[i].birth_date,"%d/%d/%d",&ano,&mes,&dia);

//             age = 2023 - ano;
//             if(mes > 10) age--;

//              output.cena3 = age;           

//             int nvoos = 0;

//             for(int i = 0; i < global_passenger_count; i++)
//             {
//                 if(strcmp(global_passenger_data[i].user_id,ID) == 0)
//                 {
//                     nvoos++;
//                 }
//             }

//              output.cena6 = nvoos;

//             int nreservas = 0;
//             double preçototal = 0;
//             int preço_noite = 0;
//             int taxacidade = 0;



//             for(int i = 0; i < global_reservation_count; i++)
//             {
//                 if(strcmp(global_reservation_data[i].user_id,ID) == 0)
//                 {
//                     nreservas++;
//                     sscanf(global_reservation_data[i].price_per_night,"%d", &preço_noite);
//                     sscanf(global_reservation_data[i].city_tax,"%d", &taxacidade);
//                     preçototal+= preço_total(global_reservation_data[i].begin_date,global_reservation_data[i].end_date, preço_noite, taxacidade);
//                 }
//             }

//              output.cena7 = nreservas;
//              output.cena8 = preçototal;


//          }
//        }
//       if(encontrado == 0) output.cena1 = "NADA";
//       return output;
//     } 