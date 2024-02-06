
//  #include <stdio.h>
//  #include <stdlib.h>
//  #include <string.h>
//  #include <ctype.h>
//  #include "../include/queries.h"
//  #include "../include/structs/flights.h"
//  #include "../include/structs/reservations.h"
//  #include "../include/structs/passengers.h"
//  #include "../include/structs/users.h"
//  #include "../include/allqueries.h"


// int compareDatesflightreser(const void* a, const void* b) {
//     FlightReservationInfo* flightreserA = (FlightReservationInfo*)a;
//     FlightReservationInfo* flightreserB = (FlightReservationInfo*)b;

    
//     // Compara os anos
//     int anoComp = strcmp(flightreserB->date, flightreserA->date);
//     if (anoComp != 0) {
//         return anoComp;
//     }

//     // Compara os meses 
//     int mesComp = strcmp(flightreserB->date + 5, flightreserA->date + 5);
//     if (mesComp != 0) {
//         return mesComp;
//     }

//     // Compara os dias
//     int diaComp = strcmp(flightreserB->date + 8, flightreserA->date + 8);
//     if (diaComp != 0) {
//         return diaComp;
//     }

//     // If departure_date is the same, compare flight_id in reverse order
//     return strcmp(flightreserA->id, flightreserB->id);
// }

// int query2Verifica(char* ID)
// {
//   int encontrado = 0;
 
//  for(int i = 0; i < global_user_count; i++)
//  {
//     if(strcmp(global_user_data[i].id,ID) == 0)
//     {
//       encontrado = 1;
//       if(strcasecmp(global_user_data[i].account_status,"inactive\n") == 0)  // Na account_status a string account_status possui um /n no final
//       {
//          return 1;
//       }
//     }
//  }
//   if(encontrado == 1) return 0;
//   else return 1;
// } 

// FlightReservationInfo* query2(char* ID, char* cena)
// {
//  if(strcmp(cena,"flights") == 0)
//  {
//     int idscounter = 0; 
//     char** ids = (char**) malloc(sizeof(char*)); // Malloc de IDS/ free na linha 114
//     for(int i = 0; i < global_passenger_count; i++)
//     {
//       if(strcmp(global_passenger_data[i].user_id,ID) == 0)
//       {
//         ids = (char**)realloc(ids, (idscounter + 1) * sizeof(char*));           // Malloc de IDS[i]/free na linha 111 

//         // Alocar espaço para o ID de voo e copiar o valor
//         ids[idscounter] = strdup(global_passenger_data[i].flight_id);
        
//         idscounter++;
//       }
//     }
   
//    FlightReservationInfo* flightInfos = (FlightReservationInfo*)malloc(sizeof(FlightReservationInfo)); // Malloc de flightInfos/ free programa-principal.c linha:301(caso F) e 370

//    int j = 0;
//    while(j < idscounter)
//    {
//     for(int i = 0; i < global_flight_count; i++)
//     {
//         if(strcmp(ids[j],global_flight_data[i].id) == 0) 
//         {
//           flightInfos = (FlightReservationInfo*)realloc(flightInfos,(j+1)*sizeof(FlightReservationInfo)); 
//           char data[11];
//           sscanf(global_flight_data[i].schedule_departure_date,"%10s",data);
          
//           flightInfos[j].id = strdup(ids[j]); // Malloc de flightInfos[i].id/ free programa-principal.c linha:299(caso F) e 368
          
          
//           flightInfos[j].date = strdup(data); // Malloc de flightInfos[i].date/ free programa-principal.c linha:298(caso F) e 367
          

//             break;
//         }
//     }
//      j++;
//    }
//     for (int i = 0; i < idscounter; i++)
//     {
//     flightInfos[i].contador = idscounter;
//     }
  
//    qsort(flightInfos, idscounter, sizeof(FlightReservationInfo), compareDatesflightreser);

    
//     for(int i = 0; i < idscounter; i++)
//     {
//         free(ids[i]);  // free de ids[i]
//     }
   
//    free(ids); //free IDS
//   return flightInfos;
//  }
//  else if(strcmp(cena, "reservations") == 0)
//  {
//     int bookidscounter = 0;
//     FlightReservationInfo* reservationInfos = (FlightReservationInfo*)malloc(sizeof(FlightReservationInfo)); // Malloc de flightInfos/ free programa-principal.c linha:301(caso f) e 370
    
//     for (int i = 0; i < global_reservation_count; i++)
//     {
//         if (strcmp(global_reservation_data[i].user_id, ID) == 0)
//         {
//             reservationInfos = (FlightReservationInfo*)realloc(reservationInfos, (bookidscounter + 1) * sizeof(FlightReservationInfo));
            
//             reservationInfos[bookidscounter].id = strdup(global_reservation_data[i].id); // Malloc de flightInfos[i].id/ free programa-principal.c linha:299(caso F) e 368
            
//             reservationInfos[bookidscounter].date = strdup(global_reservation_data[i].begin_date); // Malloc de flightInfos[i].date/ free programa-principal.c linha:298(caso F) e 367
            
//             bookidscounter++;
//         }
//     }
//        qsort(reservationInfos, bookidscounter, sizeof(FlightReservationInfo), compareDatesflightreser);
  
//     for (int i = 0; i < bookidscounter; i++)
//     {
//       reservationInfos[i].contador = bookidscounter;
//     }
  
//    return reservationInfos;  
//   }
//  else
//   {
//     int idscounter = 0; 
//     char** ids = (char**) malloc(sizeof(char*)); // Malloc de ids/ free na linha 195
//     for(int i = 0; i < global_passenger_count; i++)
//     {
//       if(strcmp(global_passenger_data[i].user_id,ID) == 0)
//       {
//         ids = (char**)realloc(ids, (idscounter + 1) * sizeof(char*)); // Malloc de ids[i] free na linha 192

//         // Alocar espaço para o ID de voo e copiar o valor
//         ids[idscounter] = strdup(global_passenger_data[i].flight_id);
        
//         idscounter++;
//       }
//     }

//     FlightReservationInfo* flightreserInfos = (FlightReservationInfo*)malloc(sizeof(FlightReservationInfo)); // Malloc de flightreserInfos/ free programa-principal.c linha:333(caso F) e 393

//    int j = 0;
//    while(j < idscounter)
//    {
//     for(int i = 0; i < global_flight_count; i++)
//     {
//         if(strcmp(ids[j],global_flight_data[i].id) == 0) 
//         {
//           flightreserInfos = (FlightReservationInfo*)realloc(flightreserInfos,(i+1)*sizeof(FlightReservationInfo)); // Malloc de flightInfos/ free programa-principal.c linha:333(caso F) e 393
//           char data[11];
//           sscanf(global_flight_data[i].schedule_departure_date,"%10s",data);
          
//           flightreserInfos[j].id = strdup(ids[j]); // Malloc de flightInfos[i].id/ free programa-principal.c linha:331(caso F) e 391

//           flightreserInfos[j].date = strdup(data); // Malloc de flightInfos[i].date/ free programa-principal.c linha:330(caso F) 390
//           flightreserInfos[j].date = realloc(flightreserInfos[j].date,strlen(flightreserInfos[j].date)+strlen(";flight")+1);
//           strcat(flightreserInfos[j].date,";flight");
//            j++;
//            break;
//         }
//     }
     
//    }
    
//     for(int i = 0; i < idscounter; i++)
//     {
//         free(ids[i]);  // free de ids[i]
//     }
//    free(ids); //free IDS


//     for (int i = 0; i < global_reservation_count; i++)
//     {
//         if (strcmp(global_reservation_data[i].user_id, ID) == 0)
//         {
//             flightreserInfos = (FlightReservationInfo*)realloc(flightreserInfos, (j+1) * sizeof(FlightReservationInfo)); // Malloc de flightInfos/ free programa-principal.c linha:333(caso F) e 393
            
//             flightreserInfos[j].id = strdup(global_reservation_data[i].id); // Malloc de flightInfos[i].id/ free programa-principal.c linha:331(caso F) e 391
            
//             flightreserInfos[j].date = strdup(global_reservation_data[i].begin_date); // Malloc de flightInfos[i].date/ free programa-principal.c linha:330(caso F) e 390
            
//             j++;
//         }
//     }
    

//     qsort(flightreserInfos, j, sizeof(FlightReservationInfo), compareDatesflightreser);

//     for (int i = 0; i < j; i++)
//     {
//         if(strstr(flightreserInfos[i].id,"Book") != NULL)
//         {
//           flightreserInfos[i].date = realloc(flightreserInfos[i].date,strlen(flightreserInfos[i].date)+strlen(";reservation")+1);
//           strcat(flightreserInfos[i].date,";reservation");
//         } 
//     }

//    for (int i = 0; i < j; i++)
//     {
//     flightreserInfos[i].contador = j;
//     }
  
//    return flightreserInfos;
//   }
// }