// Participantes: 
// Sebastian Ramirez C.I:31567908
// Angel Vivas       C.I:30890743

#include "defs.h"

bool check_str_int(const char* str) {
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        if (*str < 48 || *str > 57) {
            return false;
        } else {
            str++;
        }
    }
    return true;
}

void list_tarea_quick_sort(tarea_list *list, sort_type sort, int start, int end) {
    if (end <= start) {
        return;
    }

    tarea_t pivot = list_tarea_get(*list, end);
    int i = start-1;
    for (int j = start; j <= end; j++) {
        switch (sort) {
        case SORT_ALFABETICAMENTE:
            if (strcasecmp(list_tarea_get(*list, j).desc.c_str(), pivot.desc.c_str()) < 0) {
                i++;
                swap(list_tarea_get_node(*list, j)->tarea.desc, list_tarea_get_node(*list, i)->tarea.desc);
                swap(list_tarea_get_node(*list, j)->tarea.prioridad, list_tarea_get_node(*list, i)->tarea.prioridad);
            }
            break;
        case SORT_PRIORIDAD:
            if (list_tarea_get(*list, j).prioridad > pivot.prioridad) {
                i++;
                swap(list_tarea_get_node(*list, j)->tarea.desc, list_tarea_get_node(*list, i)->tarea.desc);
                swap(list_tarea_get_node(*list, j)->tarea.prioridad, list_tarea_get_node(*list, i)->tarea.prioridad);
            }
            break;
        }
    }
    i++;
    swap(list_tarea_get_node(*list, end)->tarea.desc, list_tarea_get_node(*list, i)->tarea.desc);
    swap(list_tarea_get_node(*list, end)->tarea.prioridad, list_tarea_get_node(*list, i)->tarea.prioridad);

    list_tarea_quick_sort(list, sort, start, i-1);
    list_tarea_quick_sort(list, sort, i+1, end);
}

void list_tarea_push(tarea_list *list, tarea_t tarea) {
    if (list->size < 1) {
        list->head = new node_tarea_t;
        list->head->tarea = tarea;
        list->head->next = NULL;
        list->size++;
        return;
    }
    
    node_tarea_t *node = list->head;
    while (node->next != NULL) {
        node = node->next;
    }

    node->next = new node_tarea_t;
    node->next->tarea = tarea;
    node->next->next = NULL;
    list->size++;
}


void list_tarea_pop(tarea_list *list) { 
    node_tarea_t *node = list->head;
    while (node->next != NULL) {
        node = node->next;
    }
    delete node->next;
    node->next = NULL;
    list->size--;
}

void list_tarea_insert(tarea_list *list, int pos, tarea_t tarea) {
    if (pos < 0 || pos > list->size) {
        printf("There are no elements in that position");
        return;
    }
    if (list->size < 1 && pos == 0) {
        list->head = new node_tarea_t;
        list->head->tarea = tarea;
        list->head->next = NULL;
        list->size++;
        return;
    }
    if (pos == 0) {
        node_tarea_t *aux = new node_tarea_t;
        aux->tarea = tarea;
        aux->next = list->head;
        list->head = aux;
        list->size++;
        return;
    }
    
    node_tarea_t *node = list->head;
    for (int i = 0; i < pos-1; i++) {
        node = node->next;
    }
    node_tarea_t *aux = new node_tarea_t;
    aux->tarea = tarea;
    if (pos == list->size) {
        aux->next = NULL;
    } else {
        aux->next = node->next;
    }
    node->next = aux;
    list->size++;
}

int list_tarea_remove(tarea_list *list, int pos) {
    if (pos >= list->size || pos < 0) {
        printf("Element in the position %d: doesnt exist\n", pos);
        return INT32_MIN;
    }
    node_tarea_t *node = list->head;
    for (int i = 0; i < pos-1; i++) {
        node = node->next; 
    }

    node_tarea_t *aux = NULL;
    if (pos == 0 && list->size < 2) {
        delete list->head; 
        list->head = NULL;
    }  else if (pos == 0) {
        aux = list->head;
        list->head = list->head->next;
    } else if (pos == list->size-1) {
        delete node->next;
        node->next = NULL;
    } else {
        aux = node->next;
        node->next = node->next->next;
    }
    if (aux != NULL) {
        delete aux;
    }
    list->size--;

    return 0;
}

node_tarea_t *list_tarea_get_node(tarea_list list, int pos) {
    if (pos >= list.size || pos < 0) {
        printf("Element in the position %d: doesnt exist\n", pos);
    }

    node_tarea_t *node = list.head;
    for (int i = 0; i < pos; i++) {
        node = node->next;
    }

    return node;
}

tarea_t list_tarea_get(tarea_list list, int pos) {
    if (pos >= list.size || pos < 0) {
        printf("Element in the position %d: doesnt exist\n", pos);
        exit(1);
    }
    node_tarea_t *node = list.head;
    for (int i = 0; i < pos; i++) {
        node = node->next;
    }

    return node->tarea;
}

int list_tarea_set(tarea_list *list, int pos, tarea_t tarea) {
    if (pos >= list->size || pos < 0) {
        printf("Element in the position %d: doesnt exist\n", pos);
        return -1;
    }
    node_tarea_t *node = list->head;
    for (int i = 0; i < pos; i++) {
        node = node->next;
    }
    node->tarea = tarea;

    return 0;
}

int list_tarea_get_size(tarea_list list) {
    return list.size;
}

void print_tareas(tarea_list list) {
    printf("________________________________________________________________\n");
    printf("|                          Lista de tarea                      |\n");
    printf("|______________________________________________________________|\n");
    printf("|                  Descripcion                  |  Prioridad   |\n");
    printf("|-----------------------------------------------|--------------|\n");
    for(int i = 0; i < list_tarea_get_size(list); i++) {
        tarea_t tarea = list_tarea_get(list, i);
        std::string str;
        if (tarea.prioridad == OPCIONAL) {
            str = "Opcional";
        }
        if (tarea.prioridad == BAJA) {
            str = "Baja";
        }
        if (tarea.prioridad == MEDIA) {
            str = "Media";
        }
        if (tarea.prioridad == ALTA) {
            str = "Alta";
        }
        printf("| [%d] %-41s | %-12s |\n", i+1, tarea.desc.c_str(), str.c_str());
    }

    printf("----------------------------------------------------------------\n\n");
}

int main(int argc, char *argv[]) {
    int num_tareas = 0;
    tarea_list list = {0};

    CLEAR;
    printf("  *********  ******      *****    ******  \n");
    SLEEP(0.25);
    printf("      *      *    *      *    *   *    *  \n");
    SLEEP(0.25);
    printf("      *      *    *      *     *  *    *  \n");
    SLEEP(0.25);
    printf("      *      *    *      *    *   *    *  \n");
    SLEEP(0.25);
    printf("      *      ******      *****    ******  \n");
    SLEEP(0.25);
    printf("                                          \n");
    SLEEP(0.25);
    printf("           *      *  ***** *********      \n");
    SLEEP(0.25);
    printf("           *      *  *         *          \n");
    SLEEP(0.25);
    printf("           *      *  *****     *          \n");
    SLEEP(0.25);
    printf("           *      *      *     *          \n");
    SLEEP(0.25);
    printf("           *****  *  *****     *          \n");
    SLEEP(1.0);

    printf("\nPresione ENTER para continuar");
    getchar();

    while (true) {
        CLEAR;
        char in[128] = {0};

        print_tareas(list);

        printf("1) Agregar tarea\n");
        printf("2) Eliminar tarea\n");
        printf("3) Modificar tarea\n");
        printf("4) Ordenar tareas\n");
        printf("5) Salir\n\n");
        printf("> ");
        cin.getline(in, 128);
        fflush(stdin);

        if (!check_str_int(in) || CHAR2INT(*in) < 0 || CHAR2INT(*in) > 5) {
            printf("Introduzca una opcion valida!\n"); 
            SLEEP(1.0);
            continue;
        }

        CLEAR;
        if (CHAR2INT(*in) == 1) {
            char desc[128] = {0};
            prioridad priori;

            print_tareas(list);

            printf("Introduzca la descripcion de la tarea: ");
            cin.getline(desc, 128);
            fflush(stdin);

            printf("Seleccione la prioridad de la tarea:\n");
            printf("  1) Opcional\n");
            printf("  2) Baja\n");
            printf("  3) Media\n");
            printf("  4) Alta\n\n");
            printf("> ");

            cin.getline(in, 128);
            fflush(stdin);

            if (!check_str_int(in) || stoi(in) < 0 || stoi(in) > 4) {
                printf("Introduzca una opcion valida\n"); 
                continue;
            }
            priori = (prioridad)(*in - '0');

            tarea_t tarea = {
                .desc = desc,
                .prioridad = priori
            };
            list_tarea_push(&list, tarea);

            printf("\nTarea agregada. Presione ENTER para continuar");
            getchar();
            continue;
        }
        if (CHAR2INT(*in) == 2 && list_tarea_get_size(list) > 0) {
            print_tareas(list);

            printf("Introduzca cual tarea desea eliminar: ");
            cin.getline(in, 128);
            fflush(stdin);
            if (!check_str_int(in)) {
                printf("Introduzca una opcion valida\n");
                SLEEP(1.0);
                continue;
            }
            if (!check_str_int(in) || stoi(in) < 1 || stoi(in)-1 > list_tarea_get_size(list)-1) {
                printf("Introduzca una opcion valida\n");
                SLEEP(1.0);
                continue;
            }
            list_tarea_remove(&list, CHAR2INT(*in)-1);

            printf("\nTarea [%d] eliminada. Presione ENTER para continuar", CHAR2INT(*in));
            getchar();
            continue;
        } else {
//          printf("\nNo existen tareas que eliminar!\n");
//          SLEEP(1.0);
//          continue;
        }

        if (CHAR2INT(*in) == 3 && list_tarea_get_size(list) > 0) {
            print_tareas(list);

            printf("Introduzca cual tarea desea modificar: ");
            cin.getline(in, 128);
            fflush(stdin);
            if (!check_str_int(in) || stoi(in) < 1 || stoi(in)-1 > list_tarea_get_size(list)-1) {
                printf("Introduzca una opcion valida\n");
                SLEEP(1.0);
                continue;
            }
            tarea_t tarea = list_tarea_get(list, CHAR2INT(*in)-1);
            int list_pos = stoi(in)-1;
            char desc[128] = {0};
            prioridad priori;

            printf("Que desea modificar?:\n");
            printf("  1) Descripcion\n");
            printf("  2) Prioridad\n");
            printf("  3) Ambas\n\n");
            printf("> ");
            cin.getline(in, 128);
            fflush(stdin);

            if (!check_str_int(in)) {
                printf("\nSolo enteros\n");     
                SLEEP(1.0);
                continue;
            }
            if (stoi(in) < 0 || stoi(in) > 3) {
                printf("\nIntroduzca una opcion valida\n");
                SLEEP(1.0);
                continue;
            }

            if (CHAR2INT(*in) == 1 || CHAR2INT(*in) == 3) {
                printf("Introduzca la nueva descripcion de la tarea: ");
                cin.getline(desc, 128);
                fflush(stdin);
                tarea.desc = desc;
            }
            if (CHAR2INT(*in) == 2 || CHAR2INT(*in) == 3) {
                printf("Seleccione la nueva prioridad de la tarea:\n");
                printf("  1) Opcional\n");
                printf("  2) Baja\n");
                printf("  3) Media\n");
                printf("  4) Alta\n\n");
                printf("> ");
                cin.getline(in, 128);
                fflush(stdin);
                if (!check_str_int(in) || stoi(in) < 0 || stoi(in) > 4) {
                    printf("Introduzca una opcion valida\n");
                    continue;
                }
                priori = (prioridad)(CHAR2INT(*in));
                tarea.prioridad = priori;
            }
            list_tarea_set(&list, list_pos, tarea);

            printf("\nTarea [%d] modificada. Presione ENTER para continuar", list_pos+1);
            getchar();
            continue;
        }
        if (CHAR2INT(*in) == 4 && list_tarea_get_size(list) > 0) {
            printf("Ordenar:\n");
            printf("1) Alfabeticamente\n");
            printf("2) Prioridad\n\n");
            printf("> ");
            cin.getline(in, 128);
            fflush(stdin);

            if (!check_str_int(in)) {
                printf("\nSolo enteros\n");     
                SLEEP(1.0);
                continue;
            }
            if (stoi(in) < 1 || stoi(in) > 2) {
                printf("\nIntroduzca una opcion valida\n");
                SLEEP(1.0);
                continue;
            }

            sort_type sort;
            if (CHAR2INT(*in) == 1) {
                sort = SORT_ALFABETICAMENTE; 
            }
            if (CHAR2INT(*in) == 2) {
                sort = SORT_PRIORIDAD;
            }
            list_tarea_quick_sort(&list, sort, 0, list_tarea_get_size(list)-1);

            printf("Tareas ordenadas %s. Presione ENTER para continuar", sort == SORT_ALFABETICAMENTE ? "alfabeticamente" : "por prioridad");
            getchar();
        }
        if(CHAR2INT(*in) == 5) {
            CLEAR;
            printf("Hecho por Sebastian Ramirez y Angel Vivas\n");
            SLEEP(3.0);
            CLEAR;
            break;
        }
    }

    return 0;
}
