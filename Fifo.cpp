#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Definición de la estructura para representar un producto
struct Producto {
    int codigo;      // Código único del producto
    string nombre;   // Nombre del producto
    int cantidad;    // Cantidad disponible en inventario
    int precio;      // Precio por unidad del producto
};

// Vector que almacenará los productos en el inventario
vector<Producto> inventario;

// Función para registrar un nuevo producto en el inventario
void registrarProducto() {
    Producto p;
    cout << "Ingrese código: ";
    cin >> p.codigo;
    cout << "Ingrese nombre: ";
    cin >> ws; // Limpia el buffer de entrada
    getline(cin, p.nombre); // Permite leer el nombre completo incluyendo espacios
    cout << "Ingrese cantidad: ";
    cin >> p.cantidad;
    cout << "Ingrese precio por unidad: ";
    cin >> p.precio;
    
    // Agregar el producto al inventario
    inventario.push_back(p);
    cout << "Producto registrado con éxito.\n";
}

// Función para mostrar todos los productos en el inventario
void mostrarProductos() {
    cout << "\nInventario:\n";
    cout << "Código\tNombre\tCantidad\tPrecio\tCosto Total\n";
    for (const auto &p : inventario) {
        int costoTotal = p.cantidad * p.precio; // Cálculo del costo total por producto
        cout << p.codigo << "\t" << p.nombre << "\t" << p.cantidad << "\t" << p.precio << "\t" << costoTotal << "\n";
    }
}

// Función para actualizar la cantidad de un producto tras una venta
void actualizarCantidad() {
    int codigo, cantidad;
    cout << "Ingrese código del producto vendido: ";
    cin >> codigo;
    cout << "Ingrese cantidad vendida: ";
    cin >> cantidad;
    
    // Buscar el producto en el inventario
    for (auto &p : inventario) {
        if (p.codigo == codigo) {
            if (p.cantidad >= cantidad) {
                p.cantidad -= cantidad; // Reducir la cantidad en el inventario
                cout << "Cantidad actualizada.\n";
            } else {
                cout << "No hay suficiente stock.\n";
            }
            return;
        }
    }
    cout << "Producto no encontrado.\n";
}

// Función para calcular el costo total del inventario
void calcularCostoTotal() {
    int costoTotal = 0;
    
    // Sumar el costo total de todos los productos en el inventario
    for (const auto &p : inventario) {
        costoTotal += p.cantidad * p.precio;
    }
    cout << "Costo total del inventario: " << costoTotal << "\n";
}

// Función para eliminar un producto del inventario si su cantidad es cero
void eliminarProducto() {
    int codigo;
    cout << "Ingrese código del producto a eliminar: ";
    cin >> codigo;
    
    // Buscar el producto en el inventario
    for (auto it = inventario.begin(); it != inventario.end(); ++it) {
        if (it->codigo == codigo) {
            if (it->cantidad == 0) {
                inventario.erase(it); // Eliminar el producto del inventario
                cout << "Producto eliminado.\n";
            } else {
                cout << "No se puede eliminar. La cantidad no es cero.\n";
            }
            return;
        }
    }
    cout << "Producto no encontrado.\n";
}

// Función principal del programa
int main() {
    int opcion;
    do {
        // Menú de opciones
        cout << "\n1. Registrar Producto\n";
        cout << "2. Mostrar Productos\n";
        cout << "3. Actualizar Cantidad tras Venta\n";
        cout << "4. Calcular Costo Total del Inventario\n";
        cout << "5. Eliminar Producto\n";
        cout << "6. Salir\n";
        cout << "Ingrese opción: ";
        cin >> opcion;
        
        // Ejecutar la opción seleccionada
        switch (opcion) {
            case 1:
                registrarProducto();
                break;
            case 2:
                mostrarProductos();
                break;
            case 3:
                actualizarCantidad();
                break;
            case 4:
                calcularCostoTotal();
                break;
            case 5:
                eliminarProducto();
                break;
            case 6:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 6); // Repetir el menú hasta que el usuario decida salir
    
    return 0;
}