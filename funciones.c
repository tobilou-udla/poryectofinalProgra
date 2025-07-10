#include <stdio.h>
#include <string.h>
#include <time.h>
#include "funciones.h"

// Umbrales críticos para contaminantes (basados en estándares internacionales)
#define UMBRAL_CO2_PRECAUCION 1000
#define UMBRAL_CO2_ALERTA 5000
#define UMBRAL_CO2_EMERGENCIA 30000

#define UMBRAL_SO2_PRECAUCION 35
#define UMBRAL_SO2_ALERTA 40
#define UMBRAL_SO2_EMERGENCIA 75

#define UMBRAL_NO2_PRECAUCION 10
#define UMBRAL_NO2_ALERTA 25
#define UMBRAL_NO2_EMERGENCIA 200

#define UMBRAL_PM25_PRECAUCION 10
#define UMBRAL_PM25_ALERTA 25
#define UMBRAL_PM25_EMERGENCIA 35

// Declare a global variable for the number of records
int numRegistros = 30;

void crearZonasMonitoreo(){
    struct ZonaMonitoreo zonas[20];
    int numZonas = 5; // Crear 5 zonas de ejemplo

    for (int z = 0; z < numZonas; z++) {
        zonas[z].id = z + 1;
        sprintf(zonas[z].nombre, "Zona %d", z + 1);
        sprintf(zonas[z].ubicacion, "Ubicación %d", z + 1);

        for (int i = 0; i < numRegistros; i++) {
            zonas[z].contaminantes.co2[i] = 850 + i * 1.1 + z * 10; // Variación por zona
            zonas[z].contaminantes.so2[i] = 20 + i * 0.5 + z * 2; // Variación por zona
            zonas[z].contaminantes.no2[i] = 10 + i * 0.5 + z * 1.5; // Variación por zona
            zonas[z].contaminantes.pm25[i] = 5 + i * 0.1 + z * 0.5; // Variación por zona
            zonas[z].factoresClimaticos.temperatura[i] = 18 + i * 0.5 + z * 0.3; // Variación por zona
            zonas[z].factoresClimaticos.humedad[i] = 70 - i * 1 - z * 0.5; // Variación por zona
            zonas[z].factoresClimaticos.velocidadViento[i] = 9 + i * 0.2 + z * 0.1; // Variación por zona
            zonas[z].factoresClimaticos.direccionViento[i] = 10 + i * 0.1 + z * 0.2; // Variación por zona

            // Calcular la fecha y hora correspondiente
            struct tm fechaBase = {0};
            fechaBase.tm_year = 2025 - 1900;
            fechaBase.tm_mon = 6; // Julio (0-indexed)
            fechaBase.tm_mday = 9 - i; // Ajustar para que la fecha sea dinámica
            mktime(&fechaBase);

            sprintf(zonas[z].fecha[i], "%02d/%02d/%04d", fechaBase.tm_mday, fechaBase.tm_mon + 1, fechaBase.tm_year + 1900);
            sprintf(zonas[z].hora[i], "08:%02d:00", i); // Ejemplo de hora dinámica
        }
    }

    guardarZonas(zonas, numZonas);
    printf("Zonas de monitoreo creadas y guardadas correctamente.\n");
}

void mostrarZonas(struct ZonaMonitoreo zonas[], int numZonas) {
    if (numZonas == 0) {
        printf("No hay zonas de monitoreo disponibles.\n");
        return;
    }

    printf("\n=== SELECCIONE UNA ZONA DE MONITOREO ===\n");
    for (int i = 0; i < numZonas; i++) {
        printf("%d. %s\n", i + 1, zonas[i].nombre);
    }

    int seleccion;
    printf("Ingrese el número de la zona que desea ver: ");
    scanf("%d", &seleccion);

    if (seleccion < 1 || seleccion > numZonas) {
        printf("Selección inválida.\n");
        return;
    }

    struct ZonaMonitoreo zonaSeleccionada = zonas[seleccion - 1];

    printf("\n=== REGISTROS DE LA ZONA: %s ===\n", zonaSeleccionada.nombre);
    printf("Ubicación: %s\n", zonaSeleccionada.ubicacion);
    printf("Fecha: %s\n", zonaSeleccionada.fecha);
    printf("Hora: %s\n", zonaSeleccionada.hora);

    printf("\nContaminantes (últimos 30 días):\n");
    printf("------------------------------------------------------------\n");
    printf("| Fecha       |   CO2   |   SO2   |   NO2   |  PM2.5  |\n");
    printf("------------------------------------------------------------\n");

    for (int j = 0; j < numRegistros; j++) {
        printf("| %s | %7.2f | %7.2f | %7.2f | %7.2f |\n", zonaSeleccionada.fecha[j], zonaSeleccionada.contaminantes.co2[j], zonaSeleccionada.contaminantes.so2[j], zonaSeleccionada.contaminantes.no2[j], zonaSeleccionada.contaminantes.pm25[j]);
    }
    printf("------------------------------------------------------------\n");

    printf("Factores Climáticos (últimos 30 días):\n");
    printf("---------------------------------------------------------------------\n");
    printf("| Fecha       | Temperatura | Humedad | Vel. Viento | Dir. Viento |\n");
    printf("---------------------------------------------------------------------\n");

    for (int j = 0; j < numRegistros; j++) {
        printf("| %s |   %7.2f   | %7.2f |   %7.2f   |   %7.2f   |\n", zonaSeleccionada.fecha[j], zonaSeleccionada.factoresClimaticos.temperatura[j], zonaSeleccionada.factoresClimaticos.humedad[j], zonaSeleccionada.factoresClimaticos.velocidadViento[j], zonaSeleccionada.factoresClimaticos.direccionViento[j]);
    }
    printf("---------------------------------------------------------------------\n");
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

float promedioPonderado(float valores[], int numRegistros) {
    float suma = 0, totalPesos = 0;
    for (int i = 0; i < numRegistros; i++) {
        int peso = numRegistros - i;
        suma += valores[i] * peso;
        totalPesos += peso;
    }
    return suma / totalPesos;
}

float promedio(float valores[], int numRegistros) {
    float suma = 0;
    for (int i = 0; i < numRegistros; i++) {
        suma += valores[i];
    }
    return suma / numRegistros;
}

void generarPrediccion(struct ZonaMonitoreo zonas[], int numZonas) {
    if (numZonas == 0) {
        printf("No hay zonas de monitoreo disponibles para generar predicciones.\n");
        return;
    }

    printf("\n=== SELECCIONE UNA ZONA DE MONITOREO PARA VER PREDICCIONES ===\n");
    for (int i = 0; i < numZonas; i++) {
        printf("%d. %s\n", i + 1, zonas[i].nombre);
    }

    int seleccion;
    printf("Ingrese el número de la zona que desea ver: ");
    scanf("%d", &seleccion);

    if (seleccion < 1 || seleccion > numZonas) {
        printf("Selección inválida.\n");
        return;
    }

    struct ZonaMonitoreo zonaSeleccionada = zonas[seleccion - 1];

    printf("\n=== PREDICCIONES BASADAS EN PROMEDIOS PONDERADOS PARA LA ZONA: %s ===\n", zonaSeleccionada.nombre);
    float co2Predicho = promedioPonderado(zonaSeleccionada.contaminantes.co2, numRegistros);
    float so2Predicho = promedioPonderado(zonaSeleccionada.contaminantes.so2, numRegistros);
    float no2Predicho = promedioPonderado(zonaSeleccionada.contaminantes.no2, numRegistros);
    float pm25Predicho = promedioPonderado(zonaSeleccionada.contaminantes.pm25, numRegistros);

    printf("CO2: %.2f ppm | SO2: %.2f µg/m³ | NO2: %.2f µg/m³ | PM2.5: %.2f µg/m³\n",
           co2Predicho, so2Predicho, no2Predicho, pm25Predicho);
}

void generarAlertas(struct ZonaMonitoreo zonas[], int numZonas) {
    if (numZonas == 0) {
        printf("No hay zonas de monitoreo disponibles.\n");
        return;
    }

    printf("\n=== SELECCIONE UNA ZONA DE MONITOREO PARA VER ALERTAS ===\n");
    for (int i = 0; i < numZonas; i++) {
        printf("%d. %s\n", i + 1, zonas[i].nombre);
    }

    int seleccion;
    printf("Ingrese el número de la zona que desea ver: ");
    scanf("%d", &seleccion);

    if (seleccion < 1 || seleccion > numZonas) {
        printf("Selección inválida.\n");
        return;
    }

    struct ZonaMonitoreo zonaSeleccionada = zonas[seleccion - 1];
    struct ReporteActual reporte = zonaSeleccionada.reporteActual;

    printf("\n=== ALERTAS PARA LA ZONA: %s ===\n", zonaSeleccionada.nombre);
    if (reporte.co2 > UMBRAL_CO2_EMERGENCIA) {
        printf("EMERGENCIA: CO2 excede el umbral de emergencia (%.2f ppm)\n", reporte.co2);
    } else if (reporte.co2 > UMBRAL_CO2_ALERTA) {
        printf("ALERTA: CO2 excede el umbral crítico (%.2f ppm)\n", reporte.co2);
    } else if (reporte.co2 > UMBRAL_CO2_PRECAUCION) {
        printf("PRECAUCION: CO2 excede el umbral de precaución (%.2f ppm)\n", reporte.co2);
    }

    if (reporte.pm25 > UMBRAL_PM25_EMERGENCIA) {
        printf("EMERGENCIA: PM2.5 excede el umbral de emergencia (%.2f µg/m³)\n", reporte.pm25);
    } else if (reporte.pm25 > UMBRAL_PM25_ALERTA) {
        printf("ALERTA: PM2.5 excede el umbral crítico (%.2f µg/m³)\n", reporte.pm25);
    } else if (reporte.pm25 > UMBRAL_PM25_PRECAUCION) {
        printf("PRECAUCION: PM2.5 excede el umbral de precaución (%.2f µg/m³)\n", reporte.pm25);
    }
}

void generarRecomendaciones(struct ZonaMonitoreo zonas[], int numZonas) {
    if (numZonas == 0) {
        printf("No hay zonas de monitoreo disponibles.\n");
        return;
    }

    printf("\n=== SELECCIONE UNA ZONA DE MONITOREO PARA VER RECOMENDACIONES ===\n");
    for (int i = 0; i < numZonas; i++) {
        printf("%d. %s\n", i + 1, zonas[i].nombre);
    }

    int seleccion;
    printf("Ingrese el número de la zona que desea ver: ");
    scanf("%d", &seleccion);

    if (seleccion < 1 || seleccion > numZonas) {
        printf("Selección inválida.\n");
        return;
    }

    struct ZonaMonitoreo zonaSeleccionada = zonas[seleccion - 1];
    struct ReporteActual reporte = zonaSeleccionada.reporteActual;

    printf("\n=== RECOMENDACIONES PARA LA ZONA: %s ===\n", zonaSeleccionada.nombre);
    if (reporte.co2 > UMBRAL_CO2_EMERGENCIA) {
        printf("Evacuar debido a niveles críticos de CO2.\n");
    } else if (reporte.co2 > UMBRAL_CO2_ALERTA) {
        printf("Reducir actividades industriales.\n");
    } else if (reporte.co2 > UMBRAL_CO2_PRECAUCION) {
        printf("Monitorear niveles de CO2.\n");
    }

    if (reporte.pm25 > UMBRAL_PM25_EMERGENCIA) {
        printf("Evacuar debido a niveles críticos de PM2.5.\n");
    } else if (reporte.pm25 > UMBRAL_PM25_ALERTA) {
        printf("Usar mascarillas.\n");
    } else if (reporte.pm25 > UMBRAL_PM25_PRECAUCION) {
        printf("Reducir actividades al aire libre.\n");
    }
}

void calcularPromedios(struct ZonaMonitoreo *zona, float *promedioCO2, float *promedioSO2, float *promedioNO2, float *promedioPM25, float *promedioTemperatura, float *promedioHumedad, float *promedioVelocidadViento) {
    float sumaCO2 = 0, sumaSO2 = 0, sumaNO2 = 0, sumaPM25 = 0;
    float sumaTemperatura = 0, sumaHumedad = 0, sumaVelocidadViento = 0;

    for (int i = 0; i < numRegistros; i++) {
        sumaCO2 += zona->contaminantes.co2[i];
        sumaSO2 += zona->contaminantes.so2[i];
        sumaNO2 += zona->contaminantes.no2[i];
        sumaPM25 += zona->contaminantes.pm25[i];
        sumaTemperatura += zona->factoresClimaticos.temperatura[i];
        sumaHumedad += zona->factoresClimaticos.humedad[i];
        sumaVelocidadViento += zona->factoresClimaticos.velocidadViento[i];
    }

    *promedioCO2 = sumaCO2 / numRegistros;
    *promedioSO2 = sumaSO2 / numRegistros;
    *promedioNO2 = sumaNO2 / numRegistros;
    *promedioPM25 = sumaPM25 / numRegistros;
    *promedioTemperatura = sumaTemperatura / numRegistros;
    *promedioHumedad = sumaHumedad / numRegistros;
    *promedioVelocidadViento = sumaVelocidadViento / numRegistros;
}

void generarRecomendacionesCompletas(struct ZonaMonitoreo zonas[], int numZonas) {
    printf("\n=== RECOMENDACIONES ===\n");
    for (int i = 0; i < numZonas; i++) {
        int recomendacionesGeneradas = 0;
        printf("Zona: %s\n", zonas[i].nombre);
        printf("Ubicación: %s\n", zonas[i].ubicacion);
        printf("Recomendaciones:\n");
        for (int j = 0; j < numRegistros; j++) {
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

void exportarDatos(struct ZonaMonitoreo zonas[], int numZonas) {
    if (numZonas == 0) {
        printf("No hay zonas de monitoreo disponibles para exportar.");
        return;
    }

    printf("\n=== SELECCIONE UNA ZONA DE MONITOREO PARA EXPORTAR DATOS ===\n");
    for (int i = 0; i < numZonas; i++) {
        printf("%d. %s\n", i + 1, zonas[i].nombre);
    }

    int seleccion;
    printf("Ingrese el número de la zona que desea exportar: ");
    scanf("%d", &seleccion);

    if (seleccion < 1 || seleccion > numZonas) {
        printf("Selección inválida.\n");
        return;
    }

    struct ZonaMonitoreo zonaSeleccionada = zonas[seleccion - 1];

    char nombreArchivo[100];
    sprintf(nombreArchivo, "reporte_contaminacion_zona_%d.txt", zonaSeleccionada.id);

    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para exportar los datos.\n");
        return;
    }

    char fecha[20], hora[10];
    obtenerFechaHora(fecha, hora);

    fprintf(archivo, "Fecha del reporte: %s\n", fecha);
    fprintf(archivo, "Hora del reporte: %s\n", hora);

    fprintf(archivo, "\n=== REPORTE DE CONTAMINACIÓN ===\n");
    fprintf(archivo, "Zona: %s\n", zonaSeleccionada.nombre);
    fprintf(archivo, "Ubicación: %s\n", zonaSeleccionada.ubicacion);

    fprintf(archivo, "\nDatos actuales registrados:\n");
    fprintf(archivo, "CO2: %.2f ppm | SO2: %.2f µg/m³ | NO2: %.2f µg/m³ | PM2.5: %.2f µg/m³\n", 
            zonaSeleccionada.reporteActual.co2, zonaSeleccionada.reporteActual.so2, 
            zonaSeleccionada.reporteActual.no2, zonaSeleccionada.reporteActual.pm25);
    fprintf(archivo, "Temperatura: %.2f °C | Humedad: %.2f %% | Vel. Viento: %.2f km/h | Dir. Viento: %.2f°\n", 
            zonaSeleccionada.reporteActual.temperatura, zonaSeleccionada.reporteActual.humedad, 
            zonaSeleccionada.reporteActual.velocidadViento, zonaSeleccionada.reporteActual.direccionViento);

    fprintf(archivo, "\nPromedio histórico:\n");
    fprintf(archivo, "CO2: %.2f ppm | SO2: %.2f µg/m³ | NO2: %.2f µg/m³ | PM2.5: %.2f µg/m³\n",
            promedio(zonaSeleccionada.contaminantes.co2, numRegistros),
            promedio(zonaSeleccionada.contaminantes.so2, numRegistros),
            promedio(zonaSeleccionada.contaminantes.no2, numRegistros),
            promedio(zonaSeleccionada.contaminantes.pm25, numRegistros));

    fprintf(archivo, "\nPredicción:\n");
    fprintf(archivo, "CO2: %.2f ppm | SO2: %.2f µg/m³ | NO2: %.2f µg/m³ | PM2.5: %.2f µg/m³\n",
            promedioPonderado(zonaSeleccionada.contaminantes.co2, numRegistros),
            promedioPonderado(zonaSeleccionada.contaminantes.so2, numRegistros),
            promedioPonderado(zonaSeleccionada.contaminantes.no2, numRegistros),
            promedioPonderado(zonaSeleccionada.contaminantes.pm25, numRegistros));

    fprintf(archivo, "\nAlertas:\n");
    if (zonaSeleccionada.reporteActual.co2 > UMBRAL_CO2_EMERGENCIA) {
        fprintf(archivo, "EMERGENCIA: CO2 excede el umbral de emergencia (%.2f ppm)\n", zonaSeleccionada.reporteActual.co2);
    } else if (zonaSeleccionada.reporteActual.co2 > UMBRAL_CO2_ALERTA) {
        fprintf(archivo, "ALERTA: CO2 excede el umbral crítico (%.2f ppm)\n", zonaSeleccionada.reporteActual.co2);
    } else if (zonaSeleccionada.reporteActual.co2 > UMBRAL_CO2_PRECAUCION) {
        fprintf(archivo, "PRECAUCION: CO2 excede el umbral de precaución (%.2f ppm)\n", zonaSeleccionada.reporteActual.co2);
    }

    if (zonaSeleccionada.reporteActual.pm25 > UMBRAL_PM25_EMERGENCIA) {
        fprintf(archivo, "EMERGENCIA: PM2.5 excede el umbral de emergencia (%.2f µg/m³)\n", zonaSeleccionada.reporteActual.pm25);
    } else if (zonaSeleccionada.reporteActual.pm25 > UMBRAL_PM25_ALERTA) {
        fprintf(archivo, "ALERTA: PM2.5 excede el umbral crítico (%.2f µg/m³)\n", zonaSeleccionada.reporteActual.pm25);
    } else if (zonaSeleccionada.reporteActual.pm25 > UMBRAL_PM25_PRECAUCION) {
        fprintf(archivo, "PRECAUCION: PM2.5 excede el umbral de precaución (%.2f µg/m³)\n", zonaSeleccionada.reporteActual.pm25);
    }

    fprintf(archivo, "\nRecomendaciones:\n");
    if (zonaSeleccionada.reporteActual.co2 > UMBRAL_CO2_EMERGENCIA) {
        fprintf(archivo, "Evacuar debido a niveles críticos de CO2.\n");
    } else if (zonaSeleccionada.reporteActual.co2 > UMBRAL_CO2_ALERTA) {
        fprintf(archivo, "Reducir actividades industriales.\n");
    } else if (zonaSeleccionada.reporteActual.co2 > UMBRAL_CO2_PRECAUCION) {
        fprintf(archivo, "Monitorear niveles de CO2 regularmente.\n");
    }

    if (zonaSeleccionada.reporteActual.pm25 > UMBRAL_PM25_EMERGENCIA) {
        fprintf(archivo, "Evacuar debido a niveles críticos de PM2.5.\n");
    } else if (zonaSeleccionada.reporteActual.pm25 > UMBRAL_PM25_ALERTA) {
        fprintf(archivo, "Usar mascarillas.\n");
    } else if (zonaSeleccionada.reporteActual.pm25 > UMBRAL_PM25_PRECAUCION) {
        fprintf(archivo, "Evitar actividades al aire libre.\n");
    }

    fclose(archivo);
    printf("Datos exportados correctamente a %s\n", nombreArchivo);
}

int menu(){
    int opc;
    printf("\n========================================\n");
    printf("  SISTEMA DE MONITOREO DE CONTAMINACIÓN\n");
    printf("========================================\n");
    printf("1. Crear Zonas de Monitoreo\n");
    printf("2. Mostrar Zonas de Monitoreo\n");
    printf("3. Generar Predicciones (24h)\n");
    printf("4. Generar Alertas\n");
    printf("5. Generar Recomendaciones\n");
    printf("6. Exportar Datos\n");
    printf("7. Agregar Reporte actual\n");
    printf("8. Salir\n");
    printf("========================================\n");
    printf("Seleccione una opción: ");
    scanf("%d", &opc);
    fflush(stdin);
    return opc;
}

void obtenerFechaHora(char *fecha, char *hora) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Formatear la fecha como DD/MM/YYYY
    sprintf(fecha, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // Formatear la hora como HH:MM:SS
    sprintf(hora, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void ingresarDatosActuales(struct ZonaMonitoreo zonas[], int numZonas) {
    for (int i = 0; i < numZonas; i++) {
        printf("\n--- %s ---\n", zonas[i].nombre);
        zonas[i].reporteActual.co2 = pedirFlotanteValido("Ingrese CO2 actual: ");
        zonas[i].reporteActual.so2 = pedirFlotanteValido("Ingrese SO2 actual: ");
        zonas[i].reporteActual.no2 = pedirFlotanteValido("Ingrese NO2 actual: ");
        zonas[i].reporteActual.pm25 = pedirFlotanteValido("Ingrese PM2.5 actual: ");
        zonas[i].reporteActual.temperatura = pedirFlotanteValido("Temperatura (°C): ");
        zonas[i].reporteActual.velocidadViento = pedirFlotanteValido("Viento (km/h): ");
        zonas[i].reporteActual.humedad = pedirFlotanteValido("Humedad (%): ");

        for (int j = 29; j > 0; j--) {
            zonas[i].contaminantes.co2[j] = zonas[i].contaminantes.co2[j - 1];
            zonas[i].contaminantes.so2[j] = zonas[i].contaminantes.so2[j - 1];
            zonas[i].contaminantes.no2[j] = zonas[i].contaminantes.no2[j - 1];
            zonas[i].contaminantes.pm25[j] = zonas[i].contaminantes.pm25[j - 1];
        }

        zonas[i].contaminantes.co2[0] = zonas[i].reporteActual.co2;
        zonas[i].contaminantes.so2[0] = zonas[i].reporteActual.so2;
        zonas[i].contaminantes.no2[0] = zonas[i].reporteActual.no2;
        zonas[i].contaminantes.pm25[0] = zonas[i].reporteActual.pm25;
    }
}

float pedirFlotanteValido(const char *mensaje) {
    float valor;
    int valido;
    do {
        printf("%s", mensaje);
        valido = scanf("%f", &valor);
        fflush(stdin);
        if (valido != 1) {
            printf("Entrada inválida. Por favor, ingrese un número válido.\n");
        }
    } while (valido != 1);
    return valor;
}
