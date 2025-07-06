#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"

// Umbrales críticos para contaminantes (basados en estándares internacionales)
#define UMBRAL_CO2_PRECAUCION 1000
#define UMBRAL_CO2_ALERTA 1500
#define UMBRAL_CO2_EMERGENCIA 2000

#define UMBRAL_SO2_PRECAUCION 80
#define UMBRAL_SO2_ALERTA 150
#define UMBRAL_SO2_EMERGENCIA 250

#define UMBRAL_NO2_PRECAUCION 100
#define UMBRAL_NO2_ALERTA 200
#define UMBRAL_NO2_EMERGENCIA 300

#define UMBRAL_PM25_PRECAUCION 25
#define UMBRAL_PM25_ALERTA 50
#define UMBRAL_PM25_EMERGENCIA 75

void crearZonasMonitoreo(){
    struct ZonaMonitoreo zonas[20];
    int numZonas = 5; // Crear 5 zonas de ejemplo

    // Zona 1: Centro Histórico
    zonas[0].id = 1;
    strcpy(zonas[0].nombre, "Centro Histórico");
    strcpy(zonas[0].ubicacion, "Plaza Principal, Quito");
    for (int i = 0; i < 14; i++) {
        zonas[0].contaminantes.co2[i] = 450.5 + i * 10;
        zonas[0].contaminantes.so2[i] = 25.3 + i * 2;
        zonas[0].contaminantes.no2[i] = 45.7 + i * 3;
        zonas[0].contaminantes.pm25[i] = 15.2 + i * 1;
        zonas[0].factoresClimaticos.temperatura[i] = 18.5 + i * 0.5;
        zonas[0].factoresClimaticos.humedad[i] = 65.0 - i * 1;
        zonas[0].factoresClimaticos.velocidadViento[i] = 8.2 + i * 0.2;
        strcpy(zonas[0].factoresClimaticos.direccionViento[i], "NE");
    }
    strcpy(zonas[0].fecha, "15/07/2025");
    strcpy(zonas[0].hora, "08:00:00");

    // Zona 2: Zona Industrial Norte
    zonas[1].id = 2;
    strcpy(zonas[1].nombre, "Zona Industrial Norte");
    strcpy(zonas[1].ubicacion, "Sector Industrial, Quito");
    for (int i = 0; i < 14; i++) {
        zonas[1].contaminantes.co2[i] = 850.7 + i * 15;
        zonas[1].contaminantes.so2[i] = 65.8 + i * 3;
        zonas[1].contaminantes.no2[i] = 125.4 + i * 5;
        zonas[1].contaminantes.pm25[i] = 35.6 + i * 2;
        zonas[1].factoresClimaticos.temperatura[i] = 20.1 - i * 0.3;
        zonas[1].factoresClimaticos.humedad[i] = 58.3 - i * 1;
        zonas[1].factoresClimaticos.velocidadViento[i] = 12.5 + i * 0.5;
        strcpy(zonas[1].factoresClimaticos.direccionViento[i], "SO");
    }
    strcpy(zonas[1].fecha, "15/07/2025");
    strcpy(zonas[1].hora, "10:30:00");

    // Zona 3: Zona Residencial Sur
    zonas[2].id = 3;
    strcpy(zonas[2].nombre, "Zona Residencial Sur");
    strcpy(zonas[2].ubicacion, "Sector Residencial, Quito");
    for (int i = 0; i < 14; i++) {
        zonas[2].contaminantes.co2[i] = 380.2 + i * 8;
        zonas[2].contaminantes.so2[i] = 18.9 + i * 1;
        zonas[2].contaminantes.no2[i] = 32.1 + i * 2;
        zonas[2].contaminantes.pm25[i] = 12.8 + i * 0.5;
        zonas[2].factoresClimaticos.temperatura[i] = 19.3 - i * 0.2;
        zonas[2].factoresClimaticos.humedad[i] = 70.2 - i * 1;
        zonas[2].factoresClimaticos.velocidadViento[i] = 6.8 + i * 0.3;
        strcpy(zonas[2].factoresClimaticos.direccionViento[i], "E");
    }
    strcpy(zonas[2].fecha, "15/07/2025");
    strcpy(zonas[2].hora, "09:00:00");

    // Zona 4: Aeropuerto
    zonas[3].id = 4;
    strcpy(zonas[3].nombre, "Aeropuerto");
    strcpy(zonas[3].ubicacion, "Aeropuerto Internacional, Quito");
    for (int i = 0; i < 14; i++) {
        zonas[3].contaminantes.co2[i] = 600.4 + i * 12;
        zonas[3].contaminantes.so2[i] = 30.5 + i * 1.5;
        zonas[3].contaminantes.no2[i] = 55.3 + i * 4;
        zonas[3].contaminantes.pm25[i] = 20.1 + i * 1;
        zonas[3].factoresClimaticos.temperatura[i] = 21.0 - i * 0.4;
        zonas[3].factoresClimaticos.humedad[i] = 60.0 - i * 0.5;
        zonas[3].factoresClimaticos.velocidadViento[i] = 10.0 + i * 0.4;
        strcpy(zonas[3].factoresClimaticos.direccionViento[i], "N");
    }
    strcpy(zonas[3].fecha, "15/07/2025");
    strcpy(zonas[3].hora, "08:30:00");
    
    // Zona 5: Parque Nacional
    zonas[4].id = 5;
    strcpy(zonas[4].nombre, "Parque Nacional");
    strcpy(zonas[4].ubicacion, "Parque Metropolitano, Quito");
    for (int i = 0; i < 14; i++) {
        zonas[4].contaminantes.co2[i] = 320.8 + i * 5;
        zonas[4].contaminantes.so2[i] = 12.1 + i * 0.5;
        zonas[4].contaminantes.no2[i] = 22.5 + i * 1;
        zonas[4].contaminantes.pm25[i] = 8.9 + i * 0.3;
        zonas[4].factoresClimaticos.temperatura[i] = 17.2 - i * 0.2;
        zonas[4].factoresClimaticos.humedad[i] = 75.5 - i * 0.3;
        zonas[4].factoresClimaticos.velocidadViento[i] = 5.3 + i * 0.1;
        strcpy(zonas[4].factoresClimaticos.direccionViento[i], "N");
    }
    strcpy(zonas[4].fecha, "15/07/2025");
    strcpy(zonas[4].hora, "09:00:00");
    
    guardarZonas(zonas, numZonas);
    printf("Zonas de monitoreo creadas y guardadas correctamente.\n");
}

void mostrarZonas(struct ZonaMonitoreo zonas[], int numZonas){
    printf("\n=== ZONAS DE MONITOREO ===\n");
    printf("============================================\n");
    for (int i = 0; i < numZonas; i++) {
        printf("\nZona ID: %d\n", zonas[i].id);
        printf("Nombre: %s\n", zonas[i].nombre);
        printf("Ubicación: %s\n", zonas[i].ubicacion);
        printf("Fecha: %s\n", zonas[i].fecha);
        printf("Hora: %s\n", zonas[i].hora);

        printf("\nContaminantes (últimos 14 días):\n");
        printf("------------------------------------------------------------\n");
        printf("| Día |   CO2   |   SO2   |   NO2   |  PM2.5  |\n");
        printf("------------------------------------------------------------\n");
        for (int j = 0; j < 14; j++) {
            printf("|  %2d | %7.2f | %7.2f | %7.2f | %7.2f |\n", j + 1, zonas[i].contaminantes.co2[j], zonas[i].contaminantes.so2[j], zonas[i].contaminantes.no2[j], zonas[i].contaminantes.pm25[j]);
        }
        printf("------------------------------------------------------------\n");

        printf("Factores Climáticos (últimos 14 días):\n");
        printf("---------------------------------------------------------------------\n");
        printf("| Día | Temperatura | Humedad | Vel. Viento | Dir. Viento |\n");
        printf("---------------------------------------------------------------------\n");
        for (int j = 0; j < 14; j++) {
            printf("|  %2d |   %7.2f   | %7.2f |   %7.2f   |   %s   |\n", j + 1, zonas[i].factoresClimaticos.temperatura[j], zonas[i].factoresClimaticos.humedad[j], zonas[i].factoresClimaticos.velocidadViento[j], zonas[i].factoresClimaticos.direccionViento[j]);
        }
        printf("---------------------------------------------------------------------\n");
    }
    if (numZonas == 0) {
        printf("No hay zonas de monitoreo disponibles.\n");
    }
}

void guardarZonas(struct ZonaMonitoreo zonas[], int numZonas){
    FILE *archivo = fopen("zonas_monitoreo.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar las zonas.\n");
        return;
    }
    fwrite(zonas, sizeof(struct ZonaMonitoreo), numZonas, archivo);
    fclose(archivo);
}

int cargarZonas(struct ZonaMonitoreo zonas[], int *numZonas){
    FILE *archivo = fopen("zonas_monitoreo.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para cargar las zonas.\n");
        return 0;
    }
    *numZonas = fread(zonas, sizeof(struct ZonaMonitoreo), 20, archivo);
    fclose(archivo);
    return 1;
}

void generarPrediccion(struct ZonaMonitoreo zonas[], int numZonas){
    printf("\n=== PREDICCIONES BASADAS EN PROMEDIOS ===\n");
    printf("========================================\n");
    for (int i = 0; i < numZonas; i++) {
        float promedioCO2 = 0, promedioSO2 = 0, promedioNO2 = 0, promedioPM25 = 0;
        for (int j = 0; j < 14; j++) {
            promedioCO2 += zonas[i].contaminantes.co2[j];
            promedioSO2 += zonas[i].contaminantes.so2[j];
            promedioNO2 += zonas[i].contaminantes.no2[j];
            promedioPM25 += zonas[i].contaminantes.pm25[j];
        }
        promedioCO2 /= 7;
        promedioSO2 /= 7;
        promedioNO2 /= 7;
        promedioPM25 /= 7;

        printf("Zona: %s\n", zonas[i].nombre);
        printf("Promedio CO2: %.2f ppm\n", promedioCO2);
        printf("Promedio SO2: %.2f µg/m³\n", promedioSO2);
        printf("Promedio NO2: %.2f µg/m³\n", promedioNO2);
        printf("Promedio PM2.5: %.2f µg/m³\n", promedioPM25);
        printf("----------------------------------------\n");
    }
}

void generarAlertas(struct ZonaMonitoreo zonas[], int numZonas){
    printf("\n=== ALERTAS GENERADAS ===\n");
    printf("========================================\n");
    for (int i = 0; i < numZonas; i++) {
        for (int j = 0; j < 14; j++) {
            if (zonas[i].contaminantes.co2[j] > UMBRAL_CO2_EMERGENCIA) {
                printf("EMERGENCIA: CO2 excede el umbral de emergencia en zona %s, día %d (%.2f ppm)\n", zonas[i].nombre, j + 1, zonas[i].contaminantes.co2[j]);
            } else if (zonas[i].contaminantes.co2[j] > UMBRAL_CO2_ALERTA) {
                printf("ALERTA: CO2 excede el umbral crítico en zona %s, día %d (%.2f ppm)\n", zonas[i].nombre, j + 1, zonas[i].contaminantes.co2[j]);
            } else if (zonas[i].contaminantes.co2[j] > UMBRAL_CO2_PRECAUCION) {
                printf("PRECAUCIÓN: CO2 excede el umbral de precaución en zona %s, día %d (%.2f ppm)\n", zonas[i].nombre, j + 1, zonas[i].contaminantes.co2[j]);
            }

            if (zonas[i].contaminantes.so2[j] > UMBRAL_SO2_EMERGENCIA) {
                printf("EMERGENCIA: SO2 excede el umbral de emergencia en zona %s, día %d (%.2f µg/m³)\n", zonas[i].nombre, j + 1, zonas[i].contaminantes.so2[j]);
            } else if (zonas[i].contaminantes.so2[j] > UMBRAL_SO2_ALERTA) {
                printf("ALERTA: SO2 excede el umbral crítico en zona %s, día %d (%.2f µg/m³)\n", zonas[i].nombre, j + 1, zonas[i].contaminantes.so2[j]);
            } else if (zonas[i].contaminantes.so2[j] > UMBRAL_SO2_PRECAUCION) {
                printf("PRECAUCIÓN: SO2 excede el umbral de precaución en zona %s, día %d (%.2f µg/m³)\n", zonas[i].nombre, j + 1, zonas[i].contaminantes.so2[j]);
            }

            if (zonas[i].contaminantes.no2[j] > UMBRAL_NO2_EMERGENCIA) {
                printf("EMERGENCIA: NO2 excede el umbral de emergencia en zona %s, día %d (%.2f µg/m³)\n", zonas[i].nombre, j + 1, zonas[i].contaminantes.no2[j]);
            } else if (zonas[i].contaminantes.no2[j] > UMBRAL_NO2_ALERTA) {
                printf("ALERTA: NO2 excede el umbral crítico en zona %s, día %d (%.2f µg/m³)\n", zonas[i].nombre, j + 1, zonas[i].contaminantes.no2[j]);
            } else if (zonas[i].contaminantes.no2[j] > UMBRAL_NO2_PRECAUCION) {
                printf("PRECAUCIÓN: NO2 excede el umbral de precaución en zona %s, día %d (%.2f µg/m³)\n", zonas[i].nombre, j + 1, zonas[i].contaminantes.no2[j]);
            }

            if (zonas[i].contaminantes.pm25[j] > UMBRAL_PM25_EMERGENCIA) {
                printf("EMERGENCIA: PM2.5 excede el umbral de emergencia en zona %s, día %d (%.2f µg/m³)\n", zonas[i].nombre, j + 1, zonas[i].contaminantes.pm25[j]);
            } else if (zonas[i].contaminantes.pm25[j] > UMBRAL_PM25_ALERTA) {
                printf("ALERTA: PM2.5 excede el umbral crítico en zona %s, día %d (%.2f µg/m³)\n", zonas[i].nombre, j + 1, zonas[i].contaminantes.pm25[j]);
            } else if (zonas[i].contaminantes.pm25[j] > UMBRAL_PM25_PRECAUCION) {
                printf("PRECAUCIÓN: PM2.5 excede el umbral de precaución en zona %s, día %d (%.2f µg/m³)\n", zonas[i].nombre, j + 1, zonas[i].contaminantes.pm25[j]);
            }
        }
        printf("----------------------------------------\n"); // Linea separadora entre zonas
    }
}

void generarRecomendaciones(struct ZonaMonitoreo zonas[], int numZonas) {
    printf("\n=== RECOMENDACIONES ===\n");
    for (int i = 0; i < numZonas; i++) {
        int recomendacionesGeneradas = 0;
        printf("Zona: %s\n", zonas[i].nombre);
        printf("Ubicación: %s\n", zonas[i].ubicacion);
        printf("Recomendaciones:\n");
        for (int j = 0; j < 14; j++) {
            if (zonas[i].contaminantes.co2[j] > UMBRAL_CO2_EMERGENCIA) {
                printf("- Evacuar la zona en el día %d debido a niveles críticos de CO2.\n", j + 1);
                recomendacionesGeneradas = 1;
            } else if (zonas[i].contaminantes.co2[j] > UMBRAL_CO2_ALERTA) {
                printf("- Reducir actividades industriales en el día %d.\n", j + 1);
                recomendacionesGeneradas = 1;
            } else if (zonas[i].contaminantes.co2[j] > UMBRAL_CO2_PRECAUCION) {
                printf("- Monitorear niveles de CO2 en el día %d.\n", j + 1);
                recomendacionesGeneradas = 1;
            }

            if (zonas[i].contaminantes.pm25[j] > UMBRAL_PM25_EMERGENCIA) {
                printf("- Evacuar la zona en el día %d debido a niveles críticos de PM2.5.\n", j + 1);
                recomendacionesGeneradas = 1;
            } else if (zonas[i].contaminantes.pm25[j] > UMBRAL_PM25_ALERTA) {
                printf("- Usar mascarillas en el día %d.\n", j + 1);
                recomendacionesGeneradas = 1;
            } else if (zonas[i].contaminantes.pm25[j] > UMBRAL_PM25_PRECAUCION) {
                printf("- Reducir actividades al aire libre en el día %d.\n", j + 1);
                recomendacionesGeneradas = 1;
            }
        }
        if (recomendacionesGeneradas == 0) {
            printf("Zona %s está perfecta, no se necesitan recomendaciones.\n", zonas[i].nombre);
        }
        printf("----------------------------------------\n");
    }
}

void exportarDatos(struct ZonaMonitoreo zonas[], int numZonas){
    FILE *archivo = fopen("reporte_contaminacion.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para exportar datos.\n");
        return;
    }

    fprintf(archivo, "\n=== REPORTE DE CONTAMINACIÓN ===\n");
    fprintf(archivo, "========================================\n");
    for (int i = 0; i < numZonas; i++) {
        fprintf(archivo, "\nZona: %s\n", zonas[i].nombre);
        fprintf(archivo, "Ubicación: %s\n", zonas[i].ubicacion);
        fprintf(archivo, "Fecha: %s\n", zonas[i].fecha);
        fprintf(archivo, "\nContaminantes (últimos 7 días):\n");
        fprintf(archivo, "----------------------------------------\n");
        fprintf(archivo, "| Día |   CO2   |   SO2   |   NO2   |  PM2.5  |\n");
        fprintf(archivo, "----------------------------------------\n");
        for (int j = 0; j < 14; j++) {
            fprintf(archivo, "|  %d  | %7.2f | %7.2f | %7.2f | %7.2f |\n", j + 1, zonas[i].contaminantes.co2[j], zonas[i].contaminantes.so2[j], zonas[i].contaminantes.no2[j], zonas[i].contaminantes.pm25[j]);
        }
        fprintf(archivo, "----------------------------------------\n");

        fprintf(archivo, "\nRecomendaciones:\n");
        for (int j = 0; j < 14; j++) {
            if (zonas[i].contaminantes.co2[j] > UMBRAL_CO2_EMERGENCIA) {
                fprintf(archivo, "- Evacuar la zona en el día %d debido a niveles críticos de CO2.\n", j + 1);
            } else if (zonas[i].contaminantes.co2[j] > UMBRAL_CO2_ALERTA) {
                fprintf(archivo, "- Reducir actividades industriales en el día %d.\n", j + 1);
            } else if (zonas[i].contaminantes.co2[j] > UMBRAL_CO2_PRECAUCION) {
                fprintf(archivo, "- Monitorear niveles de CO2 en el día %d.\n", j + 1);
            }

            if (zonas[i].contaminantes.pm25[j] > UMBRAL_PM25_EMERGENCIA) {
                fprintf(archivo, "- Evacuar la zona en el día %d debido a niveles críticos de PM2.5.\n", j + 1);
            } else if (zonas[i].contaminantes.pm25[j] > UMBRAL_PM25_ALERTA) {
                fprintf(archivo, "- Usar mascarillas en el día %d.\n", j + 1);
            } else if (zonas[i].contaminantes.pm25[j] > UMBRAL_PM25_PRECAUCION) {
                fprintf(archivo, "- Reducir actividades al aire libre en el día %d.\n", j + 1);
            }
        }
        fprintf(archivo, "\nAlertas:\n");
        for (int j = 0; j < 14; j++) {
            if (zonas[i].contaminantes.co2[j] > UMBRAL_CO2_EMERGENCIA) {
                fprintf(archivo, "EMERGENCIA: CO2 excede el umbral de emergencia en el día %d (%.2f ppm)\n", j + 1, zonas[i].contaminantes.co2[j]);
            } else if (zonas[i].contaminantes.co2[j] > UMBRAL_CO2_ALERTA) {
                fprintf(archivo, "ALERTA: CO2 excede el umbral crítico en el día %d (%.2f ppm)\n", j + 1, zonas[i].contaminantes.co2[j]);
            } else if (zonas[i].contaminantes.co2[j] > UMBRAL_CO2_PRECAUCION) {
                fprintf(archivo, "PRECAUCION: CO2 excede el umbral de precaución en el día %d (%.2f ppm)\n", j + 1, zonas[i].contaminantes.co2[j]);
            }

            if (zonas[i].contaminantes.pm25[j] > UMBRAL_PM25_EMERGENCIA) {
                fprintf(archivo, "EMERGENCIA: PM2.5 excede el umbral de emergencia en el día %d (%.2f µg/m³)\n", j + 1, zonas[i].contaminantes.pm25[j]);
            } else if (zonas[i].contaminantes.pm25[j] > UMBRAL_PM25_ALERTA) {
                fprintf(archivo, "ALERTA: PM2.5 excede el umbral crítico en el día %d (%.2f µg/m³)\n", j + 1, zonas[i].contaminantes.pm25[j]);
            } else if (zonas[i].contaminantes.pm25[j] > UMBRAL_PM25_PRECAUCION) {
                fprintf(archivo, "PRECAUCION: PM2.5 excede el umbral de precaución en el día %d (%.2f µg/m³)\n", j + 1, zonas[i].contaminantes.pm25[j]);
            }
        }
        fprintf(archivo, "----------------------------------------\n");
    }

    fclose(archivo);
    printf("Datos exportados correctamente a reporte_contaminacion.txt\n");
}

int menu(){
    int opc;
    printf("\n========================================\n");
    printf("  SISTEMA DE MONITOREO DE CONTAMINACIÓN\n");
    printf("========================================\n");
    printf("1. Crear Zonas de Monitoreo\n");
    printf("2. Mostrar Zonas de Monitoreo\n");
    printf("3. Generar Predicciones\n");
    printf("4. Generar Alertas\n");
    printf("5. Generar Reporte Completo\n");
    printf("6. Exportar Datos\n");
    printf("7. Salir\n");
    printf("========================================\n");
    printf("Seleccione una opción: ");
    scanf("%d", &opc);
    fflush(stdin);
    return opc;
}
