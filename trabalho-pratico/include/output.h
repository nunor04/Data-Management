#ifndef OUTPUT_H
#define OUTPUT_H

#include "../include/interpreter.h"
#include "../include/queries/query3.h"
#include "../include/queries/query4.h"
#include "../include/queries/query7.h"
#include "../include/queries/query9.h"
#include "../include/catalogos/catalogos_manager.h"

void batch_mode_q3(int N, Query3 result, int formato, const char* targetHotel, int ficheiroVazio); // Se for vazio == 1
void batch_mode_q4(int N, QueryResult result, int formato, const char* hotel_id, int ficheiroVazio);
void batch_mode_q9(int N, Q9 result, int formato, const char* prefix, int ficheiroVazio);
void batch_mode_q7(int N, Q7 result, int formato, int ficheiroVazio);
void testsoutput(double testarray[], long QMem[]);

#endif