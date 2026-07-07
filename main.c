#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "activos.h"
#include "inventario.h"
#include "colors.h"

// Prototipos de E/S y búsquedas locales
void buscarActivoMain(Nodo *cab);
void guardarEnArchivo(Nodo *cab);
void cargarDesdeArchivo(Nodo **cab);

int main() {
    Nodo *lista = NULL;
    int op;

    // Carga inicial persistente al arrancar la aplicación
    cargarDesdeArchivo(&lista);

    do {
        printf(BG_WHITE"\n===== TECHSOLUTIONS S.A. - GESTION DE ACTIVOS TI ====="RESET"\n");
        printf(YELLOW"1. Registrar activo\n");
        printf("2. Buscar activo por codigo\n");
        printf("3. Actualizar responsable\n");
        printf("4. Dar de baja activo\n");
        printf("5. Mostrar inventario completo\n");
        printf("6. Mostrar activos por departamento\n");
        printf("0. Salir del Sistema\n");
        printf("Opcion: "RESET);
        scanf("%d", &op);

        switch(op) {
            case 1: 
                registrarActivo(&lista); 
                guardarEnArchivo(lista);
                break;
            case 2: 
                buscarActivoMain(lista); 
                break;
            case 3: 
                actualizarResponsable(lista); 
                guardarEnArchivo(lista);
                break;
            case 4: 
                darDeBajaActivo(&lista); 
                guardarEnArchivo(lista);
                break;
            case 5: 
                mostrarInventarioCompleto(lista); 
                break;
            case 6: 
                mostrarActivosPorDepartamento(lista); 
                break;
        }

    } while(op != 0);

    // Persistencia final y prevención de fugas de memoria (Free)
    guardarEnArchivo(lista);
    liberarLista(&lista);

    return 0;
}

// ================= FUNCIONES DE PERSISTENCIA (FILE I/O) =================

void cargarDesdeArchivo(Nodo **cab) {
    FILE *archivo = fopen("activos.txt", "r");
    if (archivo == NULL) return; // Retorna si el archivo aún no se ha creado
    
    Activo a;
    // Formato delimitado por comas para evitar conflictos con cadenas compuestas
    while (fscanf(archivo, "%d,%[^,],%[^,],%[^,],%[^,],%[^\n]\n", &a.codigo, a.nombre, a.tipo, a.departamento, a.responsable, a.estado) != EOF) {
        insertarFinal(cab, a);
    }
    fclose(archivo);
}

void guardarEnArchivo(Nodo *cab) {
    FILE *archivo = fopen("activos.txt", "w");
    if (archivo == NULL) {
        printf(RED"Critical Error: No se pudo escribir en activos.txt\n"RESET);
        return;
    }

    Nodo *aux = cab;
    while(aux != NULL) {
        fprintf(archivo, "%d,%s,%s,%s,%s,%s\n",
            aux->dato.codigo,
            aux->dato.nombre,
            aux->dato.tipo,
            aux->dato.departamento,
            aux->dato.responsable,
            aux->dato.estado);
        aux = aux->sig;
    }

    fclose(archivo);
}

// ================= PROCESO DE BÚSQUEDA DETALLADA =================

void buscarActivoMain(Nodo *cab) {
    int codigo;

    printf(BLUE"Codigo del activo a buscar: "RESET);
    scanf("%d", &codigo);

    Nodo *aux = buscarPorCodigo(cab, codigo);
    if(aux != NULL) {
        printf(GREEN"\n=== FICHA TECNICA DEL ACTIVO ===\n"RESET);
        printf(BLUE"Codigo:        "RESET"%d\n", aux->dato.codigo);
        printf(BLUE"Nombre:        "RESET"%s\n", aux->dato.nombre);
        printf(BLUE"Tipo:          "RESET"%s\n", aux->dato.tipo);
        printf(BLUE"Departamento:  "RESET"%s\n", aux->dato.departamento);
        printf(BLUE"Responsable:   "RESET"%s\n", aux->dato.responsable);
        printf(BLUE"Estado actual: "RESET"%s\n", aux->dato.estado);
    } else {
        printf(RED"El codigo especificado no coincide con ningun activo.\n"RESET);
    }
}