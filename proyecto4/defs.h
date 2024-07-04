// Participantes: 
// Sebastian Ramirez C.I:31567908
// Angel Vivas       C.I:30890743

#ifndef DEFS_H
#define DEFS_H

#include <iostream>
#include <ctime>
#include <chrono>
#include <list>
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

#define CHECK_RANGE(in, r1, r2) return true ? in > r1 && in < r2 : false

#define CHAR2INT(x) x - '0'

#define ARRAY_LEN(x) sizeof(x)/sizeof(x[0])

typedef enum {
    OPCIONAL = 1,
    BAJA     = 2,
    MEDIA    = 3,
    ALTA     = 4,
} prioridad;

typedef enum {
    SORT_ALFABETICAMENTE = 1,
    SORT_PRIORIDAD       = 2,
} sort_type;

typedef struct {
    std::string desc;
    prioridad prioridad;
} tarea_t;

struct _node_t {
    int data;
    struct _node_t *next;
};

typedef struct _node_t node_t;

struct _node_str_t {
    std::string data;
    struct _node_str_t *next;
};

typedef struct _node_str_t node_str_t;

struct _node_tarea_t {
    tarea_t tarea;
    struct _node_tarea_t *next;
};

typedef struct _node_tarea_t node_tarea_t;

typedef struct {
    node_t *head;
    size_t size;
} int_list;

typedef struct {
    node_str_t *head;
    size_t size;
} str_list;

typedef struct {
    node_tarea_t *head;
    int size;
} tarea_list;

bool check_str_int(const char *str);
void list_tarea_quick_sort(tarea_list *list, sort_type sort, int start, int end);
void list_tarea_push(tarea_list *list, tarea_t tarea);
void list_tarea_pop(tarea_list *list);
void list_tarea_insert(tarea_list *list, int pos, tarea_t tarea);
int list_tarea_remove(tarea_list *list, int pos);
tarea_t list_tarea_get(tarea_list list, int pos);
int list_tarea_set(tarea_list *list, int pos, tarea_t tarea);
int list_tarea_get_size(tarea_list list);
node_tarea_t *list_tarea_get_node(tarea_list list, int pos);
void print_tareas(tarea_list list);

#endif
