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
void avanzar_mazo(Tablero *tablero);
void imprimir_tablero(Tablero *tablero);
void liberar_tablero(Tablero *tablero);

void quitar_salto(char texto[]);
void convertir_mayusculas(char texto[]);
int interpretar_accion(char texto[], Accion *accion);
void imprimir_accion(Accion accion);

void configurar_consola(void);
void limpiar_consola(void);
void imprimir_rojo(void);
void imprimir_negro(void);
