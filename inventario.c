#include <stdio.h>
#include <string.h>
#include "inventario.h"
#include "colors.h"

void mostrarInventarioCompleto(Nodo *cab) {
    Nodo *aux = cab;
    printf(CYAN"\n================================= INVENTARIO COMPLETO DE ACTIVOS =================================\n"RESET);
    
    if(aux == NULL) {
        printf(YELLOW" No se registran activos en el inventario actual.\n"RESET);
        printf(CYAN"==================================================================================================\n"RESET);
        return;
    }

    while(aux != NULL) {
        printf(BLUE"[%d]"RESET" %-25s | Tipo: %-12s | Dep: %-15s | Resp: %-15s | Estado: %s\n",
            aux->dato.codigo, 
            aux->dato.nombre, 
            aux->dato.tipo, 
            aux->dato.departamento, 
            aux->dato.responsable, 
            aux->dato.estado);
        aux = aux->sig;
    }
    printf(CYAN"==================================================================================================\n"RESET);
}

void mostrarActivosPorDepartamento(Nodo *cab) {
    char dep[50];
    int encontrado = 0;

    printf(BLUE"Departamento a consultar: "RESET);
    scanf(" %[^\n]", dep);

    printf(CYAN"\n===== ACTIVOS ASIGNADOS A: %s =====\n"RESET, dep);
    Nodo *aux = cab;
    while(aux != NULL) {
        if(strcmp(aux->dato.departamento, dep) == 0) {
            printf(GRAY"[%d]"RESET" %s (Responsable: %s) - Estado: %s\n",
                aux->dato.codigo, aux->dato.nombre, aux->dato.responsable, aux->dato.estado);
            encontrado = 1;
        }
        aux = aux->sig;
    }

    if(!encontrado) {
        printf(RED"No hay activos registrados en este departamento.\n"RESET);
    }
}

void actualizarResponsable(Nodo *cab) {
    int codigo;

    printf(YELLOW"Codigo del activo a actualizar: "RESET);
    scanf("%d", &codigo);

    Nodo *aux = buscarPorCodigo(cab, codigo);
    if(aux != NULL) {
        printf(WHITE"Responsable actual: %s\n"RESET, aux->dato.responsable);
        printf(YELLOW"Nuevo responsable: "RESET);
        scanf(" %[^\n]", aux->dato.responsable);
        printf(GREEN"Responsable asignado correctamente.\n"RESET);
    } else {
        printf(RED"Error: Activo no encontrado.\n"RESET);
    }
}