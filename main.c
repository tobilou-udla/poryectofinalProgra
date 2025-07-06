#include <stdio.h>
#include "funciones.h"

int main() {
    // Arreglos para almacenar datos del sistema
    struct ZonaMonitoreo zonas[20];
    struct Alerta alertas[100];
    int numZonas = 0;
    int numAlertas = 0;

    int opc;
    do {
        opc = menu();
        switch (opc)
        {
            case 1:
                crearZonasMonitoreo();
                printf("Zonas de monitoreo creadas correctamente.\n");
                break;
            case 2:
                if(cargarZonas(zonas, &numZonas)) {
                    mostrarZonas(zonas, numZonas);
                } else {
                    printf("No se pudieron cargar las zonas de monitoreo.\n");
                }
                break;
            case 3:
                if(cargarZonas(zonas, &numZonas)) {
                    generarPrediccion(zonas, numZonas);
                } else {
                    printf("No se pudieron cargar las zonas para generar predicciones.\n");
                }
                break;
            case 4:
                if(cargarZonas(zonas, &numZonas)) {
                    generarAlertas(zonas, numZonas);
                } else {
                    printf("No se pudieron cargar las zonas para generar alertas.\n");
                }
                break;
            case 5:
                if(cargarZonas(zonas, &numZonas)) {
                    generarRecomendaciones(zonas, numZonas);
                } else {
                    printf("No se pudieron cargar las zonas para generar recomendaciones.\n");
                }
                break;
            case 6:
                if(cargarZonas(zonas, &numZonas)) {
                    exportarDatos(zonas, numZonas);
                } else {
                    printf("No se pudieron cargar las zonas para exportar.\n");
                }
                break;
            case 7:
                printf("Saliendo del Sistema de Monitoreo de Contaminación del Aire.\n");
                break;
            default:
                printf("Opción no válida. Por favor, intente de nuevo.\n");
                break;
        }

    } while (opc != 7);
    
    return 0;
}
