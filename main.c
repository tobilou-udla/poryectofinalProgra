#include <stdio.h>
#include "funciones.h"

int main() {
    // Arreglos para almacenar datos del sistema
    struct ZonaMonitoreo zonas[20];
    int numZonas = 0;
    int numAlertas = 0;

    struct ReporteActual reporte;

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
            case 8:
                printf("Saliendo del Sistema de Monitoreo de Contaminación del Aire.\n");
                break;
            case 7:
                if (cargarZonas(zonas, &numZonas)) {
                    printf("\n=== SELECCIONE UNA ZONA DE MONITOREO PARA INGRESAR EL REPORTE ACTUAL ===\n");
                    for (int i = 0; i < numZonas; i++) {
                        printf("%d. %s\n", i + 1, zonas[i].nombre);
                    }

                    int zonaId;
                    printf("Ingrese el ID de la zona para ingresar el reporte actual: ");
                    scanf("%d", &zonaId);

                    int zonaEncontrada = 0;
                    for (int i = 0; i < numZonas; i++) {
                        if (zonas[i].id == zonaId) {
                            ingresarDatosActuales(&zonas[i], 1);
                            guardarZonas(zonas, numZonas);
                            printf("Datos actuales ingresados y guardados correctamente en la zona %s.\n", zonas[i].nombre);
                            zonaEncontrada = 1;
                            break;
                        }
                    }

                    if (!zonaEncontrada) {
                        printf("No se encontró una zona con el ID especificado.\n");
                    }
                } else {
                    printf("No se pudieron cargar las zonas para ingresar datos actuales.\n");
                }
                break;
            default:
                printf("Opción no válida. Por favor, intente de nuevo.\n");
                break;
        }

    } while (opc != 8);
    
    return 0;
}
