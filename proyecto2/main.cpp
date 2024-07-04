// Participantes: 
// Sebastian Ramirez C.I:31567908
// Angel Vivas       C.I:30890743

// NOTA:
// - El primer uso del mezcla directa deja sin ordenar el ultimo elemento, a la siguiente ordenacion si lo hace
// - Cada vez que se ordenan alfabeticamente los clientes se modifica el archivo original, se dejo una copia(clientes.def.dat)
//   con los nombres desordenados el cual habria que renombrar a "clientes.dat" por si se quiere hacer el ordenamiento desde cero

#include "defs.h"
#include <cstdio>

void vec_productos_quick_sort(vector<producto_t> *productos, int start, int end) {
    if (end <= start) {
        return;
    }

    char *pivot = productos->at(end).descripcion;
    int i = start-1;
    for (int j = start; j <= end; j++) {
        if (strcasecmp(productos->at(j).descripcion, pivot) < 0) {
            i++;
            swap(productos->at(j), productos->at(i));
        }
    }
    i++;
    swap(productos->at(end), productos->at(i));
    vec_productos_quick_sort(productos, start, i-1);
    vec_productos_quick_sort(productos, i+1, end);
}

void set_binario_clientes(fstream& clientes1, int pos1, fstream& clientes2, int pos2) {
    cliente_t tmp_cliente = {0};

    clientes2.seekg(pos2 * sizeof(cliente_t));
    clientes2.read((char*)&tmp_cliente, sizeof(cliente_t));

    clientes1.seekp(pos1 * sizeof(cliente_t));
    clientes1.write((char*)&tmp_cliente, sizeof(cliente_t));
}

int obtener_tamano_clientes(fstream& clientes) {
    clientes.seekg(0, ios::end);
    int result = (int)clientes.tellg()/sizeof(cliente_t);
    clientes.clear();
    clientes.seekg(0, ios::beg);

    return result;
}

std::string obtener_nombre_clientes(fstream& clientes, int pos) {
    cliente_t cliente = {0};
    clientes.seekg(pos * sizeof(cliente_t));
    clientes.read((char*)&cliente, sizeof(cliente_t));
    clientes.clear();
    clientes.seekg(0, ios::beg);

    return cliente.nombre;
}

std::string obtener_nombre_productos(fstream& productos, int pos) {
    producto_t producto = {0};
    productos.seekg(pos * sizeof(producto_t));
    productos.read((char*)&producto, sizeof(producto_t));
    productos.clear();
    productos.seekg(0, ios::beg);

    return producto.descripcion;
}

void clientes_mezcla(fstream& clientes1, const char* str1, fstream& clientes2, const char* str2, fstream& clientes) {
    int len = obtener_tamano_clientes(clientes);
    int left_len = len/2;
    int right_len = len - left_len;
    int i = 0;
    int l = 0;
    int r = 0;

    while (l < left_len && r < right_len) {
        if (strcasecmp(obtener_nombre_clientes(clientes1, l).c_str(), 
                       obtener_nombre_clientes(clientes2, r).c_str()) < 0) 
        {
            set_binario_clientes(clientes, i, clientes1, l);
            i++;
            l++;
        } else {
            set_binario_clientes(clientes, i, clientes2, r);
            i++;
            r++;
        }
    }
    while (l < left_len) {
        set_binario_clientes(clientes, i, clientes1, l);
        i++;
        l++;
    }
    while (r < right_len) {
        set_binario_clientes(clientes, i, clientes2, r);
        i++;
        r++;
    }
    clientes1.close();
    clientes2.close();
    DELETE_FILE(str1);
    DELETE_FILE(str2);
}

void clientes_mezcla_directa(fstream& clientes, int itr) {
    int len = obtener_tamano_clientes(clientes);
    if (len <= 1) {
        return;
    }

    int mid = len/2;
    fstream clientes1; 
    fstream clientes2; 

    cliente_t cliente = {0};
    char str1[128] = {0};
    char str2[128] = {0};
    snprintf(str1, 128, "clientes%d.dat", itr++);
    snprintf(str2, 128, "clientes%d.dat", itr++);

    clientes1.open(str1, ios::app | ios::binary);
    clientes2.open(str2, ios::app | ios::binary);
    if (!clientes1.is_open() && !clientes2.is_open()) {
        printf("Error clientes 1 y 2\n");
        exit(1);
    }

    int j = 0;
    for (int i = 0; i < len; i++) {
        clientes.read((char*)&cliente, sizeof(cliente_t));
        if (i < mid) {
            clientes1.write((char*)&cliente, sizeof(cliente_t));
        } else {
            clientes2.write((char*)&cliente, sizeof(cliente_t));
            j++;
        }
    }
    clientes1.close();
    clientes2.close();
    clientes1.open(str1, ios::in | ios::out | ios::binary);
    clientes2.open(str2, ios::in | ios::out | ios::binary);

    clientes_mezcla_directa(clientes1, itr);
    clientes_mezcla_directa(clientes2, itr);
    clientes_mezcla(clientes1, str1, clientes2, str2, clientes);
}

void clientes_mezcla_natural(fstream& clientes) {
    int len = obtener_tamano_clientes(clientes);
    fstream clientes1;
    fstream clientes2;

    int i = 0;
    int j = 0;
    int k = 0;
    bool ordenado = false;

    clientes1.open("clientes1.dat", ios::app | ios::binary);
    clientes2.open("clientes2.dat", ios::app | ios::binary);
    while (!ordenado) {
        cliente_t cliente = {0};
        if (strcasecmp(obtener_nombre_clientes(clientes, i).c_str(), 
                       obtener_nombre_clientes(clientes, i+1).c_str()) < 0) 
        {
            clientes.seekg(i * sizeof(cliente_t));
            clientes.read((char*)&cliente, sizeof(cliente_t));
            clientes1.write((char*)&cliente, sizeof(cliente_t));
            i++;
            if (i >= len-1) {
                clientes.seekg(i * sizeof(cliente_t));
                clientes.read((char*)&cliente, sizeof(cliente_t));
                clientes1.write((char*)&cliente, sizeof(cliente_t));
                i = 0;
            } else {
                continue;
            }
        } else {
            clientes.seekg(i * sizeof(cliente_t));
            clientes.read((char*)&cliente, sizeof(cliente_t));
            clientes1.write((char*)&cliente, sizeof(cliente_t));
            i++;
            while (true) {
                if (strcasecmp(obtener_nombre_clientes(clientes, i).c_str(), 
                               obtener_nombre_clientes(clientes, i+1).c_str()) < 0) 
                {
                    clientes.seekg(i * sizeof(cliente_t));
                    clientes.read((char*)&cliente, sizeof(cliente_t));
                    clientes2.write((char*)&cliente, sizeof(cliente_t));
                    i++;
                    if (i >= len-1) {
                        clientes.seekg(i * sizeof(cliente_t));
                        clientes.read((char*)&cliente, sizeof(cliente_t));
                        clientes2.write((char*)&cliente, sizeof(cliente_t));
                        i = 0;
                        break;
                    } 
                } else { 
                    clientes.seekg(i * sizeof(cliente_t));
                    clientes.read((char*)&cliente, sizeof(cliente_t));
                    clientes2.write((char*)&cliente, sizeof(cliente_t));
                    i++;
                    break;
                }
            }
        }
        if (i >= len-1) {
            i = 0;
        }
        int l = 0;
        int r = 0;
        if (k >= len-1) {
            k = 0;
        }

        clientes1.close();
        clientes2.close();
        clientes1.open("clientes1.dat", ios::in | ios::out | ios::binary);
        clientes2.open("clientes2.dat", ios::in | ios::out | ios::binary);

        int len1 = obtener_tamano_clientes(clientes1);
        int len2 = obtener_tamano_clientes(clientes2);
        while (l < len1 && r < len2) {
            if (strcasecmp(obtener_nombre_clientes(clientes1, l).c_str(), 
                           obtener_nombre_clientes(clientes2, r).c_str()) < 0) 
            {
                set_binario_clientes(clientes, k, clientes1, l);
                l++;
                k++;
            } else {
                set_binario_clientes(clientes, k, clientes2, r);
                r++;
                k++;
            }
        }
        while (l < len1) {
            set_binario_clientes(clientes, k, clientes1, l);
            l++;
            k++;
        }
        while (r < len2) {
            set_binario_clientes(clientes, k, clientes2, r);
            r++;
            k++;
        }
        clientes1.close();
        clientes2.close();
        DELETE_FILE("clientes1.dat");
        DELETE_FILE("clientes2.dat");

        int check = 0;
        for (int n = 0; n < len-1; n++) {
            if (strcasecmp(obtener_nombre_clientes(clientes, n).c_str(), 
                           obtener_nombre_clientes(clientes, n+1).c_str()) < 0) 
            {
                check++;  
            } else {
                break;
            }
        }
        if (check >= len-1) {
            ordenado = true;
        }

        clientes1.open("clientes1.dat", ios::app | ios::binary);
        clientes2.open("clientes2.dat", ios::app | ios::binary);
    }
}

void consultar_clientes() {
    cliente_t cliente = {0};
    int cant_clientes = 0;
    fstream f;

    f.open("clientes.dat", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("No existen clientes guardados!\n");
        f.close();
        return;
    }

    printf("____________________________________________________________________________________\n");
    printf("|                                     CLIENTES                                     |\n");
    printf("|__________________________________________________________________________________|\n");
    printf("|     ID     |       Nombre      |     Telefono    |           Direccion           |\n");
    printf("|----------------------------------------------------------------------------------|\n");

    f.read((char*)&cliente, sizeof(cliente_t));
    while(!f.eof()) {
        print_info_cliente(cliente);
        f.read((char*)&cliente, sizeof(cliente_t));

        cant_clientes++;
    }
    printf("------------------------------------------------------------------------------------\n");

    f.close();
}

void consultar_productos(vector<producto_t> productos) {
    printf("________________________________________________________________________\n");
    printf("|                               PRODUCTOS                               |\n");
    printf("|_______________________________________________________________________|\n");
    printf("| ID  | ID Proveedor |   Descripcion   |  Precio | Stock | Stock minimo |\n");
    printf("|-----------------------------------------------------------------------|\n");

    for (producto_t producto : productos) {
        print_info_producto(producto);
    } 
    printf("-------------------------------------------------------------------------\n");
}

void consultar_producto(producto_t producto) {
    printf("________________________________________________________________________\n");
    printf("|                               PRODUCTO                                |\n");
    printf("|_______________________________________________________________________|\n");
    printf("| ID  | ID Proveedor |   Descripcion   |  Precio | Stock | Stock minimo |\n");
    printf("|-----------------------------------------------------------------------|\n");

    print_info_producto(producto);
    printf("-------------------------------------------------------------------------\n");
}

void print_info_cliente(cliente_t cliente) {
    printf("| %-10d | %-17s | %-15s | %-29s |\n", cliente.id,
                                                  cliente.nombre,
                                                  cliente.telefono,
                                                  cliente.direccion);
}

void print_info_producto(producto_t producto) {
    printf("| %-3d | %-12d | %-15s | %-7.2f | %-5d | %-12d |\n", producto.id,
                                                                 producto.id_proveedor,
                                                                 producto.descripcion,
                                                                 producto.precio,
                                                                 producto.stock,
                                                                 producto.stock_min);
}

vector<producto_t> crear_vector_productos() {
    vector<producto_t> productos;
    producto_t producto = {0};
    fstream binario;
    binario.open("productos.dat", ios::in | ios::binary);

    binario.read((char*)&producto, sizeof(producto_t));
    while (!binario.eof()) {
        productos.push_back(producto);
        binario.read((char*)&producto, sizeof(producto_t));
    }

    return productos;
}

int vec_productos_binary_search(vector<producto_t> vec, const char *target) {
    int l = 0;
    int r = vec.size()-1;

    while (l <= r) {
        int m = (l+r)/2;
        const char *str = vec.at(m).descripcion; 
        if (strcasecmp(str, target) < 0) {
            l = (m+1);
        } else if (strcasecmp(str, target) > 0) {
            r = (m-1);
        } else {
            return m;
        } 
    }
    return -1;
}

int clientes_binary_search(fstream& clientes, const char *target) {
    int len = obtener_tamano_clientes(clientes);
    int l = 0;
    int r = len-1;

    while (l <= r) {
        cliente_t cliente = {0};
        int m = (l+r)/2;
        clientes.seekg(m * sizeof(cliente_t));
        clientes.read((char *)&cliente, sizeof(cliente_t));

        if (strcasecmp(cliente.nombre, target) < 0) {
            l = (m+1);
        } else if (strcasecmp(cliente.nombre, target) > 0) {
            r = (m-1);
        } else {
            return m;
        } 
    }
    return -1;
}

int main(int argc, char *argv[]) {
    int in = 0;
    char busqueda[128] = {0};
    float tiempo_sor = 0.0f;
    fstream clientes;

    while (true) {
        vector<producto_t> vec_productos = crear_vector_productos();
        printf("\t\t    Menu\n\n");
        printf("1: Mostrar registros de Productos\n");
        printf("2: Mostrar registros de Clientes\n");
        printf("3: Ordenacion de Productos por Quicksort\n");
        printf("4: Ordenacion de Clientes por Mezcla Directa\n");
        printf("5: Ordenacion de Clientes por Mezcla Natural\n");
        printf("6: Busqueda Binaria de prodcutos\n");
        printf("7: SALIR\n\n");
        printf("> ");
        scanf("%d", &in);
        fflush(stdin);

        if (in == 1) {
            consultar_productos(vec_productos);
        }  
        if (in == 2) {
            consultar_clientes();
        } 
        if (in == 3) {
            clock_t t1 = clock();
            vec_productos_quick_sort(&vec_productos, 0, vec_productos.size()-1);
            clock_t t2 = clock();
            consultar_productos(vec_productos);
            double s = (double)(t2-t1)/CLOCKS_PER_SEC;
            double ms = ((double)(t2-t1)/CLOCKS_PER_SEC) * 1000;
            double ns = ((double)(t2-t1)/CLOCKS_PER_SEC) * 1e+9;
            printf("Tiempo de ordenacion de productos alfabeticamente por Quicksort:\n");
            printf("  Segundos: %lf\n", s);
            printf("  Milisegundos: %lf\n", ms);
            printf("  Nanosegundos: %.0lf\n", ns);
        }
        if (in == 4) {
            clientes.open("clientes.dat", ios::in | ios::out | ios::binary);
            clock_t t1 = clock();
            clientes_mezcla_directa(clientes, 0);
            clock_t t2 = clock();
            clientes_mezcla_directa(clientes, 0);
            consultar_clientes();
            double s = (double)(t2-t1)/CLOCKS_PER_SEC;
            double ms = ((double)(t2-t1)/CLOCKS_PER_SEC) * 1000;
            double ns = ((double)(t2-t1)/CLOCKS_PER_SEC) * 1e+9;
            printf("Tiempo de ordenacion de clientes alfabeticamente por mezcla directa:\n");
            printf("  Segundos: %lf\n", s);
            printf("  Milisegundos: %lf\n", ms);
            printf("  Nanosegundos: %.0lf\n", ns);
        }
        if (in == 5) {
            clientes.open("clientes.dat", ios::in | ios::out | ios::binary);
            clock_t t1 = clock();
            clientes_mezcla_natural(clientes);
            clock_t t2 = clock();
            consultar_clientes();
            double s = (double)(t2-t1)/CLOCKS_PER_SEC;
            double ms = ((double)(t2-t1)/CLOCKS_PER_SEC) * 1000;
            double ns = ((double)(t2-t1)/CLOCKS_PER_SEC) * 1e+9;
            printf("Tiempo de ordenacion de clientes alfabeticamente por mezcla natural:\n");
            printf("  Segundos: %lf\n", s);
            printf("  Milisegundos: %lf\n", ms);
            printf("  Nanosegundos: %.0lf\n", ns);
        }
        if (in == 6) {
            CLEAR;
            vec_productos_quick_sort(&vec_productos, 0, vec_productos.size()-1); 	 
            printf("Indique el nombre del producto: ");
            cin.getline(busqueda, 128);
            int result = vec_productos_binary_search(vec_productos, busqueda);
            if (result >= 0) {
                consultar_producto(vec_productos.at(result));
            } else {
                printf("El producto %s no existe!\n", busqueda);
            }
            printf("\nPresione ENTER para volver al menu");
            fflush(stdin);
            getchar();
            CLEAR;
        }  
        if (in == 7) {
            exit(1);
        } 
        if (in < 1 || in > 7) {
            printf("\nIntroduzca una opcion valida!!\n");
            SLEEP(2.0);
            CLEAR;	
        }
    }

}
