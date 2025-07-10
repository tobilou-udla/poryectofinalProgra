// Estructura para almacenar datos de contaminantes
struct Contaminante
{
    float co2[50];      // Dióxido de carbono (ppm)
    float so2[50];      // Dióxido de azufre (µg/m³)
    float no2[50];      // Dióxido de nitrógeno (µg/m³)
    float pm25[50];     // Partículas PM2.5 (µg/m³)
};

// Estructura para factores climáticos
struct FactoresClimaticos
{
    float temperatura[50];    // Temperatura (°C)
    float humedad[50];       // Humedad relativa (%)
    float velocidadViento[50]; // Velocidad del viento (km/h)
    float direccionViento[50]; // Dirección del viento en grados
};

// Estructura para una zona de monitoreo
struct ZonaMonitoreo
{
    int id;
    char nombre[50];
    char ubicacion[100];
    struct Contaminante contaminantes;
    struct FactoresClimaticos factoresClimaticos;
    char fecha[30][20]; // Arreglo para almacenar las últimas 30 fechas
    char hora[30][10];  // Arreglo para almacenar las últimas 30 horas
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
void agregarReporte(struct ZonaMonitoreo *zona, float co2, float so2, float no2, float pm25, float temperatura, float humedad, float velocidadViento, float direccionViento, char fecha[], char hora[]);
