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

