#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <cstdlib>

using namespace std;

int stock1 = 100, stock2 = 100, stock3 = 100, stock4 = 100, stock5 = 100;
int stock6 = 100, stock7 = 100, stock8 = 100, stock9 = 100, stock10 = 100;

int vendidas1 = 0, vendidas2 = 0, vendidas3 = 0, vendidas4 = 0, vendidas5 = 0;
int vendidas6 = 0, vendidas7 = 0, vendidas8 = 0, vendidas9 = 0, vendidas10 = 0;

int carrito1 = 0, carrito2 = 0, carrito3 = 0, carrito4 = 0, carrito5 = 0;
int carrito6 = 0, carrito7 = 0, carrito8 = 0, carrito9 = 0, carrito10 = 0;

string nombre_producto(int k) {
    switch (k) {
        case 1:  return "tomate";
        case 2:  return "repollo";
        case 3:  return "papas";
        case 4:  return "carne molida";
        case 5:  return "carne de cerdo";
        case 6:  return "cerdo";
        case 7:  return "cerveza nacional";
        case 8:  return "cerveza importada";
        case 9:  return "vino";
        case 10: return "vodka";
        default: return "";
    }
}

double precio_producto(int k) {
    switch (k) {
        case 1:  return 10;
        case 2:  return 15;
        case 3:  return 12;
        case 4:  return 20;
        case 5:  return 18;
        case 6:  return 22;
        case 7:  return 50;
        case 8:  return 80;
        case 9:  return 200;
        case 10: return 100;
        default: return 0;
    }
}

int obtener_stock(int k) {
    switch (k) {
        case 1:  return stock1;
        case 2:  return stock2;
        case 3:  return stock3;
        case 4:  return stock4;
        case 5:  return stock5;
        case 6:  return stock6;
        case 7:  return stock7;
        case 8:  return stock8;
        case 9:  return stock9;
        case 10: return stock10;
        default: return 0;
    }
}

void sumar_stock(int k, int cantidad) {
    switch (k) {
        case 1:  stock1 += cantidad;  break;
        case 2:  stock2 += cantidad;  break;
        case 3:  stock3 += cantidad;  break;
        case 4:  stock4 += cantidad;  break;
        case 5:  stock5 += cantidad;  break;
        case 6:  stock6 += cantidad;  break;
        case 7:  stock7 += cantidad;  break;
        case 8:  stock8 += cantidad;  break;
        case 9:  stock9 += cantidad;  break;
        case 10: stock10 += cantidad; break;
    }
}

int obtener_vendidas(int k) {
    switch (k) {
        case 1:  return vendidas1;
        case 2:  return vendidas2;
        case 3:  return vendidas3;
        case 4:  return vendidas4;
        case 5:  return vendidas5;
        case 6:  return vendidas6;
        case 7:  return vendidas7;
        case 8:  return vendidas8;
        case 9:  return vendidas9;
        case 10: return vendidas10;
        default: return 0;
    }
}

void sumar_vendidas(int k, int cantidad) {
    switch (k) {
        case 1:  vendidas1 += cantidad;  break;
        case 2:  vendidas2 += cantidad;  break;
        case 3:  vendidas3 += cantidad;  break;
        case 4:  vendidas4 += cantidad;  break;
        case 5:  vendidas5 += cantidad;  break;
        case 6:  vendidas6 += cantidad;  break;
        case 7:  vendidas7 += cantidad;  break;
        case 8:  vendidas8 += cantidad;  break;
        case 9:  vendidas9 += cantidad;  break;
        case 10: vendidas10 += cantidad; break;
    }
}

int obtener_carrito(int k) {
    switch (k) {
        case 1:  return carrito1;
        case 2:  return carrito2;
        case 3:  return carrito3;
        case 4:  return carrito4;
        case 5:  return carrito5;
        case 6:  return carrito6;
        case 7:  return carrito7;
        case 8:  return carrito8;
        case 9:  return carrito9;
        case 10: return carrito10;
        default: return 0;
    }
}

void sumar_carrito(int k, int cantidad) {
    switch (k) {
        case 1:  carrito1 += cantidad;  break;
        case 2:  carrito2 += cantidad;  break;
        case 3:  carrito3 += cantidad;  break;
        case 4:  carrito4 += cantidad;  break;
        case 5:  carrito5 += cantidad;  break;
        case 6:  carrito6 += cantidad;  break;
        case 7:  carrito7 += cantidad;  break;
        case 8:  carrito8 += cantidad;  break;
        case 9:  carrito9 += cantidad;  break;
        case 10: carrito10 += cantidad; break;
    }
}

void limpiar_carrito() {
    carrito1 = carrito2 = carrito3 = carrito4 = carrito5 = 0;
    carrito6 = carrito7 = carrito8 = carrito9 = carrito10 = 0;
}

void confirmar_compra() {
    int i, cantidad;
    for (i = 1; i <= 10; i++) {
        cantidad = obtener_carrito(i);
        sumar_stock(i, -cantidad);
        sumar_vendidas(i, cantidad);
    }
    limpiar_carrito();
}

int leer_entero(string mensaje, int minimo, int maximo) {
    int dato;
    bool correcto = false;

    while (!correcto) {
        cout << mensaje;
        cin >> dato;
        if (cin.eof()) exit(0);
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "ERROR: Dato incorrecto." << endl;
        } else {
            cin.ignore(1000, '\n');
            if (dato < minimo || dato > maximo) {
                cout << "ERROR: Dato incorrecto (opciones del " << minimo << " al " << maximo << ")." << endl;
            } else {
                correcto = true;
            }
        }
    }
    return dato;
}

int comprar_producto(int k, int &unidades) {
    int cantidad, disponible;

    cout << "Usted ha seleccionado " << nombre_producto(k) << "." << endl;
    cout << "Precio: L " << precio_producto(k) << endl;

    disponible = obtener_stock(k) - obtener_carrito(k);
    if (disponible <= 0) {
        cout << "ERROR: No hay inventario disponible de este producto." << endl;
        return 0;
    }

    cantidad = leer_entero("Ingrese la cantidad que desea comprar (0 para cancelar, maximo " + to_string(disponible) + "): ", 0, disponible);
    if (cantidad > 0) {
        sumar_carrito(k, cantidad);
        unidades = unidades + cantidad;
        cout << "Total a pagar: L " << cantidad * precio_producto(k) << endl;
    }
    return cantidad;
}

void menu_verduras(double &sub_verduras, int &unidades) {
    int tipo_producto, agregar_producto, cantidad, k;

    do {
        cout << "Usted ha seleccionado verduras." << endl;
        cout << " ingrese tipo de producto que desea comprar: " << endl;
        cout << "1. tomate      " << endl;
        cout << "2. repollo     " << endl;
        cout << "3. papas       " << endl;
        tipo_producto = leer_entero("", 1, 3);
        k = tipo_producto;

        cantidad = comprar_producto(k, unidades);
        sub_verduras = sub_verduras + cantidad * precio_producto(k);

        cout << " desea agregar otro producto menu verduras? " << endl;
        cout << "1. si " << endl;
        cout << "2. no " << endl;
        agregar_producto = leer_entero("", 1, 2);
    } while (agregar_producto == 1);
}

void menu_carnes(double &sub_carnes, double &desc_segundo_carne, int &lineas_carnes, int &unidades) {
    int tipo_producto, agregar_producto, cantidad, k;
    double monto;

    do {
        cout << "Usted ha seleccionado carnes." << endl;
        cout << " ingrese tipo de producto que desea comprar: " << endl;
        cout << "1. carne molida         " << endl;
        cout << "2. carne de cerdo  " << endl;
        cout << "3. cerdo       " << endl;
        tipo_producto = leer_entero("", 1, 3);
        k = tipo_producto + 3;

        cantidad = comprar_producto(k, unidades);
        if (cantidad > 0) {
            monto = cantidad * precio_producto(k);
            sub_carnes = sub_carnes + monto;
            lineas_carnes = lineas_carnes + 1;
            if (lineas_carnes == 2) desc_segundo_carne = desc_segundo_carne + monto * 0.50;
        }

        cout << " desea agregar otro producto menu carnes? " << endl;
        cout << "1. si " << endl;
        cout << "2. no " << endl;
        agregar_producto = leer_entero("", 1, 2);
    } while (agregar_producto == 1);
}

void menu_licores(double &sub_licores, double &desc_sixpack, int &unidades) {
    int tipo_producto, agregar_producto, cantidad, edad, k;

    cout << "Usted ha seleccionado licores." << endl;
    edad = leer_entero("verifique la edad del cliente: ", 15, 100);

    if (edad < 18) {
        cout << "Lo siento, no puede comprar licores a menores de 18 anios." << endl;
        return;
    }

    do {
        cout << "Ingrese el tipo de licor que desea comprar: " << endl;
        cout << "1. cerveza nacional       " << endl;
        cout << "2. cerveza importada   " << endl;
        cout << "3. vino  " << endl;
        cout << "4. vodka  " << endl;
        tipo_producto = leer_entero("", 1, 4);
        k = tipo_producto + 6;

        cantidad = comprar_producto(k, unidades);
        if (cantidad > 0) {
            sub_licores = sub_licores + cantidad * precio_producto(k);
            if (k == 7 || k == 8) desc_sixpack = desc_sixpack + (cantidad / 6) * 10;
        }

        cout << " desea agregar otro producto menu licores? " << endl;
        cout << "1. si " << endl;
        cout << "2. no " << endl;
        agregar_producto = leer_entero("", 1, 2);
    } while (agregar_producto == 1);
}

void mostrar_factura(string nombre, int edad_cliente, int tipo_cliente, int dia_semana,
                     double sub_verduras, double sub_carnes, double sub_licores,
                     double desc_segundo_carne, double desc_sixpack, int unidades) {
    double subtotal, pv, pc, pl, pdia, pedad, d_verd, d_carn, d_lic;
    double desc_cliente, desc_dia, desc_edad, descuentos, impuestos, total, dolares;

    subtotal = sub_verduras + sub_carnes + sub_licores;
    pv = 0; pc = 0; pl = 0;
    if (tipo_cliente == 2) {
        pv = 0.04;
        pc = 0.04;
    } else if (tipo_cliente == 1) {
        pc = 0.03;
    } else {
        pl = 0.02;
    }
    pdia = 0;
    if (dia_semana == 1 || dia_semana == 3) pdia = 0.03;
    pedad = 0;
    if (dia_semana == 5 && edad_cliente >= 65) pedad = 0.10;
    desc_cliente = sub_verduras * pv + sub_carnes * pc + sub_licores * pl;
    desc_dia = subtotal * pdia;
    desc_edad = subtotal * pedad;
    d_verd = sub_verduras * (pv + pdia + pedad);
    d_carn = sub_carnes * (pc + pdia + pedad) + desc_segundo_carne;
    d_lic = sub_licores * (pl + pdia + pedad) + desc_sixpack;
    descuentos = d_verd + d_carn + d_lic;

    impuestos = (sub_verduras - d_verd + sub_carnes - d_carn) * 0.15
              + (sub_licores - d_lic) * 0.18;
    total = subtotal - descuentos + impuestos;
    dolares = total / 24.5;

    cout << "\n=== FACTURA ===" << endl;
    cout << "Cliente: " << nombre << endl;
    cout << "Unidades compradas: " << unidades << endl;
    cout << "Subtotal: L " << subtotal << endl;
    cout << "--- Descuentos ---" << endl;
    cout << "Por tipo de cliente: L " << desc_cliente << endl;
    cout << "Lunes/Miercoles (3%): L " << desc_dia << endl;
    cout << "Viernes tercera edad (10%): L " << desc_edad << endl;
    cout << "Segundo producto de carnes (50%): L " << desc_segundo_carne << endl;
    cout << "Six-pack de cerveza: L " << desc_sixpack << endl;
    cout << "Total descuentos: L " << descuentos << endl;
    cout << "Impuestos (ISV): L " << impuestos << endl;
    cout << "TOTAL A PAGAR: L " << total << endl;
    cout << "Total en Dolares: $ " << dolares << endl;
    cout << "=============================" << endl;
}

void realizar_compra() {
    int sexo, edad, tipo_cliente, tipo_producto, agregar_producto, dia_semana;
    int edad_cliente, unidades, lineas_carnes;
    double sub_verduras, sub_carnes, sub_licores, desc_segundo_carne, desc_sixpack;
    string nombre, Tipo_producto;

    limpiar_carrito();
    unidades = 0;
    lineas_carnes = 0;
    sub_verduras = 0;
    sub_carnes = 0;
    sub_licores = 0;
    desc_segundo_carne = 0;
    desc_sixpack = 0;

    cout << "Bienvenido a Super Market!" << endl;
    do {
        cout << "INGRESE SU NOMBRE: ";
        getline(cin, nombre);
        if (cin.eof()) exit(0);
        if (nombre.empty()) {
            cout << "ERROR: Debe ingresar un nombre para continuar." << endl;
        }
    } while (nombre.empty());

    cout << "Seleccione el sexo del cliente: " << endl;
    cout << "1. Masculino" << endl;
    cout << "2. Femenino" << endl;
    cout << "3. Otro" << endl;
    sexo = leer_entero("", 1, 3);

    edad = leer_entero("Ingrese la edad del cliente: ", 15, 100);
    edad_cliente = edad;

    cout << " seleccione el tipo de cliente: " << endl;
    cout << "1. Regular" << endl;
    cout << "2. VIP" << endl;
    cout << "3. nuevo " << endl;
    tipo_cliente = leer_entero("", 1, 3);

    cout << "seleccione dia de la semana: " << endl;
    cout << "1. Lunes" << endl;
    cout << "2. Martes" << endl;
    cout << "3. Miercoles" << endl;
    cout << "4. Jueves" << endl;
    cout << "5. Viernes" << endl;
    cout << "6. Sabado" << endl;
    cout << "7. Domingo" << endl;
    dia_semana = leer_entero("", 1, 7);

    do {
        cout << " seleccione el tipo de producto que desea comprar: " << endl;
        cout << "1. verduras" << endl;
        cout << "2. carnes" << endl;
        cout << "3. licores " << endl;
        tipo_producto = leer_entero("", 1, 3);

        switch (tipo_producto) {
            case 1:
                menu_verduras(sub_verduras, unidades);
                break;
            case 2:
                menu_carnes(sub_carnes, desc_segundo_carne, lineas_carnes, unidades);
                break;
            case 3:
                menu_licores(sub_licores, desc_sixpack, unidades);
                break;
        }

        cout << " desea agregar otro producto menu principal? " << endl;
        cout << "1. si " << endl;
        cout << "2. no " << endl;
        agregar_producto = leer_entero("", 1, 2);
    } while (agregar_producto == 1);

    if (unidades == 0) {
        cout << "No se compro ningun producto." << endl;
        limpiar_carrito();
    } else {
        mostrar_factura(nombre, edad_cliente, tipo_cliente, dia_semana,
                        sub_verduras, sub_carnes, sub_licores,
                        desc_segundo_carne, desc_sixpack, unidades);
        confirmar_compra();
    }
}

void ver_inventario() {
    int i;
    cout << "\n===== INVENTARIO =====" << endl;
    for (i = 1; i <= 10; i++) {
        cout << i << ". " << nombre_producto(i) << " | Precio: L " << precio_producto(i)
             << " | Stock: " << obtener_stock(i) << " | Vendidas: " << obtener_vendidas(i) << endl;
    }
}

void reabastecer_inventario() {
    int i, producto, cantidad;

    for (i = 1; i <= 10; i++) {
        cout << i << ". " << nombre_producto(i) << " | Stock: " << obtener_stock(i) << endl;
    }
    producto = leer_entero("Numero de producto a reabastecer (1-10): ", 1, 10);
    cantidad = leer_entero("Cantidad a agregar: ", 1, 10000);
    sumar_stock(producto, cantidad);
    cout << "Stock actualizado: " << nombre_producto(producto) << " ahora tiene " << obtener_stock(producto) << " unidades." << endl;
}

int main () {
    int opcion_menu = 0;

    cout << fixed << setprecision(2);

    while (opcion_menu != 4) {
        cout << "\n===== SUPER MARKET - MENU PRINCIPAL =====" << endl;
        cout << "1. Realizar una compra" << endl;
        cout << "2. Ver inventario" << endl;
        cout << "3. Reabastecer inventario" << endl;
        cout << "4. Salir" << endl;
        opcion_menu = leer_entero("Seleccione una opcion: ", 1, 4);

        switch (opcion_menu) {
            case 1:
                realizar_compra();
                break;
            case 2:
                ver_inventario();
                break;
            case 3:
                reabastecer_inventario();
                break;
            case 4:
                cout << "Gracias por usar Super Market. Hasta pronto!" << endl;
                break;
        }
    }
       return 0;
}