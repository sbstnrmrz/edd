// Participantes
// Sebastian Jose Ramirez Castaneda C.I:31564908
// Angel Miguel Vivas Perez C.I: 30890743
// como bandera del compilador agregar -std=c++11, para poder hacer uso de las funciones stoi, stof

#ifndef DEFS_H
#define DEFS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;

#if __WIN32
#define CLEAR system("cls")
#define SLEEP(secs) {                                   \
    char buf[32] = {0};                                  \
    sprintf(buf, "timeout /t %d /nobreak > nul", secs); \
    system(buf);                                        \
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
    snprintf(str, 32, "sleep %d", secs); \
    system(str);                         \
}
#define DELETE_FILE(file) {           \
    char str[32] = {0};               \
    snprintf(str, 32, "rm %s", file); \
    system(str);                      \
}
#endif

typedef enum {
    ADMINISTRADOR = 1,
    PERSONAL      = 2,
    VENDEDOR      = 3,
} tipo_de_cuenta;

typedef struct {
    char usuario[128];
    char contrasena[128];
    tipo_de_cuenta tipo; 
} cuenta_t;

typedef struct {
    int   id;
    int   id_proveedor;
    int   stock;
    float precio;
    char  descripcion[45];
    int   stock_min;
} producto_t;

typedef struct {
    int id;
    char nombre[45];
    char telefono[30];
} proveedor_t;

typedef struct {
    int id;
    int id_producto;
    int id_factura;
    int cantidad;
} compra_t;

typedef struct {
    int id;
    int id_cliente;
    char fecha[12];
} factura_t;

typedef struct {
    int id;
    char nombre[45];
    char direccion[70];
    char telefono[18];
} cliente_t;

void agregar_cuenta();
void agregar_proveedor();
void agregar_producto();
void agregar_compra();
void agregar_factura(int id_factura, const char *fecha);
void agregar_cliente(int id);

void modificar_proveedor();
void modificar_producto();
void modificar_compra();
void modificar_factura();
void modificar_cliente();

void eliminar_cuenta();
void eliminar_proveedor();
void eliminar_producto();
void eliminar_compra();
void eliminar_cliente();
void eliminar_factura();

int buscar_factura(int id_factura);
int buscar_cliente(int id_cliente);

int consultar_cuentas();
int consultar_proveedores();
int consultar_productos();
int consultar_compras();
int consultar_clientes();
int consultar_facturas();

producto_t buscar_producto(int id_producto);
bool check_id_cliente(int id_cliente);
void modificar_producto_factura(producto_t producto);
void actualizar_archivo();

void cerrar_caja();

void print_info_cuenta(cuenta_t cuenta);
void print_tipo_cuenta(tipo_de_cuenta tipo);
void print_info_proveedor(proveedor_t proveedor);
void print_info_proveedor_tabla(proveedor_t proveedor);
void print_info_producto(producto_t producto);
void print_info_compra(compra_t compra);
void print_info_factura(factura_t factura);
void print_info_cliente(cliente_t cliente);
void print_info_cliente_tabla(cliente_t cliente);
void print_factura(factura_t factura);

#endif
