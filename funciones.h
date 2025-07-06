// Estructura para almacenar datos de contaminantes
struct Contaminante
{
    float co2[14];      // Dióxido de carbono (ppm)
    float so2[14];      // Dióxido de azufre (µg/m³)
    float no2[14];      // Dióxido de nitrógeno (µg/m³)
    float pm25[14];     // Partículas PM2.5 (µg/m³)
};

// Estructura para factores climáticos
struct FactoresClimaticos
{
    float temperatura[14];    // Temperatura (°C)
    float humedad[14];       // Humedad relativa (%)
    float velocidadViento[14]; // Velocidad del viento (km/h)
    char direccionViento[14][10]; // Dirección del viento
};

// Estructura para una zona de monitoreo
struct ZonaMonitoreo
{
    int id;
    char nombre[50];
    char ubicacion[100];
    struct Contaminante contaminantes;
    struct FactoresClimaticos factoresClimaticos;
    char fecha[20];      // Fecha de la medición
    char hora[10];       // Hora de la medición
};

// Funciones principales del sistema de monitoreo de contaminación
void leerCadena(char *cadena, int num);
void obtenerFechaHora(char *fecha, char *hora);
int menu();

// Funciones para manejo de zonas de monitoreo
void crearZonasMonitoreo();
void mostrarZonas(struct ZonaMonitoreo zonas[], int numZonas);
void guardarZonas(struct ZonaMonitoreo zonas[], int numZonas);
int cargarZonas(struct ZonaMonitoreo zonas[], int *numZonas);

// Funciones de predicción
void generarPrediccion(struct ZonaMonitoreo zonas[], int numZonas);

// Funciones de alertas
void generarAlertas(struct ZonaMonitoreo zonas[], int numZonas);

// Funciones de reportes
void exportarDatos(struct ZonaMonitoreo zonas[], int numZonas);
void generarRecomendaciones(struct ZonaMonitoreo zonas[], int numZonas);
