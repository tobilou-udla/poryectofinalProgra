// Estructura para almacenar un reporte actual
struct ReporteActual {
    float co2;      // Dióxido de carbono (ppm)
    float so2;      // Dióxido de azufre (µg/m³)
    float no2;      // Dióxido de nitrógeno (µg/m³)
    float pm25;     // Partículas PM2.5 (µg/m³)
    float temperatura; // Temperatura (°C)
    float humedad;     // Humedad relativa (%)
    float velocidadViento; // Velocidad del viento (km/h)
    float direccionViento; // Dirección del viento en grados
    char fecha[20]; // Fecha del reporte actual
    char hora[10];  // Hora del reporte actual
};

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
    struct ReporteActual reporteActual; // Reporte actual anidado
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
void agregarReporte(struct ZonaMonitoreo *zona, struct ReporteActual reporte);
float pedirFlotanteValido(const char *mensaje);
void ingresarDatosActuales(struct ZonaMonitoreo zonas[], int numZonas);
