#ifndef ACTIVOS_H
#define ACTIVOS_H

typedef struct {
    int codigo;
    char nombre[100];
    char tipo[50];
    char departamento[50];
    char responsable[50];
    char estado[20];
} Activo;

typedef struct Nodo {
    Activo dato;
    struct Nodo *ant;
    struct Nodo *sig;
} Nodo;

// Funciones principales del ciclo de vida del activo
void registrarActivo(Nodo **cab);
void darDeBajaActivo(Nodo **cab);

// Utilidades de la lista doblemente enlazada
Nodo* crearNodo(Activo a);
void insertarFinal(Nodo **cab, Activo a);
Nodo* buscarPorCodigo(Nodo *cab, int codigo);
void eliminarNodo(Nodo **cab, int codigo);
void liberarLista(Nodo **cab);

#endif