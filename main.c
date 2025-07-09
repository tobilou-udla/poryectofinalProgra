#include <stdio.h>
#include "funciones.h"

int main() {
    // Arreglos para almacenar datos del sistema
    struct ZonaMonitoreo zonas[20];
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
            case 8:
                printf("Saliendo del Sistema de Monitoreo de Contaminación del Aire.\n");
                break;
            case 7:
                if(cargarZonas(zonas, &numZonas)) {
                    int zonaId;
                    float co2, so2, no2, pm25, temperatura, humedad, velocidadViento;
                    char direccionViento[10], fecha[20], hora[10];

                    printf("Ingrese el ID de la zona para agregar el reporte: ");
                    scanf("%d", &zonaId);

                    printf("Ingrese los datos del reporte:\n");
                    printf("CO2 (ppm): ");
                    scanf("%f", &co2);
                    printf("SO2 (µg/m³): ");
                    scanf("%f", &so2);
                    printf("NO2 (µg/m³): ");
                    scanf("%f", &no2);
                    printf("PM2.5 (µg/m³): ");
                    scanf("%f", &pm25);
                    printf("Temperatura (°C): ");
                    scanf("%f", &temperatura);
                    printf("Humedad (%): ");
                    scanf("%f", &humedad);
                    printf("Velocidad del viento (km/h): ");
                    scanf("%f", &velocidadViento);
                    printf("Dirección del viento: ");
                    scanf("%s", direccionViento);
                    obtenerFechaHora(fecha, hora);

                    for (int i = 0; i < numZonas; i++) {
                        if (zonas[i].id == zonaId) {
                            agregarReporte(&zonas[i], co2, so2, no2, pm25, temperatura, humedad, velocidadViento, direccionViento, fecha, hora);
                            printf("Reporte agregado correctamente a la zona %s.\n", zonas[i].nombre);
                            break;
                        }
                    }
                } else {
                    printf("No se pudieron cargar las zonas para agregar un reporte.\n");
                }
                break;
            default:
                printf("Opción no válida. Por favor, intente de nuevo.\n");
                break;
        }

    } while (opc != 7);
    
    return 0;
}
