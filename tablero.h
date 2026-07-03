#include "carta.h"

typedef struct Tablero
{
    Nodo *columnas[7];
    Nodo *mazo;
    Nodo *descarte;
    Nodo *palos[4];
    int puntos;
} Tablero;

void inicializar_tablero(Tablero *tablero);
void cargar_tablero(Tablero *tablero);
void avanzar_mazo(Tablero *tablero);
void imprimir_tablero(Tablero *tablero);
void liberar_tablero(Tablero *tablero);

