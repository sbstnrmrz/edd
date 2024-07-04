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

void cola_enqueue(cola_t *cola, int data) {
    cola->data = (int*)realloc(cola->data, sizeof(int) * (cola->size+1));
    cola->data[cola->size] = data;
    cola->size++;
}

void cola_dequeue(cola_t *cola) {
    if (cola->size < 1) {
        printf("La cola no tiene elementos que eliminar\n"); 
        return;
    }

    for (int i = 0; i < cola->size-1; i++) {
        cola->data[i] = cola->data[i+1];
    }
    cola->data = (int*)realloc(cola->data, sizeof(int) * (cola->size-1));
    cola->size--;

    if (cola->size < 1) {
        cola->data = NULL;
    }
}


int cola_front(cola_t cola) {
    return cola.data[0];
}

int cola_rear(cola_t cola) {
    return cola.data[cola.size-1];
}

bool cola_is_empty(cola_t cola) {
    if (cola_size(cola) < 1) {
        return true;
    }
    return false;
}

int cola_size(cola_t cola) {
    return cola.size;
}

bool pila_is_empty(pila_t pila) {
    if (pila_size(pila) < 1) {
        return true;
    }
    return false;
}

int pila_size(pila_t pila) {
    return pila.size;
}

void pila_push(pila_t *pila, int data) {
    pila->data = (int*)realloc(pila->data, sizeof(int) * (pila->size+1));
    pila->data[pila->size] = data;
    pila->size++;
}

void pila_pop(pila_t *pila) {
    if (pila->size < 1) {
        printf("La cola no tiene elementos que eliminar\n"); 
        return;
    }
    pila->data = (int*)realloc(pila->data, sizeof(pila->size-1));
    pila->size--;
}

int pila_top(pila_t pila) {
    return pila.data[pila.size-1];
}

void print_pila(pila_t pila) {
    for (int i = 0; i < 2; i++) {
        printf("pila[%d]: %d\n", i, pila.data[i]);
    } 
    printf("\n");
}

int main(int argc, char *argv[]) {
    char in = 0;
    char taq1[3] = {0};
    char taq2[3] = {0};
    char taq3[3] = {0};
    char str3[128] = {0};
	cola_t cola = {0};
	cola.size = 0;
    pila_t pila = {0};
    pila_t taquilla1 = {0};
    pila_t taquilla2 = {0};
    pila_t taquilla3 = {0};

    while (true) {
    	if(cola.size < 1) {
				printf("\t\tNo hay clientes en cola");
		}else{
			printf("Cola Virtual: ");
	    	for(int i =0; i < cola.size; i++) {
				if (cola.data[i] < 100) {
	                snprintf(str3, 4, "0%d", cola.data[i]);
	            } else {
	                snprintf(str3, 4, "%d", cola.data[i]);
	            }
	            printf("%s  ",str3);
			}
	    }
    	
    	
		printf("\n ______________________________________________________");
		printf("\n|                      Atendiendo                      |\n");
		printf("|                                                      |\n");
		printf("| Taquilla 1:%3s     Taquilla 2:%3s     Taquilla 3:%3s |\n",taq1,taq2,taq3);
		printf("|______________________________________________________|");
		
        printf("\n\n\t\t    Banco  El Tesoro\n\n");
        printf("\t Ingrese una de las siguientes opciones\n\n");
        printf("A: Agregar persona a la cola virtual\n");
        printf("1: Atender al siguiente de la cola en Taquilla 1\n");
        printf("2: Atender al siguiente de la cola en Taquilla 2\n");
        printf("3: Atender al siguiente de la cola en Taquilla 3\n");
        printf("4: Salir del programa\n\n");
        printf(">");
        scanf(" %c", &in);
        fflush(stdin);
        
        if (in == 'A' || in == 'a') {
            CLEAR;
            char cedula[128] = {0};
            printf("Ingrese su numero de cedula: ");
            scanf("%s", cedula);
            fflush(stdin);
            CLEAR;

            if (!check_str_int(cedula) || strlen(cedula)-1 <= 3) {
                printf("Debe ingresar solo numeros o tener minimo 3 digitos\n");
                SLEEP(2.0);
                CLEAR;
                continue;
            }

            int len = strlen(cedula);
            int dig_str = 0;
            bool check = false;
            int cnt = 0;
            bool reversa = false;
            for (int i = 0; i < cola_size(cola); i++) {
                char str[3] = {0};
                strncpy(str, cedula + (len-3), 3);
                str[3] = '\0';
                dig_str = stoi(str);

                if (dig_str == cola.data[i]) {
                    char str2[1] = {0};
                    strncpy(str2, cedula+cnt, 1);
                    str2[1] = '\0';
                    len--;
                    cnt++;
                    i = -1;
                    check = false;

                    pila_push(&pila, stoi(str2));
                    if (len-3 < 0) {
                        if (reversa) {
                            cedula[strlen(cedula)-1] = '0'; 
                        }
                        len = strlen(cedula);
                        cnt = 0;
                        strncpy(str2, cedula + (len-2), 1);
                        str2[1] = '\0';
                        pila_push(&pila, stoi(str2));
                        strncpy(str2, cedula + (len-1), 1);
                        str2[1] = '\0';
                        pila_push(&pila, stoi(str2));

                        for (int k = 0; k < len; k++) {
                            cedula[k] = pila_top(pila) + '0';
                            pila_pop(&pila);
                        }
                        i = -1;
                        reversa = true;
                    }
                } else {
                    check = true;
                }
            }
            if (cola.size < 1) {
            	char str[3] = {0};
                strncpy(str, cedula + (len-3), 3);
                str[3] = '\0';
                dig_str = stoi(str);
                cola_enqueue(&cola, dig_str);
			}
            if (check) {
                cola_enqueue(&cola, dig_str);                

                while (pila.size > 0) {
                    pila_pop(&pila);
                } 
            }
            continue;
        }
        if (in - '0' >= 1 && in - '0' <= 3 && cola_size(cola) > 0) {
            int codigo = cola_front(cola);
            printf("\nEl cliente con codigo %d se dirige a la taquilla %c\n\n", codigo, in);
            switch (in - '0') {
            case 1:
            	if (cola.data[0] < 100) {
                	snprintf(str3, 4, "0%d", cola.data[0]);
                	strcpy(taq1, str3);
	            }else{
	            	snprintf(str3, 4, "%d", cola.data[0]);
	                strcpy(taq1, str3);
				}
            	cola_dequeue(&cola);
            	CLEAR;
            	break;
            case 2:
            	if (cola.data[0] < 100) {
	                snprintf(str3, 4, "0%d", cola.data[0]);
	                strcpy(taq2, str3);
	            }else{
	            	snprintf(str3, 4, "%d", cola.data[0]);
	                strcpy(taq2, str3);
				}
            	cola_dequeue(&cola);
            	CLEAR;
				break;
            case 3:
	           	if (cola.data[0] < 100) {
	                snprintf(str3, 4, "0%d", cola.data[0]);
	                strcpy(taq3, str3);
	            }else{
	            	snprintf(str3, 4, "%d", cola.data[0]);
	                strcpy(taq3, str3);
				}
            	cola_dequeue(&cola);
            	CLEAR;
				break;
				break;
			}
        }

        if (in - '0' == 4) {
        	CLEAR;
        	printf("Hecho por Sebastian Ramirez y Angel Vivas");
        	SLEEP(2.0);
            break;
        }
        if (in - '0' < 1 || in - '0' > 4) {
            printf("Ingrese una opcion valida!!\n");
            SLEEP(2.0);
            CLEAR;
        }
    }
    return 0;
}
