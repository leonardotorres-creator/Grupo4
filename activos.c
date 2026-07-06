#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "activos.h"
#include "colors.h"

Nodo* crearNodo(Activo a) {
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    if(nuevo != NULL) {
        nuevo->dato = a;
        nuevo->ant = NULL;
        nuevo->sig = NULL;
    }
    return nuevo;
}

void insertarFinal(Nodo **cab, Activo a) {
    Nodo *nuevo = crearNodo(a);
    if(nuevo == NULL) return;

    if(*cab == NULL) {
        *cab = nuevo;
        return;
    }

    Nodo *aux = *cab;
    while(aux->sig != NULL)
        aux = aux->sig;

    aux->sig = nuevo;
    nuevo->ant = aux;
}

Nodo* buscarPorCodigo(Nodo *cab, int codigo) {
    Nodo *aux = cab;
    while(aux != NULL) {
        if(aux->dato.codigo == codigo)
            return aux;
        aux = aux->sig;
    }
    return NULL;
}

void registrarActivo(Nodo **cab) {
    Activo nuevo;

    printf(WHITE"Codigo del Activo: "RESET);
    scanf("%d", &nuevo.codigo);

    if(buscarPorCodigo(*cab, nuevo.codigo) != NULL) {
        printf(RED"Error: El codigo de activo ya existe en el sistema\n"RESET);
        return;
    }

    printf(WHITE"Nombre del Activo : "RESET);
    scanf(" %[^\n]", nuevo.nombre);
    printf(WHITE"Tipo de Activo (Hardaware - Software - Redes): "RESET);
    scanf(" %[^\n]", nuevo.tipo);
    printf(WHITE"Departamento asignado : "RESET);
    scanf(" %[^\n]", nuevo.departamento);
    printf(WHITE"Responsable de la custodia: "RESET);
    scanf(" %[^\n]", nuevo.responsable);
    
    // Por defecto, todo activo ingresa con estado Activo
    strcpy(nuevo.estado, "Activo");

    insertarFinal(cab, nuevo);
    printf(GREEN"Activo registrado con exito en la infraestructura.\n"RESET);
}

void eliminarNodo(Nodo **cab, int codigo) {
    Nodo *aux = buscarPorCodigo(*cab, codigo);

    if(aux == NULL) return;

    if(aux->ant == NULL && aux->sig == NULL) {
        *cab = NULL; 
    } else if(aux->ant == NULL) {
        *cab = aux->sig; 
        (*cab)->ant = NULL;
    } else if(aux->sig == NULL) {
        aux->ant->sig = NULL; 
    } else {
        aux->ant->sig = aux->sig; 
        aux->sig->ant = aux->ant;
    }

    free(aux);
}

void darDeBajaActivo(Nodo **cab) {
    int codigo;
    printf(GRAY"Ingrese el codigo del activo a dar de baja: "RESET);
    scanf("%d", &codigo);
    
    Nodo *aux = buscarPorCodigo(*cab, codigo);
    if(aux != NULL) {
        eliminarNodo(cab, codigo);
        printf(ORANGE"El activo ha sido dado de baja y removido del inventario.\n"RESET);
    } else {
        printf(RED"Error: Activo no encontrado.\n"RESET);
    }
}

void liberarLista(Nodo **cab) {
    Nodo *aux;
    while(*cab != NULL) {
        aux = *cab;
        *cab = (*cab)->sig;
        free(aux);
    }
}