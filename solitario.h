#define NEGRO "\x1b[30m"
#define ROJO "\x1b[31m"
#define VERDE "\x1b[32m"
#define AMARILLO "\x1b[33m"
#define AZUL "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CIAN "\x1b[36m"
#define RESET "\x1b[0m"

#define FONDO_CONSOLA "20"

typedef struct Carta
{
    int valor;
    int color;
    int visible;
    char palo;
    char texto[4];
} Carta;

typedef struct Nodo
{
    Carta carta;
    struct Nodo *siguiente;
} Nodo;

typedef struct Tablero
{
    Nodo *columnas[7];
    Nodo *mazo;
    Nodo *descarte;
    Nodo *palos[4];
    int puntos;
} Tablero;

typedef struct Accion
{
    int tipo;
    char origen;
    int fila_origen;
    char destino;
    int fila_destino;
} Accion;

char letra_valor(int valor);

Nodo *crear_nodo(Carta carta);
void insertar_inicio(Nodo **lista, Carta carta);
void insertar_final(Nodo **lista, Carta carta);
int retirar_primero(Nodo **lista, Carta *carta);
int retirar_posicion(Nodo **lista, int posicion, Carta *carta);
int cantidad_lista(Nodo *lista);
Nodo *obtener_nodo(Nodo *lista, int posicion);
void liberar_lista(Nodo **lista);
void generar_mazo(Nodo **mazo);

void inicializar_tablero(Tablero *tablero);
void cargar_tablero(Tablero *tablero);
int avanzar_mazo(Tablero *tablero);
void imprimir_tablero(Tablero *tablero);
void liberar_tablero(Tablero *tablero);

void quitar_salto(char texto[]);
void convertir_mayusculas(char texto[]);
int interpretar_accion(char texto[], Accion *accion);
void imprimir_accion(Accion accion);

