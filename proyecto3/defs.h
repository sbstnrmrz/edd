// Participantes: 
// Sebastian Ramirez C.I:31567908
// Angel Vivas       C.I:30890743

#ifndef DEFS_H
#define DEFS_H

#include <iostream>
#include <ctime>
#include <chrono>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <string.h>
using namespace std;

#if __WIN32
#define CLEAR system("cls")
#define SLEEP(secs) {                                        \
    char buf[32] = {0};                                      \
    sprintf(buf, "timeout /t %d /nobreak > nul", (int)secs); \
    system(buf);                                             \
}
#define DELETE_FILE(file) {            \
    char str[32] = {0};                \
    snprintf(str, 32, "del %s", file); \
    system(str);                       \
}
#elif __APPLE__
#define CLEAR system("clear")
#define SLEEP(secs) {                    \
    char str[32] = {0};                  \
    snprintf(str, 32, "sleep %f", secs); \
    system(str);                         \
}
#define DELETE_FILE(file) {           \
    char str[32] = {0};               \
    snprintf(str, 32, "rm %s", file); \
    system(str);                      \
}
#endif

#define ARRAY_LEN(x) sizeof(x)/sizeof(x[0])

typedef struct {
    int *data;
    size_t size;
} cola_t;

typedef struct {
    int *data;
    size_t size;
} pila_t;

void cola_enqueue(cola_t *cola, int data);
void cola_dequeue(cola_t *cola);
int  cola_front(cola_t cola);
int  cola_rear(cola_t cola);
bool cola_is_empty(cola_t cola);
// debido al uso de colas dinamicas no se usa esta funcion
bool cola_is_full(cola_t cola);
int  cola_size(cola_t cola);

void pila_push(pila_t *pila, int data);
void pila_pop(pila_t *pila);
bool pila_is_empty(pila_t pila);
// debido al uso de pilas dinamicas no se usa esta funcion
bool pila_is_full(pila_t pila);
int  pila_top(pila_t pila);
int  pila_size(pila_t pila);


#endif
