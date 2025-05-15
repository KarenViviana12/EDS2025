
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PELICULAS 100

// Estructura de un nodo del arbol (pelicula)
typedef struct Pelicula {
    char nombre[100];
    int anio;
    char genero[30];
    float recaudacion;
    struct Pelicula* izquierda;
    struct Pelicula* derecha;
} Pelicula;

// Crea y devuelve un nuevo nodo de pelicula
Pelicula* crearPelicula(char* nombre, int anio, char* genero, float recaudacion) {
    Pelicula* nueva = (Pelicula*) malloc(sizeof(Pelicula));
    strcpy(nueva->nombre, nombre);
    nueva->anio = anio;
    strcpy(nueva->genero, genero);
    nueva->recaudacion = recaudacion;
    nueva->izquierda = nueva->derecha = NULL;
    return nueva;
}

// Inserta una pelicula en el arbol binario de acuerdo al anio
Pelicula* insertarPelicula(Pelicula* raiz, char* nombre, int anio, char* genero, float recaudacion) {
    if (raiz == NULL)
        return crearPelicula(nombre, anio, genero, recaudacion);

    if (anio < raiz->anio)
        raiz->izquierda = insertarPelicula(raiz->izquierda, nombre, anio, genero, recaudacion);
    else if (anio > raiz->anio)
        raiz->derecha = insertarPelicula(raiz->derecha, nombre, anio, genero, recaudacion);
    else
        raiz->izquierda = insertarPelicula(raiz->izquierda, nombre, anio, genero, recaudacion);

    return raiz;
}

void inorden(Pelicula* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierda);
        printf("Nombre: %s | Año: %d | Género: %s | Recaudación: %.1fM\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
        inorden(raiz->derecha);
    }
}

void preorden(Pelicula* raiz) {
    if (raiz != NULL) {
        printf("Nombre: %s | Año: %d | Género: %s | Recaudación: %.1fM\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
        preorden(raiz->izquierda);
        preorden(raiz->derecha);
    }
}

void posorden(Pelicula* raiz) {
    if (raiz != NULL) {
        posorden(raiz->izquierda);
        posorden(raiz->derecha);
        printf("Nombre: %s | Año: %d | Género: %s | Recaudación: %.1fM\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
    }
}

void buscarPorNombre(Pelicula* raiz, const char* nombreBuscado) {
    if (raiz == NULL)
        return;

    if (strcmp(raiz->nombre, nombreBuscado) == 0) {
        printf("\n¡Película encontrada!\n");
        printf("Nombre: %s\nAño: %d\nGénero: %s\nRecaudación: %.1fM\n",
               raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
        return;
    }

    buscarPorNombre(raiz->izquierda, nombreBuscado);
    buscarPorNombre(raiz->derecha, nombreBuscado);
}

void mostrarPorGenero(Pelicula* raiz, const char* generoBuscado) {
    if (raiz == NULL)
        return;

    mostrarPorGenero(raiz->izquierda, generoBuscado);

    if (strcmp(raiz->genero, generoBuscado) == 0)
        printf("Nombre: %s | Año: %d | Recaudación: %.1fM\n", raiz->nombre, raiz->anio, raiz->recaudacion);

    mostrarPorGenero(raiz->derecha, generoBuscado);
}

Pelicula* listaPeliculas[MAX_PELICULAS];
int totalPeliculas = 0;

void guardarPeliculas(Pelicula* raiz) {
    if (raiz == NULL) return;
    guardarPeliculas(raiz->izquierda);
    if (totalPeliculas < MAX_PELICULAS)
        listaPeliculas[totalPeliculas++] = raiz;
    guardarPeliculas(raiz->derecha);
}

int compararPorRecaudacion(const void* a, const void* b) {
    Pelicula* p1 = *(Pelicula**)a;
    Pelicula* p2 = *(Pelicula**)b;
    return (p1->recaudacion > p2->recaudacion) - (p1->recaudacion < p2->recaudacion);
}

void mostrarFracasos(Pelicula* raiz) {
    totalPeliculas = 0;
    guardarPeliculas(raiz);

    if (totalPeliculas == 0) {
        printf("No hay películas registradas.\n");
        return;
    }

    qsort(listaPeliculas, totalPeliculas, sizeof(Pelicula*), compararPorRecaudacion);

    int cantidad = totalPeliculas < 3 ? totalPeliculas : 3;
    printf("\n--- 3 Fracasos Taquilleros ---\n");
    for (int i = 0; i < cantidad; i++) {
        printf("Nombre: %s | Año: %d | Género: %s | Recaudación: %.1fM\n",
               listaPeliculas[i]->nombre,
               listaPeliculas[i]->anio,
               listaPeliculas[i]->genero,
               listaPeliculas[i]->recaudacion);
    }
}

Pelicula* eliminarPelicula(Pelicula* raiz, const char* nombre) {
    if (raiz == NULL) return NULL;

    int cmp = strcmp(nombre, raiz->nombre);
    if (cmp < 0) {
        raiz->izquierda = eliminarPelicula(raiz->izquierda, nombre);
    } else if (cmp > 0) {
        raiz->derecha = eliminarPelicula(raiz->derecha, nombre);
    } else {
        if (raiz->izquierda == NULL) {
            Pelicula* temp = raiz->derecha;
            free(raiz);
            return temp;
        } else if (raiz->derecha == NULL) {
            Pelicula* temp = raiz->izquierda;
            free(raiz);
            return temp;
        } else {
            Pelicula* sucesor = raiz->derecha;
            while (sucesor->izquierda != NULL)
                sucesor = sucesor->izquierda;
            strcpy(raiz->nombre, sucesor->nombre);
            raiz->anio = sucesor->anio;
            strcpy(raiz->genero, sucesor->genero);
            raiz->recaudacion = sucesor->recaudacion;
            raiz->derecha = eliminarPelicula(raiz->derecha, sucesor->nombre);
        }
    }
    return raiz;
}

void precargarPeliculas(Pelicula** raiz) {
    *raiz = insertarPelicula(*raiz, "Titanic", 1997, "Drama", 2187.5);
    *raiz = insertarPelicula(*raiz, "Avatar", 2009, "Ciencia Ficción", 2847.2);
    *raiz = insertarPelicula(*raiz, "Avengers: Endgame", 2019, "Acción", 2798.0);
    *raiz = insertarPelicula(*raiz, "El Padrino", 1972, "Crimen", 135.0);
    *raiz = insertarPelicula(*raiz, "Coco", 2017, "Animación", 807.1);
    *raiz = insertarPelicula(*raiz, "Toy Story", 1995, "Animación", 373.6);
    *raiz = insertarPelicula(*raiz, "La La Land", 2016, "Musical", 446.1);
    *raiz = insertarPelicula(*raiz, "Batman & Robin", 1997, "Acción", 238.2);
    *raiz = insertarPelicula(*raiz, "Cats", 2019, "Musical", 73.7);
    *raiz = insertarPelicula(*raiz, "John Carter", 2012, "Aventura", 284.1);
}

int main() {
    Pelicula* raiz = NULL;
    precargarPeliculas(&raiz);
    // Menú interactivo continúa...
    return 0;
}
