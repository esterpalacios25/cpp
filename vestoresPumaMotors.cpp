
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ---------- Constantes del sistema ----------
const float ISV = 0.15;          // Impuesto sobre ventas 15%
const float TASA_DOLAR = 26.42;  // 1 USD = 26.42 Lps.

// ---------- Vectores con los datos de los productos ----------
// Todos los vectores de productos tienen la misma posicion:
// la posicion 0 es el producto con codigo 1, la 1 el codigo 2, etc.
vector<string> producto;     // nombre del producto
vector<int>    categoria;    // 0=Motor, 1=Frenos, 2=Electrico, 3=Accesorios
vector<float>  precio;       // precio en Lempiras
vector<int>    inventario;   // unidades disponibles
vector<int>    puntos;       // puntos que da cada unidad

// ---------- Vectores con nombres de categorias y tipos de cliente ----------
vector<string> nombreCategoria;
vector<string> tipoCliente;

// ---------- Vectores para las estadisticas del dia ----------
vector<int>   unidadesVendidas;   // unidades vendidas de cada producto
vector<float> ventaCategoria;     // total vendido por categoria (sin ISV)
vector<int>   conteoPago;         // 0=Efectivo, 1=Transferencia
float totalDescuentos = 0;
float totalISV = 0;
float totalGeneral = 0;

// ============================================================
//  FUNCIONES
// ============================================================

// Agrega un producto a todos los vectores
void agregarProducto(string nom, int cat, float pre, int inv, int pts) {
	producto.push_back(nom);
	categoria.push_back(cat);
	precio.push_back(pre);
	inventario.push_back(inv);
	puntos.push_back(pts);
	unidadesVendidas.push_back(0);
}

// Llena los vectores con la informacion de la tabla del examen
void cargarDatos() {
	nombreCategoria.push_back("Motor y Afinacion");
	nombreCategoria.push_back("Frenos y Suspension");
	nombreCategoria.push_back("Electrico");
	nombreCategoria.push_back("Accesorios");

	tipoCliente.push_back("Particular");
	tipoCliente.push_back("Taller");
	tipoCliente.push_back("Flotilla");

	// nombre, categoria, precio, inventario, puntos
	agregarProducto("Filtro de aceite",          0,  120.00, 30,  10);
	agregarProducto("Bujia (unidad)",            0,   90.00, 80,   8);
	agregarProducto("Aceite 10W-30 (litro)",     0,  180.00, 40,  12);
	agregarProducto("Pastillas de freno (juego)",1,  450.00, 25,  25);
	agregarProducto("Disco de freno (unidad)",   1,  900.00, 15,  40);
	agregarProducto("Amortiguador (unidad)",     1, 1200.00, 12,  50);
	agregarProducto("Bateria 12V",               2, 2500.00, 10,  80);
	agregarProducto("Alternador",                2, 3800.00,  6, 100);
	agregarProducto("Bombillo LED (unidad)",     2,   80.00, 60,   5);
	agregarProducto("Limpiaparabrisas (par)",    3,  250.00, 20,  15);
	agregarProducto("Aromatizante",              3,   60.00, 50,   3);
	agregarProducto("Cera para auto",            3,  150.00, 25,   8);

	for (int i = 0; i < 4; i++) {
		ventaCategoria.push_back(0);
	}
	conteoPago.push_back(0);
	conteoPago.push_back(0);
}

// Lee un numero entero y no deja avanzar hasta que sea valido
int leerEntero(string mensaje, int minimo, int maximo) {
	int valor;
	cout << mensaje;
	cin >> valor;
	while (cin.fail() || valor < minimo || valor > maximo) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "   ERROR: valor no valido (de " << minimo << " a " << maximo << "). Intente otra vez: ";
		cin >> valor;
	}
	cin.ignore(1000, '\n');
	return valor;
}

// Lee un monto (decimal) mayor que cero
float leerMonto(string mensaje) {
	float valor;
	cout << mensaje;
	cin >> valor;
	while (cin.fail() || valor <= 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "   ERROR: monto no valido. Intente otra vez: ";
		cin >> valor;
	}
	cin.ignore(1000, '\n');
	return valor;
}

// Muestra el menu de productos con precio e inventario actual
void mostrarProductos() {
	cout << endl;
	cout << " -------------------------------------------------------------------------" << endl;
	cout << " COD | CATEGORIA            | PRODUCTO                    | PRECIO   | STOCK" << endl;
	cout << " -------------------------------------------------------------------------" << endl;
	for (int i = 0; i < (int)producto.size(); i++) {
		cout << "  " << (i + 1) << "\t| " << nombreCategoria[categoria[i]] << "\t| "
		     << producto[i] << "\t| L." << precio[i] << "\t| " << inventario[i] << endl;
	}
	cout << " -------------------------------------------------------------------------" << endl;
}

// Calcula el porcentaje total de descuento de UN producto de la factura
// (todos los descuentos que apliquen se suman)
float porcentajeDescuento(int p, int tipo, int genero, int edad, vector<int> &cant) {
	float pct = 0;
	int cat = categoria[p];

	// Descuento por tipo de cliente
	if (tipo == 1 && cat == 3) pct = pct + 5;    // Particular: 5% Accesorios
	if (tipo == 2 && cat == 0) pct = pct + 10;   // Taller: 10% Motor y Afinacion
	if (tipo == 3 && cat == 1) pct = pct + 12;   // Flotilla: 12% Frenos y Suspension

	// Descuento adicional por genero
	if (genero == 2 && cat == 3) pct = pct + 10; // Mujer: 10% Accesorios
	if (genero == 1 && cat == 1) pct = pct + 5;  // Hombre: 5% Frenos y Suspension

	// Descuento adicional por tercera edad
	if (edad >= 60) pct = pct + 10;

	// Promocion cambio de aceite: Aceite (posicion 2) + Filtro (posicion 0)
	if ((p == 2 || p == 0) && cant[2] > 0 && cant[0] > 0) pct = pct + 8;

	// Promocion por volumen: mas de 5 unidades del mismo producto
	if (cant[p] > 5) pct = pct + 3;

	return pct;
}

// Muestra el modulo de estadisticas al terminar el dia
void mostrarEstadisticas() {
	int n = producto.size();
	int mayor = 0, menor = 1000000;

	// Buscamos el maximo y el minimo de unidades vendidas
	for (int i = 0; i < n; i++) {
		if (unidadesVendidas[i] > mayor) mayor = unidadesVendidas[i];
		if (unidadesVendidas[i] > 0 && unidadesVendidas[i] < menor) menor = unidadesVendidas[i];
	}

	cout << endl;
	cout << "=========================================================" << endl;
	cout << "              ESTADISTICAS DEL DIA - PUMA MOTOR PARTS" << endl;
	cout << "=========================================================" << endl;

	if (mayor == 0) {
		cout << " No se realizo ninguna venta." << endl;
		return;
	}

	cout << " 1. Producto(s) mas vendido(s): " << endl;
	for (int i = 0; i < n; i++) {
		if (unidadesVendidas[i] == mayor) {
			cout << "      " << producto[i] << " (" << mayor << " unidades)" << endl;
		}
	}

	cout << " 2. Producto(s) menos vendido(s) (sin contar los no vendidos): " << endl;
	for (int i = 0; i < n; i++) {
		if (unidadesVendidas[i] == menor) {
			cout << "      " << producto[i] << " (" << menor << " unidades)" << endl;
		}
	}

	cout << " 3. Ganancia por categoria (sin ISV):" << endl;
	for (int c = 0; c < 4; c++) {
		cout << "      " << nombreCategoria[c] << ": L." << ventaCategoria[c] << endl;
	}

	cout << " 4. Total descuentos aplicados del dia: L." << totalDescuentos << endl;
	cout << " 5. Total ISV recaudado: L." << totalISV << endl;
	cout << " 6. Total general vendido: L." << totalGeneral
	     << "  /  $" << (totalGeneral / TASA_DOLAR) << endl;

	cout << " 7. Metodo de pago mas utilizado: ";
	if (conteoPago[0] > conteoPago[1]) {
		cout << "Efectivo (" << conteoPago[0] << " veces)" << endl;
	} else if (conteoPago[1] > conteoPago[0]) {
		cout << "Transferencia (" << conteoPago[1] << " veces)" << endl;
	} else {
		cout << "Empate: Efectivo (" << conteoPago[0] << ") y Transferencia (" << conteoPago[1] << ")" << endl;
	}
	cout << "=========================================================" << endl;
}

// ============================================================
//  PROGRAMA PRINCIPAL
// ============================================================
int main() {

	cargarDatos();
	cout << fixed;          // para mostrar siempre 2 decimales
	cout.precision(2);

	int numFactura = 0;
	char otro;

	cout << endl;
	cout << "         --------------------------------------" << endl;
	cout << "         |            BIENVENIDO              |" << endl;
	cout << "         |               a                    |" << endl;
	cout << "         |        PUMA MOTOR PARTS            |" << endl;
	cout << "         --------------------------------------" << endl;

	do {
		// ---------- DATOS DEL CLIENTE ----------
		string nombre;
		cout << endl << " ----------- DATOS DEL CLIENTE -----------" << endl;
		cout << " Nombre del cliente (sin espacios): ";
		cin >> nombre;
		cin.ignore(1000, '\n');

		int edad = leerEntero(" Edad (18 a 120): ", 18, 120);
		int genero = leerEntero(" Genero (1=Hombre, 2=Mujer): ", 1, 2);

		cout << endl << " Tipo de cliente:" << endl;
		cout << "   1) Particular (5% en Accesorios)" << endl;
		cout << "   2) Taller (10% en Motor y Afinacion)" << endl;
		cout << "   3) Flotilla (12% en Frenos y Suspension)" << endl;
		int tipo = leerEntero(" Opcion: ", 1, 3);

		// ---------- SELECCION DE PRODUCTOS ----------
		// Este vector guarda cuantas unidades de cada producto lleva ESTE cliente
		vector<int> cantFactura(producto.size(), 0);
		int codigo, cantidad;
		int totalUnidades = 0;

		do {
			mostrarProductos();
			codigo = leerEntero(" Codigo del producto (0 = terminar compra): ", 0, (int)producto.size());

			if (codigo != 0) {
				cantidad = leerEntero(" Cantidad: ", 1, 100000);

				if (cantidad > inventario[codigo - 1]) {
					cout << "   Stock insuficiente" << endl;
				} else {
					// Se descuenta del inventario automaticamente
					inventario[codigo - 1] = inventario[codigo - 1] - cantidad;
					cantFactura[codigo - 1] = cantFactura[codigo - 1] + cantidad;
					totalUnidades = totalUnidades + cantidad;
					cout << "   Producto agregado a la factura." << endl;
				}
			}
		} while (codigo != 0);

		if (totalUnidades == 0) {
			cout << endl << " No se agrego ningun producto. Factura cancelada." << endl;
		} else {

			// ---------- CALCULO DE LA FACTURA ----------
			int n = producto.size();
			vector<float> subLinea(n, 0);
			vector<float> pctLinea(n, 0);
			vector<float> descLinea(n, 0);
			float subtotal = 0, descuento = 0;
			int puntosCliente = 0;

			for (int i = 0; i < n; i++) {
				if (cantFactura[i] > 0) {
					subLinea[i] = cantFactura[i] * precio[i];
					pctLinea[i] = porcentajeDescuento(i, tipo, genero, edad, cantFactura);
					descLinea[i] = subLinea[i] * pctLinea[i] / 100;
					subtotal = subtotal + subLinea[i];
					descuento = descuento + descLinea[i];
					puntosCliente = puntosCliente + (puntos[i] * cantFactura[i]);
				}
			}

			float baseImponible = subtotal - descuento;
			float impuesto = baseImponible * ISV;
			float total = baseImponible + impuesto;
			float totalDolares = total / TASA_DOLAR;

			numFactura++;

			// ---------- IMPRESION DE LA FACTURA ----------
			cout << endl;
			cout << "=====================================================================" << endl;
			cout << "                      PUMA MOTOR PARTS - FACTURA" << endl;
			cout << "=====================================================================" << endl;
			cout << " Factura N: " << numFactura << endl;
			cout << " Cliente: " << nombre << "   Edad: " << edad;
			if (genero == 1) cout << "   Genero: Hombre" << endl;
			else cout << "   Genero: Mujer" << endl;
			cout << " Tipo de cliente: " << tipoCliente[tipo - 1] << endl;
			cout << "---------------------------------------------------------------------" << endl;
			cout << " CANT | PRODUCTO\t\t\t| P.UNIT | SUBTOTAL | %DESC | DESCUENTO" << endl;
			cout << "---------------------------------------------------------------------" << endl;
			for (int i = 0; i < n; i++) {
				if (cantFactura[i] > 0) {
					cout << "  " << cantFactura[i] << "\t| " << producto[i] << "\t| "
					     << precio[i] << " | " << subLinea[i] << " | "
					     << pctLinea[i] << "% | " << descLinea[i] << endl;
				}
			}
			cout << "---------------------------------------------------------------------" << endl;
			cout << " Subtotal:                 L." << subtotal << endl;
			cout << " Descuentos:               L." << descuento << endl;
			cout << " Total despues de desc.:   L." << baseImponible << endl;
			cout << " ISV (15%):                L." << impuesto << endl;
			cout << " TOTAL A PAGAR:            L." << total << endl;
			cout << " TOTAL EN DOLARES:         $" << totalDolares << "  (1 USD = 26.42 Lps.)" << endl;
			cout << " PUNTOS ACUMULADOS:        " << puntosCliente << endl;
			cout << "---------------------------------------------------------------------" << endl;

			// ---------- METODO DE PAGO ----------
			cout << endl << " Metodo de pago:" << endl;
			cout << "   1) Efectivo" << endl;
			cout << "   2) Transferencia" << endl;
			int metodo = leerEntero(" Opcion: ", 1, 2);

			if (metodo == 1) {
				float recibido = leerMonto(" Monto recibido: L.");
				while (recibido < total) {
					cout << "   El monto no alcanza. Faltan L." << (total - recibido) << endl;
					recibido = leerMonto(" Monto recibido: L.");
				}
				cout << endl << " Pago en EFECTIVO" << endl;
				cout << " Recibido: L." << recibido << endl;
				cout << " Cambio:   L." << (recibido - total) << endl;
			} else {
				string comprobante, bancoEmisor, bancoDestino;
				cout << " Numero de comprobante/referencia: ";
				cin >> comprobante;
				cin.ignore(1000, '\n');
				float monto = leerMonto(" Cantidad transferida (debe ser exacta): L.");
				while (monto < total - 0.01 || monto > total + 0.01) {
					cout << "   La cantidad debe ser exactamente L." << total << endl;
					monto = leerMonto(" Cantidad transferida: L.");
				}
				cout << " Banco de emision (sin espacios): ";
				cin >> bancoEmisor;
				cout << " Banco de destino (sin espacios): ";
				cin >> bancoDestino;
				cin.ignore(1000, '\n');
				cout << endl << " Pago por TRANSFERENCIA" << endl;
				cout << " Comprobante: " << comprobante << endl;
				cout << " Monto: L." << monto << endl;
				cout << " Banco emisor: " << bancoEmisor << "   Banco destino: " << bancoDestino << endl;
			}

			cout << endl << " Gracias por su compra, " << nombre << "!" << endl;
			cout << "=====================================================================" << endl;

			// ---------- ACTUALIZAR ESTADISTICAS ----------
			for (int i = 0; i < n; i++) {
				if (cantFactura[i] > 0) {
					unidadesVendidas[i] = unidadesVendidas[i] + cantFactura[i];
					ventaCategoria[categoria[i]] = ventaCategoria[categoria[i]] + (subLinea[i] - descLinea[i]);
				}
			}
			conteoPago[metodo - 1] = conteoPago[metodo - 1] + 1;
			totalDescuentos = totalDescuentos + descuento;
			totalISV = totalISV + impuesto;
			totalGeneral = totalGeneral + total;
		}

		// ---------- OTRO CLIENTE ----------
		cout << endl << " Desea ingresar otro cliente? (S/N): ";
		cin >> otro;
		cin.ignore(1000, '\n');
		while (otro != 'S' && otro != 's' && otro != 'N' && otro != 'n') {
			cout << "   ERROR: escriba S o N: ";
			cin >> otro;
			cin.ignore(1000, '\n');
		}

	} while (otro == 'S' || otro == 's');

	// ---------- ESTADISTICAS FINALES ----------
	mostrarEstadisticas();

	return 0;
}