#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// karen viviana Delgado Angulo

// Estructura de datos para representar un jugador
typedef struct {
    int id;
    char nombre[30];
    int edad;
    char genero; // 'M' o 'F'
    char deporte[50];
} Jugador;

// Nodo para la cola de espera (FIFO)
typedef struct NodoCola {
    Jugador jugador;
    struct NodoCola* siguiente;
} NodoCola;

// Nodo para la pila del historial (LIFO)
typedef struct NodoPila {
    Jugador jugador;
    struct NodoPila* siguiente;
} NodoPila;

// Punteros para el frente y el final de la cola
NodoCola* frente = NULL;
NodoCola* final = NULL;

// Puntero para la cima de la pila
NodoPila* cima = NULL;

// Función para contar la diferencia de género en la cola
int diferenciaGenero() {
    int hombres = 0, mujeres = 0;
    NodoCola* actual = frente;
    while (actual != NULL) {
        if (actual->jugador.genero == 'M')
            hombres++;
        else if (actual->jugador.genero == 'F')
            mujeres++;
        actual = actual->siguiente;
    }
    return abs(hombres - mujeres);
}

// Agregar jugador a la cola con validaciones
void agregarJugador() {
    Jugador nuevo;
    printf("Ingrese ID: ");
    scanf("%d", &nuevo.id);
    getchar(); // limpiar buffer

    printf("Ingrese nombre: ");
    fgets(nuevo.nombre, 30, stdin);
    nuevo.nombre[strcspn(nuevo.nombre, "\n")] = 0;

    printf("Ingrese edad: ");
    scanf("%d", &nuevo.edad);

    printf("Ingrese genero (M/F): ");
    getchar();
    scanf("%c", &nuevo.genero);

    printf("Ingrese deporte: ");
    getchar();
    fgets(nuevo.deporte, 50, stdin);
    nuevo.deporte[strcspn(nuevo.deporte, "\n")] = 0;

    if (nuevo.edad < 15) {
        printf("Jugador menor de 15 años. No puede ser agregado.\n");
        return;
    }

    if (diferenciaGenero() > 4) {
        printf("Diferencia de genero superior a 4. No se puede agregar el jugador hasta que se equilibre.\n");
        return;
    }

    NodoCola* nuevoNodo = (NodoCola*)malloc(sizeof(NodoCola));
    nuevoNodo->jugador = nuevo;
    nuevoNodo->siguiente = NULL;

    if (final == NULL) {
        frente = final = nuevoNodo;
    } else {
        final->siguiente = nuevoNodo;
        final = nuevoNodo;
    }

    printf("Jugador agregado a la cola de espera.\n");
}

// Mostrar jugadores en espera
void mostrarEspera() {
    NodoCola* actual = frente;
    if (actual == NULL) {
        printf("No hay jugadores en espera.\n");
        return;
    }
    printf("Jugadores en espera:\n");
    while (actual != NULL) {
        printf("ID: %d | Nombre: %s | Edad: %d | Genero: %c | Deporte: %s\n",
               actual->jugador.id, actual->jugador.nombre,
               actual->jugador.edad, actual->jugador.genero,
               actual->jugador.deporte);
        actual = actual->siguiente;
    }
}

// Contar jugadores en espera
int contarEspera() {
    int contador = 0;
    NodoCola* actual = frente;
    while (actual != NULL) {
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}

// Permitir participación (retirar de la cola y agregar al historial)
void permitirParticipacion() {
    if (frente == NULL) {
        printf("No hay jugadores en espera.\n");
        return;
    }

    Jugador jugador = frente->jugador;
    NodoCola* temp = frente;
    frente = frente->siguiente;
    if (frente == NULL) final = NULL; // si la cola queda vacía

    free(temp);

    // Agregar a la pila (historial)
    NodoPila* nuevoNodo = (NodoPila*)malloc(sizeof(NodoPila));
    nuevoNodo->jugador = jugador;
    nuevoNodo->siguiente = cima;
    cima = nuevoNodo;

    printf("Jugador %s participó y fue registrado en el historial.\n", jugador.nombre);
}

// Mostrar historial de participación
void mostrarHistorial() {
    NodoPila* actual = cima;
    if (actual == NULL) {
        printf("El historial está vacío.\n");
        return;
    }

    printf("Historial de participación:\n");
    while (actual != NULL) {
        printf("ID: %d | Nombre: %s | Edad: %d | Genero: %c | Deporte: %s\n",
               actual->jugador.id, actual->jugador.nombre,
               actual->jugador.edad, actual->jugador.genero,
               actual->jugador.deporte);
        actual = actual->siguiente;
    }
}

// Deshacer última participación
void deshacerParticipacion() {
    if (cima == NULL) {
        printf("No hay participación para deshacer.\n");
        return;
    }

    Jugador jugador = cima->jugador;
    NodoPila* temp = cima;
    cima = cima->siguiente;
    free(temp);

    // Agregar al final de la cola nuevamente
    NodoCola* nuevoNodo = (NodoCola*)malloc(sizeof(NodoCola));
    nuevoNodo->jugador = jugador;
    nuevoNodo->siguiente = NULL;

    if (final == NULL) {
        frente = final = nuevoNodo;
    } else {
        final->siguiente = nuevoNodo;
        final = nuevoNodo;
    }

    printf("Última participación deshecha. Jugador %s vuelve a la cola de espera.\n", jugador.nombre);
}

// Menú principal
void menu() {
    int opcion;
    do {
        printf("\n Registro de Jugadores Gran Torneo Deportivo  \n");
        printf("1. Agregar jugador a la cola\n");
        printf("2. Mostrar jugadores en espera\n");
        printf("3. Contar jugadores en espera\n");
        printf("4. Permitir participación del siguiente jugador\n");
        printf("5. Mostrar historial de participación\n");
        printf("6. Deshacer última participación\n");
        printf("7. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarJugador();
                break;
            case 2:
                mostrarEspera();
                break;
            case 3:
                printf("Hay %d jugadores en espera.\n", contarEspera());
                break;
            case 4:
                permitirParticipacion();
                break;
            case 5:
                mostrarHistorial();
                break;
            case 6:
                deshacerParticipacion();
                break;
            case 7:
                printf("Saliendo del sistema.\n");
                break;
            default:
                printf("Opción no válida.\n");
        }

    } while (opcion != 7);
}

// Función principal
int main() {
    menu();
    return 0;
}