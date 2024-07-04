// Participantes
// Sebastian Jose Ramirez Castaneda C.I:31564908
// Angel Miguel Vivas Perez C.I: 30890743
// como bandera del compilador agregar -std=c++11, para poder hacer uso de las funciones stoi, stof
#include "defs.h"

//asdasdadadasdd


char fecha_caja[128] = {0};
bool caja_abierta = false;

void agregar_cuenta() {
    cuenta_t cuenta = {0};
    // seleccion de tipo de cuenta
    while (true) {
        int in = 0;
        printf("Indique el tipo de cuenta\n");
        printf("  1) Administrador\n");
        printf("  2) Personal\n");
        printf("  3) Vendedor\n\n");
        printf("> ");
        cin >> in;

        if (in < 1 || in > 3) {
            printf("\nIntroduzca una opcion valida!\n\n");
            SLEEP(1);
            CLEAR;
        } else {
            cuenta.tipo = (tipo_de_cuenta)in;
            break;
        }
    }
    fflush(stdin);

    // creacion de usuario
    while (true) {
        char str[128] = {0};
        printf("Introduzca el nombre de la cuenta: ");
        cin.getline(str, 128);

        char *check = strchr(str, ' ');
        if (check != NULL) {
            printf("\nEl usuario no debe contener espacios!\n\n");
            SLEEP(1);
            CLEAR;
            continue;
        } else {
            strcpy(cuenta.usuario, str);
            break;
        }
    }

    // creacion de contrasena
    while (true) {
        char str[128] = {0};
        printf("Introduzca la contrasena de la cuenta: ");
        cin.getline(str, 128);
        fflush(stdin);

        char *check = strchr(str, ' ');
        if (check != NULL) {
            printf("\nLa contrasena no debe contener espacios!\n\n");
            SLEEP(1);
            CLEAR;
            continue;
        } else {
            strcpy(cuenta.contrasena, str);
            break;
        }
    }
    fstream f;
    f.open("cuentas.bin", ios::binary | ios::app);
    f.write((char*)&cuenta, sizeof(cuenta_t));
    f.close();

    printf("\nInformacion de la cuenta\n");
    print_info_cuenta(cuenta);

    printf("Cuenta creada exitosamente!\n");
    printf("Presione ENTER para volver al menu");
    getchar();
    CLEAR;
}

void agregar_proveedor() {
    proveedor_t proveedor = {0};
    int cant_proveedores = 0;

    fstream f;
    f.open("proveedores.bin", ios::binary | ios::in);
    if (!f.is_open()) {
       cant_proveedores = 0; 
    } else {
        f.seekg(0, f.end);
        cant_proveedores = (int)f.tellg()/sizeof(proveedor_t);
    }
    f.close();

    // seleccion de tipo de cuenta
    char str[45] = {0};
    printf("Introduzca el nombre del proveedor: ");
    cin.getline(str, 45);
    strcpy(proveedor.nombre, str);

    fflush(stdin);
    // para obtener la cantidad de proveedores en el archivo
    while (true) {
        char str[30] = {0};
        printf("Introduzca el telefono del proveedor: ");
        cin.getline(str, 30);

        char *check_str = strchr(str, ' ');
        if (check_str != NULL) {
            printf("El numero de telefono no puede contener espacios!\n");
            continue;
        }

        bool check = false;
        for (size_t i = 0; i < strlen(str); i++) {
            if (str[i] < 48 || str[i] > 57) {
                printf("El numero de telefono solo puede contener numeros!\n");
                check = true; 
                break;
            }
        }
        if (check) {
            continue;
        }
        strcpy(proveedor.telefono, str);
        break;
    }
    proveedor.id = cant_proveedores;
    fflush(stdin);

    f.open("proveedores.bin", ios::binary | ios::app);
    f.write((char*)&proveedor, sizeof(proveedor_t));
    f.close();

    print_info_proveedor(proveedor);

    printf("\nProveedor creado exitosamente!\n");
    printf("Presione ENTER para volver al menu");
    getchar();
    CLEAR;
}

void agregar_producto() {
    producto_t producto = {0};
    int cant_productos = 0;

    fstream f;
    f.open("productos.bin", ios::binary | ios::in);
    if (!f.is_open()) {
       cant_productos = 0; 
    } else {
        f.seekg(0, f.end);
        cant_productos = (int)f.tellg()/sizeof(producto_t);
    }
    f.close();

    // seleccion de tipo de cuenta
    producto.id = cant_productos;
    while (true) {
        int in = 0;
        int cant_proveedores = consultar_proveedores()-1;
        if (cant_proveedores < 0) {
            return;
        } 
        printf("Introduzca el id del proveedor: ");
        scanf("%d", &in);
        if (in < 0 || in > cant_proveedores) {
            printf("\nIntroduzca un ID valido!\n\n");
            SLEEP(1);
            CLEAR;
        } else {
            producto.id_proveedor = in;
            break;
        }
    }
    fflush(stdin);

    char str[128] = {0};
    printf("Introduzca el nombre del producto: ");
    cin.getline(str, 128);
    strcpy(producto.descripcion, str);

    fflush(stdin);

    // para obtener la cantidad de proveedores en el archivo
    float precio = 0;
    printf("Introduzca el precio del producto %s: ", producto.descripcion);
    cin >> precio;
    producto.precio = precio;

    fflush(stdin);

    int stock = 0;
    printf("Introduzca el stock de producto %s: ", producto.descripcion);
    cin >> stock;
    producto.stock = stock;

    fflush(stdin);

    while (true) {
        int stock_min = 0;
        printf("Introduzca el stock minimo de producto %s: ", producto.descripcion);
        cin >> stock_min;

        if (stock_min >= producto.stock) {
            printf("El stock minimo no puede ser mayor o igual al stock\n");
            SLEEP(1);
            CLEAR;
        } else if (stock_min < 1) {
            printf("El stock minimo tiene que se mayor o igual a 1\n");
            SLEEP(1);
            CLEAR;
        } else {
            producto.stock_min = stock_min;
            break;
        }
    }
    fflush(stdin);

    f.open("productos.bin", ios::binary | ios::app);
    f.write((char*)&producto, sizeof(producto_t));
    f.close();

    printf("\nProducto anadido exitosamente!\n");
    printf("Presione ENTER para volver al menu");
    getchar();
    CLEAR;
}

void agregar_compra() {
    compra_t compra = {0};
    int cant_compras = 0;

    fstream f;
    f.open("compras.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        cant_compras = 0; 
    } else {
        f.seekg(0, f.end);
        cant_compras = (int)f.tellg()/sizeof(compra_t);
    }
    f.close();

    compra.id_factura = rand()%89999 + 10000;
    while (true) {
        f.open("compras.bin", ios::binary | ios::in);
        f.seekg(0, f.end);
        cant_compras = (int)f.tellg()/sizeof(compra_t);
        f.close();
        while (true) {
            int in = 0;
            int cant_productos = consultar_productos()-1;
            printf("Introduzca la id del producto que desea comprar: ");
            cin >> in;
            fflush(stdin);

            if (in < 0 || in > cant_productos) {
                printf("Introduzca un ID valido!\n");
                SLEEP(1);
                CLEAR;
            } else if (buscar_producto(in).stock <= 0) {
                printf("\nEl producto no tiene suficiente stock!\n\n");
                SLEEP(1);
                CLEAR;
            } else {
                compra.id_producto = in;
                break;
            }
        }

        producto_t producto = buscar_producto(compra.id_producto);
        while (true) {
            printf("Stock actual del producto: %d\n", producto.stock);
            printf("Cantidad de la compra: ");
            cin >> compra.cantidad;
            fflush(stdin);

            if (compra.cantidad <= 0) {
                printf("La cantidad de la compra tiene que ser mayor a 0");
                continue;
            }
            if (compra.cantidad > producto.stock) {
                printf("No hay suficiente stock del producto\n");
                SLEEP(1);
                CLEAR;
            }  else {
                producto.stock -= compra.cantidad;
                break;
            }
        }
        compra.id = cant_compras;
        modificar_producto_factura(producto);
        
        print_info_compra(compra);

        f.open("compras.bin", ios::binary | ios::app);
        f.write((char*)&compra, sizeof(compra_t));
        f.close();

        char option = 0;

        printf("Desea agregar otro producto Si(s) o No(n): ");
        cin >> option;
        fflush(stdin);

        if (option == 'n') {
            break;
        }
    }
    agregar_factura(compra.id_factura, fecha_caja);
}

void agregar_factura(int id_factura, const char *fecha) {
    factura_t factura = {0};
    int cant_facturas = 0;
    fstream f;

    f.open("facturas.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        cant_facturas = 0; 
    } else {
        f.seekg(0, f.end);
        cant_facturas = (int)f.tellg()/sizeof(factura_t);
    }
    f.close();

    factura.id = id_factura;
    int in = 0;
    printf("Introduzca el id del cliente al cual desea facturar (Si el ID no se encuentra, se procede a registrarlo) : ");
    cin >> in;
    fflush(stdin);

    f.open("clientes.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        f.close();
        agregar_cliente(in);
    }
    f.close();

    if (!check_id_cliente(in)) {
        agregar_cliente(in);
    }

    factura.id_cliente = in;
    // fechasda dzcnzxcpnzvz
    strcpy(factura.fecha, fecha);

    f.open("facturas.bin", ios::binary | ios::app);
    f.write((char*)&factura, sizeof(factura_t));
    f.close();

    print_factura(factura);

    printf("\nFactura agregada exitosamente!\n");
    printf("Presione ENTER para volver al menu");
    getchar();
    CLEAR;
}

void agregar_cliente(int id) {
    cliente_t cliente = {0};
    fstream f;

    f.open("clientes.bin", ios::binary | ios::app);
    if (!f.is_open()) {
        printf("Error abriendo el archivo 'clientes.bin'\n");
        return;
    }

    cliente.id = id;
    printf("Introduzca el nombre del cliente: ");
    cin.getline(cliente.nombre, 45);
    fflush(stdin);

    while (true) {
        char str[30] = {0};
        printf("Introduzca el numero de telefono del cliente: ");
        cin.getline(str, 30);
        fflush(stdin);

        char *check_space = strchr(str, ' ');
        if (check_space != NULL) {
            printf("El numero de telefono no puede contener espacios!\n");
            continue;
        }

        bool check_num = false;
        for (size_t i = 0; i < strlen(str); i++) {
            if (str[i] < 48 || str[i] > 57) {
                printf("El numero de telefono solo puede contener numeros!\n");
                check_num = true; 
                break;
            }
        }
        if (check_num) {
            continue;
        }
        strcpy(cliente.telefono, str);
        break;
    }
    printf("Introduzca la direccion del cliente: ");
    cin.getline(cliente.direccion, 70);
    fflush(stdin);

    f.write((char*)&cliente, sizeof(cliente_t));
    f.close();

    printf("Cliente agregado exitosamente!\n");
    printf("Presione ENTER para volver al menu");
    getchar();

}

void modificar_proveedor() {
    proveedor_t proveedor = {0};
    fstream f;

    f.open("proveedores.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("\nNo existen proveedores guardados!\n\n");
        f.close();
        return;
    }
    f.close();

    int cant_proveedores = 0;
    int in = 0;
    while (true) {
        in = 0;
        cant_proveedores = consultar_proveedores()-1;
        printf("Introduzca el ID del proveedor que desea modificar: ");
        cin >> in;
        fflush(stdin);

        if (in < 0 || in > cant_proveedores) {
            printf("\nIntroduzca un ID valido!\n\n");
            SLEEP(1);
            CLEAR;
        } else {
            printf("\nSe procedera a modificar el proveedor %d\n\n", in);
            break;
        }
    }
    proveedor.id = in;

    printf("Introduzca el nuevo nombre del proveedor: ");
    cin >> proveedor.nombre;
    fflush(stdin);

    while (true) {
        char str[30] = {0};
        printf("Introduzca el nuevo telefono del proveedor: ");
        cin.getline(str, 30);
        fflush(stdin);

        char *check_str = strchr(str, ' ');
        if (check_str != NULL) {
            printf("El numero de telefono no puede contener espacios!\n");
            continue;
        }

        bool check = false;
        for (size_t i = 0; i < strlen(str); i++) {
            if (str[i] < 48 || str[i] > 57) {
                printf("\nEl numero de telefono solo puede contener numeros!\n\n");
                check = true; 
                break;
            }
        }
        if (check) {
            continue;
        }
        strcpy(proveedor.telefono, str);
        break;
    }

    f.open("proveedores.bin");
    f.seekp(proveedor.id * sizeof(proveedor_t));
    f.write((char*)&proveedor, sizeof(proveedor_t));
    f.close();

    printf("\nEl proveedor %d, ha sido modificado con exito! Presione ENTER para volver al menu", proveedor.id);
    getchar();
    CLEAR;
}

void modificar_producto() {
    producto_t producto = {0};
    fstream f;

    f.open("productos.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("\nNo existen productos guardados!\n\n");
        f.close();
        return;
    }
    f.close();

    int in = 0;
    while (true) {
        in = 0;
        int cant_productos = consultar_productos()-1;

        printf("Introduzca el ID del producto que desea modificar: ");
        cin >> in;
        fflush(stdin);

        if (in < 0 || in > cant_productos) {
            printf("\nIntroduzca un ID de producto valido!");
            SLEEP(1);
            CLEAR;
        } else {
            printf("\nSe procedera a modificar el producto %d\n\n", in);
            break;
        }
    }
    producto.id = in;

    while (true) {
        in = 0;
        int cant_proveedores = consultar_proveedores()-1;
        if (cant_proveedores <= 0) {
            return;
        } 
        printf("Introduzca el ID del proveedor: ");
        cin >> in;
        fflush(stdin);
        if (in < 0 || in > cant_proveedores) {
            printf("\nIntroduzca un ID valido!\n\n");
            SLEEP(1);
            CLEAR;
        } else {
            producto.id_proveedor = in;
            break;
        }
    }

    char str[128] = {0};
    printf("Introduzca el nombre del producto: ");
    cin.getline(str, 128);
    fflush(stdin);
    strcpy(producto.descripcion, str);

    float precio = 0;
    printf("Introduzca el precio del producto %s: ", producto.descripcion);
    cin >> precio;
    fflush(stdin);
    producto.precio = precio;

    int stock = 0;
    printf("Introduzca el stock de producto %s: ", producto.descripcion);
    cin >> stock;
    fflush(stdin);
    producto.stock = stock;

    while (true) {
        int stock_min = 0;
        printf("Introduzca el stock minimo de producto %s: ", producto.descripcion);
        cin >> stock_min;
        fflush(stdin);

        if (stock_min >= producto.stock) {
            printf("El stock minimo no puede ser mayor o igual al stock\n");
            SLEEP(1);
            CLEAR;
        } else if (stock_min < 1) {
            printf("El stock minimo tiene que se mayor o igual a 1\n");
            SLEEP(1);
            CLEAR;
        } else {
            producto.stock_min = stock_min;
            break;
        }
    }

    f.open("productos.bin");
    f.seekp(sizeof(producto_t) * producto.id);
    f.write((char*)&producto, sizeof(producto_t));
    f.close();

    printf("\nEl producto %d, ha sido modificado con exito! Presione ENTER para volver al menu", producto.id);
    getchar();
    CLEAR;
}

void modificar_compra() {
    compra_t compra = {0};

    fstream f;
    f.open("compras.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("\nNo existen compras guardadas!\n\n");
        f.close();
        return;
    }
    f.close();

    int in = 0;
    while (true) {
        in = 0;
        int cant_compras = consultar_compras()-1;
        printf("Introduzca el ID de la compra que desea modificar");
        cin >> in;
        fflush(stdin);
        
        if (in < 0 || in > cant_compras) {
            printf("\nIntroduzca un ID de compra valido!");
            SLEEP(1);
            CLEAR;
        } else {
            printf("\nSe procedera a modificar la compra %d\n\n", in);
            break;
        }
    
    }
    compra.id = in;
    
    printf("Introduzca la cantidad de la compra: ");
    cin >> compra.cantidad;
    fflush(stdin);
    
    int id_factura = 0;
    printf("Introduzca la ID de factura la compra: ");
    cin >> compra.id_factura;
    fflush(stdin);

    while (true) {
        in = 0;
        int cant_productos = consultar_productos()-1;

        printf("Introduzca el ID del producto que desea modificar: ");
        cin >> in;
        fflush(stdin);

        if (in < 0 || in > cant_productos) {
            printf("\nIntroduzca un ID de producto valido!");
            SLEEP(1);
            CLEAR;
        } else {
            break;
        }
    }
    compra.id_producto = in;
    
    f.open("compras.bin");
    f.seekp(sizeof(compra_t) * compra.id);
    f.write((char*)&compra, sizeof(compra_t));
    f.close();

    printf("\nLa compra %d, ha sido modificado con exito! Presione ENTER para volver al menu", compra.id);
    getchar();
    CLEAR;
}

void modificar_factura() {
    factura_t factura = {0};

    fstream f;
    f.open("compras.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("\nNo existen facturas guardadas!\n\n");
        f.close();
        return;
    }
    f.close();

    int in = 0;
    int check = -1;
    while (true) {
        int id_factura = 0;
        check = -1;
        consultar_facturas();
        printf("Introduzca el ID de la factura que desea modificar: ");
        cin >> id_factura;
        fflush(stdin);

        check = buscar_factura(id_factura);

        if (check < 0) {
            printf("Introduzca un ID de factura valido!\n");
            SLEEP(1);
            CLEAR;
        } else {
            printf("\nSe procedera a modificar la factura %d\n\n", id_factura);
            break;
        }
    }

    printf("Introduzca el nuevo ID de la factura: ");
    cin >> factura.id;
    fflush(stdin);

    printf("Introduzca la nueva ID(Cedula) de cliente de esa factura");
    cin >> factura.id_cliente;
    fflush(stdin);

    printf("Introduzca la nueva fecha de la factura(DD/MM/AA)");
    cin >> factura.fecha;
    fflush(stdin);

    f.open("facturas.bin");
    f.seekp(sizeof(factura_t) * check);
    f.write((char*)&factura, sizeof(factura_t));
    f.close();
}

void modificar_cliente() {
    cliente_t cliente = {0};
    fstream f;

    f.open("clientes.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("\nNo existen clientes guardados!\n\n");
        f.close();
        return;
    }
    f.close();

    int in = 0;
    int check = -1;
    while (true) {
        int id_cliente = 0;
        check = -1;
        consultar_clientes();
        printf("Introduzca el ID del cliente que desea modificar: ");
        cin >> id_cliente;
        fflush(stdin);

        check = buscar_cliente(id_cliente);

        if (check < 0) {
            printf("Introduzca un ID de cliente valido!\n");
            SLEEP(1);
            CLEAR;
        } else {
            printf("\nSe procedera a modificar la informacion del cliente %d\n\n", id_cliente);
            break;
        }
    }

    printf("Introduzca la nueva ID(Cedula) del cliente: ");
    cin >> cliente.id;
    fflush(stdin);

    printf("Introduzca el nuevo nombre del cliente: ");
    cin.getline(cliente.nombre, 45);
    fflush(stdin);

    while (true) {
        char str[30] = {0};
        printf("Introduzca el nuevo numero de telefono del cliente: ");
        cin.getline(str, 30);
        fflush(stdin);

        char *check_space = strchr(str, ' ');
        if (check_space != NULL) {
            printf("El numero de telefono no puede contener espacios!\n");
            continue;
        }

        bool check_num = false;
        for (size_t i = 0; i < strlen(str); i++) {
            if (str[i] < 48 || str[i] > 57) {
                printf("El numero de telefono solo puede contener numeros!\n");
                check_num = true; 
                break;
            }
        }
        if (check_num) {
            continue;
        }
        strcpy(cliente.telefono, str);
        break;
    }

    printf("Introduzca la nueva direccion del cliente: ");
    cin.getline(cliente.direccion, 70);
    fflush(stdin);

    f.open("clientes.bin");
    f.seekp(sizeof(cliente_t) * check);
    f.write((char*)&cliente, sizeof(cliente_t));
    f.close();
}

void modificar_producto_factura(producto_t producto) {
    fstream f;
    f.open("productos.bin");
    f.seekp(producto.id * sizeof(producto_t));
    f.write((char*)&producto, sizeof(producto_t));

    f.close();
}

void eliminar_cuenta() {
    fstream f;
    f.open("cuentas.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("No existen cuentas guardadas!\n");
        return;
    }
    consultar_cuentas();

    vector<cuenta_t> cuentas;
    cuenta_t cuenta = {0};

    f.read((char*)&cuenta, sizeof(cuenta_t));
    while (!f.eof()) {
        // si la posicion del archivo es igual al que se quiere eliminar continue
        cuentas.push_back(cuenta);
        f.read((char*)&cuenta, sizeof(cuenta_t));
    }
    f.close();
    DELETE_FILE("cuentas.bin");

    f.open("cuentas.bin", ios::binary | ios::app);

    int in = 0;
    printf("Introduzca el id del usuario que quiere eliminar\n");
    cin >> in;
    for (size_t i = 0; i < cuentas.size(); i++) {
        if (i == in) {
            continue;
        }
        f.write((char*)&cuentas.at(i), sizeof(cuenta_t));
    }
    f.close();
}

void eliminar_proveedor() {
    fstream f;
    f.open("proveedores.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("No existen proveedores guardados!\n");
        f.close();
        return;
    }

    vector<proveedor_t> proveedores;
    proveedor_t proveedor = {0};

    f.read((char*)&proveedor, sizeof(proveedor_t));
    while (!f.eof()) {
        proveedores.push_back(proveedor);
        f.read((char*)&proveedor, sizeof(proveedor_t));
    }
    f.close();


    int in = 0;
    while (true) {
        in = 0;
        int cant_proveedores = consultar_proveedores()-1;

        printf("Introduzca el ID del proveedor que quiere eliminar: ");
        cin >> in;
        fflush(stdin);

        if (in < 0 || in > cant_proveedores) {
            printf("Introduzca una opcion valida!\n\n");
            SLEEP(1);
            CLEAR;
        } else {
            break;
        }
    }

    DELETE_FILE("proveedores.bin");
    f.open("proveedores.bin", ios::binary | ios::app);
    int cnt = 0;
    for (size_t i = 0; i < proveedores.size(); i++) {
        if (i == in) {
            continue;
        }
        proveedores.at(i).id = cnt;
        f.write((char*)&proveedores.at(i), sizeof(proveedor_t));
        cnt++;
    }
    f.close();
    
    if (proveedores.size()-1 <= 0) {
        DELETE_FILE("proveedores.bin");
    }
}

void eliminar_producto() {
    fstream f;
    f.open("productos.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("No existen productos guardados!\n");
        return;
    }

    vector<producto_t> productos;
    producto_t producto = {0};

    f.read((char*)&producto, sizeof(producto_t));
    while (!f.eof()) {
        productos.push_back(producto);
        f.read((char*)&producto, sizeof(producto_t));
    }
    f.close();

    int in = 0;
    while (true) {
        in = 0;
        int cant_productos = consultar_productos()-1;
        printf("Introduzca el ID del producto que desea eliminar\n");
        cin >> in;
        fflush(stdin);

        if (in < 0 || in > cant_productos) {
            printf("Introduzca una opcion valida!\n\n");
            SLEEP(1);
            CLEAR;
        } else {
            break;
        }
    }

    DELETE_FILE("productos.bin");
    f.open("productos.bin", ios::binary | ios::app);
    int cnt = 0;
    for (size_t i = 0; i < productos.size(); i++) {
        if (i == in) {
            continue;
        }
        productos.at(i).id = cnt;
        f.write((char*)&productos.at(i), sizeof(producto_t));
        cnt++;
    }
    f.close();
    
    if (productos.size()-1 <= 0) {
        DELETE_FILE("productos.bin");
    }

    printf("Producto eliminado con exito!");
    getchar();
    CLEAR;
}

void eliminar_compra() {
    fstream f;
    f.open("compras.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("No existen proveedores guardados!\n");
        return;
    }

    vector<compra_t> compras;
    compra_t compra = {0};

    f.read((char*)&compra, sizeof(compra_t));
    while (!f.eof()) {
        compras.push_back(compra);
        f.read((char*)&compra, sizeof(compra_t));
    }
    f.close();

    int in = 0;
    while (true) {
        in = 0;
        int cant_compras = consultar_compras()-1;
        printf("Introduzca el ID de la compra que quiere eliminar\n");
        cin >> in;
        fflush(stdin);

        if (in < 0 || in > cant_compras) {
            printf("Introduzca una opcion valida!\n\n");
            SLEEP(1);
            CLEAR;
        } else {
            break;
        }
    }

    DELETE_FILE("compras.bin");
    f.open("compras.bin", ios::binary | ios::app);
    int cnt = 0;
    for (size_t i = 0; i < compras.size(); i++) {
        if (i == in) {
            continue;
        }
        compras.at(i).id = cnt;
        f.write((char*)&compras.at(i), sizeof(compra_t));
        cnt++;
    }
    f.close();
    
    if (compras.size()-1 <= 0) {
        DELETE_FILE("compras.bin");
    }
}

void eliminar_factura() {
    fstream f;
    f.open("facturas.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("No existen facturas guardadas!\n");
        return;
    }

    vector<factura_t> facturas;
    factura_t factura = {0};

    f.read((char*)&factura, sizeof(factura_t));
    while (!f.eof()) {
        facturas.push_back(factura);
        f.read((char*)&factura, sizeof(factura_t));
    }
    f.close();

    int in = 0;
    int id_factura = 0;
    while (true) {
        id_factura = 0;
        int cant_facturas = consultar_facturas()-1;
        printf("Introduzca el ID de la factura que desea eliminar: ");
        cin >> id_factura;
        fflush(stdin);

        if (buscar_factura(id_factura) < 0) {
            printf("Introduzca una opcion valida!\n\n");
            SLEEP(1);
            CLEAR;
        } else {
            break;
        }
    }

    DELETE_FILE("facturas.bin");
    f.open("facturas.bin", ios::binary | ios::app);
    for (size_t i = 0; i < facturas.size(); i++) {
        if (facturas.at(i).id == id_factura) {
            continue;
        }
        f.write((char*)&facturas.at(i), sizeof(factura_t));
    }
    f.close();
    
    if (facturas.size()-1 <= 0) {
        DELETE_FILE("facturas.bin");
    }

    printf("\nLa factura %d ha sido eliminada con exito! Presione ENTER para volver el menu", id_factura);
    getchar();
}

void eliminar_cliente() {
    fstream f;
    f.open("clientes.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("No existen clientes guardados!\n");
        return;
    }

    vector<cliente_t> clientes;
    cliente_t cliente = {0};

    f.read((char*)&cliente, sizeof(cliente_t));
    while (!f.eof()) {
        clientes.push_back(cliente);
        f.read((char*)&cliente, sizeof(cliente_t));
    }
    f.close();

    int in = 0;
    int id_cliente = 0;
    while (true) {
        in = 0;
        id_cliente = 0;
        int cant_clientes = consultar_clientes()-1;
        printf("Introduzca el ID de cliente que desea eliminar: ");
        cin >> id_cliente;
        fflush(stdin);

        if (buscar_cliente(id_cliente) < 0) {
            printf("Introduzca un id valido!\n\n");
            SLEEP(1);
            CLEAR;
        } else {
            break;
        }
    }

    DELETE_FILE("clientes.bin");
    f.open("clientes.bin", ios::binary | ios::app);
    for (size_t i = 0; i < clientes.size(); i++) {
        if (clientes.at(i).id == id_cliente) {
            continue;
        }
        f.write((char*)&clientes.at(i), sizeof(cliente_t));
    }
    f.close();
    
    if (clientes.size()-1 <= 0) {
        DELETE_FILE("clientes.bin");
    }

    printf("\nEl cliente %d ha sido eliminado con exito! Presione ENTER para volver el menu", id_cliente);
    getchar();
}

producto_t buscar_producto(int id_producto) {
    producto_t producto = {0};
    fstream f;
    f.open("productos.bin", ios::binary | ios::in);

    f.read((char*)&producto, sizeof(producto_t));
    while (!f.eof()) {
        if (producto.id == id_producto) {
            return producto;
        } else {
            f.read((char*)&producto, sizeof(producto_t));
        }
    }
    f.close();

    return producto;
}

int buscar_factura(int id_factura) {
    factura_t factura = {0};
    fstream f;

    f.open("facturas.bin", ios::binary | ios::in);
    f.read((char*)&factura, sizeof(factura_t));

    int cnt = 0;
    while (!f.eof()) {
        if (factura.id == id_factura) {
            f.close();
            return cnt;
        }
        f.read((char*)&factura, sizeof(factura_t));
        cnt++;
    }
    f.close();

    return -1;
}

int buscar_cliente(int id_cliente) {
    cliente_t cliente = {0};
    fstream f;

    f.open("clientes.bin", ios::binary | ios::in);
    f.read((char*)&cliente, sizeof(cliente_t));

    int cnt = 0;
    while (!f.eof()) {
        if (cliente.id == id_cliente) {
            f.close();
            return cnt;
        }
        f.read((char*)&cliente, sizeof(cliente_t));
        cnt++;
    }
    f.close();

    return -1;
}


bool check_id_cliente(int id_cliente) {
    fstream f;
    cliente_t cliente = {0};
    f.open("clientes.bin", ios::binary | ios::in);

    f.read((char*)&cliente, sizeof(cliente_t));
    while (!f.eof()) {
        if (cliente.id == id_cliente) {
            return true;
        } 
        f.read((char*)&cliente, sizeof(cliente_t));
    }

    return false;
}

void cerrar_caja() {
    fstream f;
    vector<proveedor_t> proveedores;
    vector<producto_t> productos;
    proveedor_t proveedor = {0};
    producto_t producto = {0};

    f.open("proveedores.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("No existen proveedores que listar!\n");
        f.close();
        return;
    }

    f.read((char*)&proveedor, sizeof(proveedor_t));
    while (!f.eof()) {
        proveedores.push_back(proveedor);
        f.read((char*)&proveedor, sizeof(proveedor_t));
    }
    f.close();

    f.open("listado.txt", ios::out);
    if (!f.is_open()) {
        printf("Error al abrir el archivo 'listado.txt'\n");
        return;
    }

    f << "PROVEEDORES" << endl << endl;
    for (int i = 0; i < proveedores.size(); i++) {
        f << "ID: " << proveedores.at(i).id << endl;
        f << "Nombre: " << proveedores.at(i).nombre << endl;
        f << "Telefono: " << proveedores.at(i).telefono << endl << endl;
    } 
    f.close();

    f.open("productos.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("No existen productos que listar!\n");
        f.close();
    }

    f.read((char*)&producto, sizeof(producto_t));
    while (!f.eof()) {
        productos.push_back(producto);
        f.read((char*)&producto, sizeof(producto_t));
    }
    f.close();

    f.open("listado.txt", ios::app);
    f << "PRODUCTOS EN STOCK MINIMO" << endl << endl;
    for (int i = 0; i < productos.size(); i++) {
        if (productos.at(i).stock <= productos.at(i).stock_min) {
            f << "ID Proveedor: " << productos.at(i).id_proveedor << endl;
            f << "ID: " << productos.at(i).id << endl;
            f << "Descripcion: " << productos.at(i).descripcion << endl;
            f << "Precio: " << productos.at(i).precio << endl;
            f << "Stock: " << productos.at(i).stock << endl;
            f << "Stock minimo: " << productos.at(i).stock_min << endl << endl;
        }
    } 
    f.close();

    printf("El listado de proveedores y productos en stock minimo ha sido generado con exito!\n\n");
}

void actualizar_archivo() {
    vector<string> str;
    string in;
    producto_t producto = {0};
    vector<producto_t> productos;
    vector<int> ids;

    fstream f;

    f.open("producto.txt", ios::in);
    getline(f, in);
    while (!f.eof()) {
        str.push_back(in);
        printf("str: %s\n", in.c_str());
        getline(f, in);

    }
    f.close();

    f.open("productos.bin", ios::binary | ios::in | ios::out);
    f.read((char*)&producto, sizeof(producto_t));
    while (!f.eof()) {
        productos.push_back(producto);
        f.read((char*)&producto, sizeof(producto_t));
    }
    f.close();

    f.open("productos.bin", ios::binary | ios::in | ios::out);
    for (int i = 0; i < productos.size(); i++) {
        for (int j = 0; j < str.size(); j++) {
            char *token = strtok((char*)str.at(j).c_str(), " ");
            if (productos.at(i).id == stoi(token)) {
                token = strtok(NULL, " ");
                producto.precio = stof(token);
                token = strtok(NULL, " ");
                producto.stock = stoi(token);
                token = strtok(NULL, " ");
                producto.stock_min = stoi(token);

                f.seekp(sizeof(producto_t) * producto.id);
                f.write((char*)&producto, sizeof(producto_t));
                break;
            }         
        }
    }
    f.close();

    for (int i = 0; i < str.size(); i++) {
        char *token = strtok((char*)str.at(i).c_str(), " ");
        ids.push_back(stoi(token));
    }
    
    int prod = 0;
    for (int i = 0; i < ids.size(); i++) {
        if (productos.at(prod).id != ids.at(i)) {
            f.open("productos.bin", ios::binary | ios::in);
            f.seekg(0, f.end);
            int cant_productos = (int)f.tellg()/sizeof(producto_t);
            f.close();

            // seleccion de tipo de cuenta
            producto.id = cant_productos;
            while (true) {
                int in = 0;
                int cant_proveedores = consultar_proveedores()-1;
                if (cant_proveedores < 0) {
                    return;
                } 
                printf("Introduzca el id del proveedor: ");
                cin >> in;
                if (in < 0 || in > cant_proveedores) {
                    printf("\nIntroduzca un ID valido!\n\n");
                    SLEEP(1);
                    CLEAR;
                } else {
                    producto.id_proveedor = in;
                    break;
                }
            }
            fflush(stdin);

            f.open("producto.txt", ios::in);
            getline(f, in);
            int cnt = 0;
            while (!f.eof()) {
                str.at(cnt) = in;
                getline(f, in);
                cnt++;
            }
            f.close();

            cout << str.at(i) << endl;
            char stri[128] = {0};
            printf("Introduzca el nombre del producto: ");
            cin.getline(stri, 128);
            fflush(stdin);
            strcpy(producto.descripcion, stri);

            char *token = strtok((char*)str.at(i).c_str(), " ");
            token = strtok(NULL, " ");
            producto.precio = stof(token);
            token = strtok(NULL, " ");
            producto.stock = stoi(token);
            token = strtok(NULL, " ");
            producto.stock_min = stoi(token);

            f.open("productos.bin", ios::binary | ios::app);
            f.write((char*)&producto, sizeof(producto_t));

            printf("\nProducto anadido exitosamente!\n");
            break;
        }
        if (prod < productos.size()-1) {
            prod++; 
        }
    }

    f.close();
}

int consultar_cuentas() {
    cuenta_t cuenta = {0}; 
    int cant_cuentas = 0;
    fstream f;

    f.open("cuentas.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("No existen cuentas guardadas\n");
        return -1;
    }

    f.read((char*)&cuenta, sizeof(cuenta_t));
    while (!f.eof()) {
        print_info_cuenta(cuenta);
        f.read((char*)&cuenta, sizeof(cuenta_t));
        cant_cuentas++;
    }
    f.close();

    return cant_cuentas;
}

int consultar_proveedores() {
    proveedor_t proveedor = {0}; 
    int cant_proveedores = 0;
    fstream f;

    f.open("proveedores.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("No existen proveedores guardados\n");
        return -1;
    }

    f.read((char*)&proveedor, sizeof(proveedor_t));
    while (!f.eof()) {
        print_info_proveedor(proveedor);
        f.read((char*)&proveedor, sizeof(proveedor_t));
        cant_proveedores++;
    }
    f.close();

    return cant_proveedores;
}

void consultar_proveedores_tabla() {
    proveedor_t proveedor = {0}; 
    fstream f;

    f.open("proveedores.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("No existen proveedores guardados\n");
        return;
    }

    f.read((char*)&proveedor, sizeof(proveedor_t));
    printf("___________________________________________\n");
    printf("|                PROVEEDORES              |\n");
    printf("|_________________________________________|\n");
    printf("| ID  |     Nombre      |     Telefono    |\n");
    printf("|-----------------------------------------|\n");

    while (!f.eof()) {
        print_info_proveedor_tabla(proveedor);
        f.read((char*)&proveedor, sizeof(proveedor_t));
    }
    printf("-------------------------------------------\n");
    f.close();

    printf("\nPresione ENTER para volver al menu!");
    getchar();
    CLEAR;
}

int consultar_productos() {
    producto_t producto = {0}; 
    int cant_productos = 0;
    fstream f;

    f.open("productos.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("No existen productos guardados\n");
        return -1;
    }

    printf("____________________________________________________________________\n");
    printf("|                          PRODUCTOS                               |\n");
    printf("|__________________________________________________________________|\n");
    printf("| ID  | ID Proveedor | Descripcion | Precio | Stock | Stock minimo |\n");
    printf("|------------------------------------------------------------------|\n");

    f.read((char*)&producto, sizeof(producto_t));
    while (!f.eof()) {
        print_info_producto(producto);
        f.read((char*)&producto, sizeof(producto_t));
        cant_productos++;
    }
    printf("--------------------------------------------------------------------\n");
    f.close();

    return cant_productos;
}

int consultar_compras() {
    compra_t compra = {0};
    int cant_compras = 0;
    fstream f;

    f.open("compras.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("No existen compras\n");
        return -1;
    }

    f.read((char*)&compra, sizeof(compra_t));
    while(!f.eof()) {
        print_info_compra(compra);
        f.read((char*)&compra, sizeof(compra_t));
        cant_compras++;
    }
    f.close();

    return cant_compras;
}

int consultar_facturas() {
    factura_t factura = {0};
    int cant_facturas = 0;
    fstream f;

    f.open("facturas.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("No existen facturas guardadas!\n");
        return -1;
    }

    f.read((char*)&factura, sizeof(factura_t));
    while(!f.eof()) {
        print_info_factura(factura);
        f.read((char*)&factura, sizeof(factura_t));
        cant_facturas++;
    }
    f.close();

    return cant_facturas;
}

int consultar_clientes() {
    cliente_t cliente = {0};
    int cant_clientes = 0;
    fstream f;

    f.open("clientes.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("No existen clientes guardados!\n");
        f.close();
        return -1;
    }

    f.read((char*)&cliente, sizeof(cliente_t));
    while(!f.eof()) {
        print_info_cliente(cliente);
        f.read((char*)&cliente, sizeof(cliente_t));
        cant_clientes++;
    }
    f.close();

    return cant_clientes;
}

void consultar_clientes_tabla() {
    cliente_t cliente = {0};
    int cant_clientes = 0;
    fstream f;

    f.open("clientes.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("No existen clientes guardados!\n");
        f.close();
        return;
    }



    printf("_________________________________________________________________________\n");
    printf("|                            CLIENTES                                   |\n");
    printf("|_______________________________________________________________________|\n");
    printf("|     ID     |     Nombre      |     Telefono    |      Direccion       |\n");
    printf("|-----------------------------------------------------------------------|\n");

    f.read((char*)&cliente, sizeof(cliente_t));
    while(!f.eof()) {
        print_info_cliente_tabla(cliente);
        f.read((char*)&cliente, sizeof(cliente_t));
        cant_clientes++;
    }
    printf("-------------------------------------------------------------------------\n");

    f.close();
}

void print_info_cuenta(cuenta_t cuenta) {
    printf("  Tipo de cuenta: ");
    print_tipo_cuenta(cuenta.tipo);
    printf("  Usuario: %s\n", cuenta.usuario);
    printf("  Contrasena: %s\n\n", cuenta.contrasena);
}

void print_tipo_cuenta(tipo_de_cuenta tipo) {
    switch (tipo) {
        case ADMINISTRADOR:
            printf("Administrador\n");
            break;
        case PERSONAL:
            printf("Personal\n");
            break;
        case VENDEDOR:
            printf("Vendedor\n");
            break;
        default:
            break;
    }
}

void print_info_proveedor(proveedor_t proveedor) {
    printf("ID: %d\n", proveedor.id);
    printf("Nombre: %s\n", proveedor.nombre);
    printf("Telefono: %s\n\n", proveedor.telefono);
}

void print_info_proveedor_tabla(proveedor_t proveedor) {
    printf("| %-3d | %-15s | %-15s |\n", proveedor.id,
                                         proveedor.nombre,
                                         proveedor.telefono);

}

void print_info_producto(producto_t producto) {
    printf("| %-3d | %-12d | %-11s | %-6.2f | %-5d | %-12d |\n", producto.id,
                                                                 producto.id_proveedor,
                                                                 producto.descripcion,
                                                                 producto.precio,
                                                                 producto.stock,
                                                                 producto.stock_min);
}



void print_info_compra(compra_t compra) {
    printf("ID Compra: %d \n", compra.id);
    printf("ID Factura: %d \n", compra.id_factura);
    printf("ID Producto: %d \n", compra.id_producto);
    printf("Stock retirado: %d \n\n", compra.cantidad);
}

void print_info_factura(factura_t factura) {
    printf("ID Factura: %d\n", factura.id);
    printf("Cedula del cliente: %d\n", factura.id_cliente);
    printf("Fecha de facturacion: %s\n\n", factura.fecha);
}

void print_info_cliente(cliente_t cliente) {
    printf("Nombre: %s\n", cliente.nombre);
    printf("Cedula: %d\n", cliente.id);
    printf("Telefono: %s\n", cliente.telefono);
    printf("Direccion: %s\n\n", cliente.direccion);
}


void print_info_cliente_tabla(cliente_t cliente) {
    printf("| %-10d | %-15s | %-15s | %-20s |\n", cliente.id,
                                               cliente.nombre,
                                               cliente.telefono,
                                               cliente.direccion);

}

void print_factura(factura_t factura) {
    printf("___________________\n");
    printf("|     FACTURA     |\n");
    printf("|-----------------|\n");
    printf("| ID     %8d |\n", factura.id);
    printf("| Cedula %8d |\n", factura.id_cliente);
    printf("| Fecha  %8s |\n", factura.fecha);
    printf("-------------------\n\n");
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    cuenta_t def_admin = {"admin", "admin", ADMINISTRADOR };
    cuenta_t cuenta = {0};

    fstream f;

    int check = -1;
    // 0 si la contrasena y usuario son correctos
    // -1 si el usuario no existe
    // -2 si la contrasena no es correcta
    while (true) {
        char usuario[128] = {0};
        char contrasena[128] = {0};

        printf("Usuario: ");
        cin.getline(usuario, 128);
        fflush(stdin);

        printf("Contrasena: ");
        cin.getline(contrasena, 128);
        fflush(stdin);

        // existe una cuenta de administrador por defecto en el caso de que no existan cuentas registradas 
        if (!strcasecmp(def_admin.usuario, usuario)) {
            if (!strcasecmp(def_admin.contrasena, contrasena)) {
                printf("\nLogueado con cuenta de tipo administrador\n");
                SLEEP(1);
                cuenta = def_admin;
                break;
            }
        }

        f.open("cuentas.bin", ios::binary | ios::in);
        if (f.is_open()) {
            f.read((char*)&cuenta, sizeof(cuenta_t));
            while (!f.eof()) {
                if (!strcasecmp(cuenta.usuario, usuario)) {
                    if (!strcasecmp(cuenta.contrasena, contrasena)) {
                        check = 0;
                        break;
                    } else {
                        check = -2; 
                        break;
                    }
                }
                check = -1;
                f.read((char*)&cuenta, sizeof(cuenta_t));
            }
            f.close();
        }
        if (check == 0) {
            switch (cuenta.tipo) {
            case ADMINISTRADOR:
                printf("\nLogueado con cuenta de tipo administrador\n");
                break;
            case PERSONAL:
                printf("\nLogueado con cuenta de tipo personal\n");
                break;
            case VENDEDOR:
                printf("\nLogueado con cuenta de tipo vendedor\n");
                break;
            default:
                break;
            }
            break;
        }
        if (check == -1) {
            printf("\nEl usuario no existe!\n\n");
            continue;            
        }
        if (check == -2) {
            printf("\nLa contrasena es incorrecta\n\n");
            continue;            
        }
    }
    f.close();

    SLEEP(1);
    CLEAR;
    if (cuenta.tipo == ADMINISTRADOR) {
        while (true) {
            int in = 0;
            printf("MENU ADMINISTRADOR\n");
            printf("  1)  Crear cuenta\n");
            printf("  2)  Agregar proveedor\n");
            printf("  3)  Agregar producto\n");
            printf("  4)  Agregar compra\n");
            printf("  5)  Agregar cliente\n");
            printf("  6)  Modificar proveedor\n");
            printf("  7)  Modificar producto\n");
            printf("  8)  Modificar compra\n");
            printf("  9)  Modificar factura\n");
            printf("  10) Modificar cliente\n");
            printf("  11) Eliminar proveedor\n");
            printf("  12) Eliminar producto\n");
            printf("  13) Eliminar compra\n");
            printf("  14) Eliminar factura\n");
            printf("  15) Eliminar cliente\n");
            printf("  16) Consultar proveedores\n");
            printf("  17) Consultar productos\n");
            printf("  18) Consultar compras\n");
            printf("  19) Consultar facturas\n");
            printf("  20) Consultar clientes\n");
            printf("  21) Salir del programa\n\n");
            printf("> ");
            cin >> in;
            fflush(stdin);

            switch(in) {
            case 1:
                agregar_cuenta();
                break;
            case 2:
                agregar_proveedor();
                break;
            case 3:
                agregar_producto();
                break;
            case 4:
                agregar_compra();
                break;
            case 5:
                printf("Introduzca el numero de cedula del cliente: ");
                cin >> in;
                fflush(stdin);
                agregar_cliente(in);
                break;
            case 6:
                modificar_proveedor();
                break;
            case 7:
                modificar_producto();
                break;
            case 8:
                modificar_compra();
                break;
            case 9:
                modificar_factura();
                break;
            case 10:
                modificar_cliente();
                break;
            case 11:
                eliminar_proveedor();
                break;
            case 12:
                eliminar_producto();
                break;
            case 13:
                eliminar_compra();
                break;
            case 14:
                eliminar_factura();
                break;
            case 15:
                eliminar_cliente();
                break;
            case 16:
                consultar_proveedores_tabla();
                break;
            case 17:
                CLEAR;
                consultar_productos();
                printf("\nPresione ENTER para volver al menu");
                getchar();
                CLEAR;
                break;
            case 18:
                CLEAR;
                consultar_compras();
                printf("\nPresione ENTER para volver al menu");
                getchar();
                CLEAR;
                break;
            case 19:
                CLEAR;
                consultar_facturas();
                printf("\nPresione ENTER para volver al menu");
                getchar();
                CLEAR;
                break;
            case 20:
                CLEAR;
                consultar_clientes_tabla();
                printf("\nPresione ENTER para volver al menu");
                getchar();
                CLEAR;
                break;
            case 21:
                exit(1);
                break;
            default:
                printf("\nIntroduzca una opcion valida!\n\n");
                SLEEP(1);
                CLEAR;
                break;
            }
        }
    }
    if (cuenta.tipo == PERSONAL) {
        while (true) {
            int in = 0;
            printf("1) Actualizar informacion de productos desde txt\n");
            printf("2) Salir del programa\n");
            printf("> ");
            cin >> in;
            fflush(stdin);

            if (in == 1) {
                actualizar_archivo();
            }
            if (in == 2) {
                break;
            }
            if (in < 1 || in > 2) {
                printf("\nIntroduzca una opcion valida!\n");
                SLEEP(1);
                CLEAR;
            }
        }
    }
    if (cuenta.tipo == VENDEDOR) {
        if (!caja_abierta) {
            while (true) {
                int in = 0;
                printf("1) Aperturar caja\n");
                printf("2) Salir del programa\n");
                printf("> ");
                cin >> in;
                fflush(stdin);

                if (in == 1) {
                    char fecha[128] = {0};
                    printf("Introduzca la fecha de apertura (DD/MM/AA): ");
                    cin >> fecha;
                    fflush(stdin);
                    strcpy(fecha_caja, fecha);

                    while (true) {
                        printf("Fecha: %s\n", fecha_caja);
                        printf("1) Procesar compra\n");
                        printf("2) Cerrar caja\n");
                        printf("> ");
                        cin >> in;
                        fflush(stdin);

                        if (in == 1) {
                            agregar_compra();
                        }
                        if (in == 2) {
                            cerrar_caja();
                            break;
                        }
                        if (in < 1 || in > 2) {
                            printf("\nIntroduzca una opcion valida!\n\n");
                            SLEEP(1);
                            CLEAR;
                        }
                    } 
                    continue;
                }
                if (in == 2) {
                    break;
                }
                if (in < 1 || in > 2) {
                    printf("\nIntroduzca una opcion valida!\n\n");
                    SLEEP(1);
                    CLEAR;
                }
            }
        }
    }

    return EXIT_SUCCESS;
}
