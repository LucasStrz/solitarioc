#include <stdio.h>
#include "solitario.h"

void inicializar_tablero(Tablero *tablero)
{
    int i;

    tablero->mazo = NULL;
    tablero->descarte = NULL;
    tablero->puntos = 0;

    for(i = 0; i < 7; i++)
    {
        tablero->columnas[i] = NULL;
    }

    for(i = 0; i < 4; i++)
    {
        tablero->palos[i] = NULL;
    }
}

void cargar_tablero(Tablero *tablero)
{
    Carta carta;
    int columna;
    int nivel;

    generar_mazo(&tablero->mazo);

    for(columna = 0; columna < 7; columna++)
    {
        for(nivel = 0; nivel <= columna; nivel++)
        {
            if(retirar_primero(&tablero->mazo, &carta) == 1)
            {
                if(nivel == columna)
                {
                    carta.visible = 1;
                }
                else
                {
                    carta.visible = 0;
                }

                insertar_final(&tablero->columnas[columna], carta);
            }
        }
    }
}

void reciclar_descarte(Tablero *tablero)
{
    Carta carta;

    while(retirar_primero(&tablero->descarte, &carta) == 1)
    {
        carta.visible = 0;
        insertar_inicio(&tablero->mazo, carta);
    }
}

int indice_columna(char columna)
{
    return columna - 'A';
}

int indice_palo_ordenado(char palo)
{
    if(palo == 'P')
    {
        return 0;
    }

    if(palo == 'T')
    {
        return 1;
    }

    if(palo == 'R')
    {
        return 2;
    }

    if(palo == 'S')
    {
        return 3;
    }

    return -1;
}

Nodo *ultimo_nodo(Nodo *lista)
{
    if(lista == NULL)
    {
        return NULL;
    }

    while(lista->siguiente != NULL)
    {
        lista = lista->siguiente;
    }

    return lista;
}

Nodo *cortar_desde(Nodo **lista, int posicion)
{
    Nodo *actual;
    Nodo *anterior;
    int contador;

    if(*lista == NULL || posicion < 1)
    {
        return NULL;
    }

    actual = *lista;
    anterior = NULL;
    contador = 1;

    while(actual != NULL && contador < posicion)
    {
        anterior = actual;
        actual = actual->siguiente;
        contador++;
    }

    if(actual == NULL)
    {
        return NULL;
    }

    if(anterior == NULL)
    {
        *lista = NULL;
    }
    else
    {
        anterior->siguiente = NULL;
    }

    return actual;
}

void agregar_lista_final(Nodo **destino, Nodo *cartas)
{
    Nodo *ultimo;

    if(cartas == NULL)
    {
        return;
    }

    if(*destino == NULL)
    {
        *destino = cartas;
        return;
    }

    ultimo = ultimo_nodo(*destino);
    ultimo->siguiente = cartas;
}

int secuencia_columna_valida(Nodo *cartas)
{
    while(cartas != NULL)
    {
        if(cartas->carta.visible == 0)
        {
            return 0;
        }

        if(cartas->siguiente != NULL)
        {
            if(cartas->carta.color == cartas->siguiente->carta.color)
            {
                return 0;
            }

            if(cartas->carta.valor != cartas->siguiente->carta.valor + 1)
            {
                return 0;
            }
        }

        cartas = cartas->siguiente;
    }

    return 1;
}

int puede_ir_a_columna(Carta carta, Nodo *columna)
{
    Nodo *tope;

    tope = ultimo_nodo(columna);

    if(tope == NULL)
    {
        if(carta.valor == 13)
        {
            return 1;
        }

        return 0;
    }

    if(tope->carta.visible == 0)
    {
        return 0;
    }

    if(tope->carta.color == carta.color)
    {
        return 0;
    }

    if(tope->carta.valor != carta.valor + 1)
    {
        return 0;
    }

    return 1;
}

int puede_ir_a_palo(Carta carta, Nodo *palo)
{
    if(palo == NULL)
    {
        if(carta.valor == 1)
        {
            return 1;
        }

        return 0;
    }

    if(palo->carta.palo != carta.palo)
    {
        return 0;
    }

    if(carta.valor != palo->carta.valor + 1)
    {
        return 0;
    }

    return 1;
}

int revelar_ultima_columna(Nodo *columna)
{
    Nodo *tope;

    tope = ultimo_nodo(columna);

    if(tope != NULL && tope->carta.visible == 0)
    {
        tope->carta.visible = 1;
        return 1;
    }

    return 0;
}

int fila_destino_columna_valida(Nodo *columna, int fila_destino, Carta carta)
{
    int cantidad;

    cantidad = cantidad_lista(columna);

    if(cantidad == 0)
    {
        if(fila_destino == 1 && carta.valor == 13)
        {
            return 1;
        }

        return 0;
    }

    if(fila_destino == cantidad)
    {
        return 1;
    }

    return 0;
}

void avanzar_mazo(Tablero *tablero)
{
    Carta carta;

    if(retirar_primero(&tablero->mazo, &carta) == 0)
    {
        if(tablero->descarte == NULL)
        {
            return;
        }

        reciclar_descarte(tablero);
        /*se recicla descarte a mazo*/
        return;
    }

    carta.visible = 1;
    insertar_inicio(&tablero->descarte, carta);

    /*printf("\nSe mostro la siguiente carta del mazo: ");
    printf("%s\n", carta.texto);*/
}

int mover_mazo_a_columna(Tablero *tablero, int destino, int fila_destino)
{
    Carta carta;

    if(tablero->descarte == NULL)
    {
        return 0;
    }

    carta = tablero->descarte->carta;

    if(fila_destino_columna_valida(tablero->columnas[destino], fila_destino, carta) == 0)
    {
        return 0;
    }

    if(puede_ir_a_columna(carta, tablero->columnas[destino]) == 0)
    {
        return 0;
    }

    retirar_primero(&tablero->descarte, &carta);
    insertar_final(&tablero->columnas[destino], carta);

    /*printf("\nSe movio %s del mazo a la columna %c.\n", carta.texto, 'A' + destino);*/
    return 1;
}

int mover_mazo_a_palo(Tablero *tablero, int destino)
{
    Carta carta;

    if(tablero->descarte == NULL)
    {
        return 0;
    }

    carta = tablero->descarte->carta;

    if(puede_ir_a_palo(carta, tablero->palos[destino]) == 0)
    {
        /*printf("\nMovimiento no permitido.\n");*/
        return 0;
    }

    retirar_primero(&tablero->descarte, &carta);
    insertar_inicio(&tablero->palos[destino], carta);
    tablero->puntos = tablero->puntos + 10;

    /*printf("\nSe movio %s del mazo a la pila %c.\n", carta.texto, "PTRS"[destino]);*/
    return 1;
}

int mover_columna_a_columna(Tablero *tablero, Accion accion)
{
    Nodo *cartas;
    Nodo *origen;
    int columna_origen;
    int columna_destino;

    columna_origen = indice_columna(accion.origen);
    columna_destino = indice_columna(accion.destino);

    if(columna_origen == columna_destino)
    {
        return 0;
    }

    origen = obtener_nodo(tablero->columnas[columna_origen], accion.fila_origen);

    if(origen == NULL)
    {
        return 0;
    }

    if(fila_destino_columna_valida(tablero->columnas[columna_destino], accion.fila_destino, origen->carta) == 0)
    {
        return 0;
    }

    if(secuencia_columna_valida(origen) == 0)
    {
        return 0;
    }

    if(puede_ir_a_columna(origen->carta, tablero->columnas[columna_destino]) == 0)
    {
        return 0;
    }

    cartas = cortar_desde(&tablero->columnas[columna_origen], accion.fila_origen);
    agregar_lista_final(&tablero->columnas[columna_destino], cartas);

    if(revelar_ultima_columna(tablero->columnas[columna_origen]) == 1)
    {
        tablero->puntos = tablero->puntos + 5;
    }

    /*printf("\nMovimiento realizado.\n");*/
    return 1;
}

int mover_columna_a_palo(Tablero *tablero, Accion accion)
{
    Carta carta;
    Nodo *origen;
    int columna_origen;
    int palo_destino;

    columna_origen = indice_columna(accion.origen);
    palo_destino = indice_palo_ordenado(accion.destino);

    if(accion.fila_origen != cantidad_lista(tablero->columnas[columna_origen]))
    {
        /*solo se puede subir la carta visible de abajo de la columna*/
        return 0;
    }

    origen = obtener_nodo(tablero->columnas[columna_origen], accion.fila_origen);

    if(origen == NULL || origen->carta.visible == 0)
    {
        /*no hay carta visible en el origen*/
        return 0;
    }

    carta = origen->carta;

    if(puede_ir_a_palo(carta, tablero->palos[palo_destino]) == 0)
    {
        /*movimiento no permitido hacia la pila superior*/
        return 0;
    }

    retirar_posicion(&tablero->columnas[columna_origen], accion.fila_origen, &carta);
    insertar_inicio(&tablero->palos[palo_destino], carta);
    tablero->puntos = tablero->puntos + 10;

    if(revelar_ultima_columna(tablero->columnas[columna_origen]) == 1)
    {
        tablero->puntos = tablero->puntos + 5;
    }

    /*printf("\nSe movio %s a la pila %c.\n", carta.texto, accion.destino);*/
    return 1;
}

int mover_palo_a_columna(Tablero *tablero, Accion accion)
{
    Carta carta;
    int palo_origen;
    int columna_destino;

    palo_origen = indice_palo_ordenado(accion.origen);
    columna_destino = indice_columna(accion.destino);

    if(tablero->palos[palo_origen] == NULL)
    {
        /*la pila superior esta vacia*/
        return 0;
    }

    carta = tablero->palos[palo_origen]->carta;

    if(fila_destino_columna_valida(tablero->columnas[columna_destino], accion.fila_destino, carta) == 0)
    {
        /*la fila destino no corresponde a la ultima carta de la columna*/
        return 0;
    }

    if(puede_ir_a_columna(carta, tablero->columnas[columna_destino]) == 0)
    {
        /*movimiento no permitido hacia la columna*/
        return 0;
    }

    retirar_primero(&tablero->palos[palo_origen], &carta);
    insertar_final(&tablero->columnas[columna_destino], carta);

    tablero->puntos = tablero->puntos - 10;

    /*printf("\n se movio %s de la pila %c a la columna %c \n", carta.texto, accion.origen, accion.destino);*/
    return 1;
}

int realizar_movimiento(Tablero *tablero, Accion accion)
{
    int destino;

    if(accion.origen == 'M')
    {
        if(accion.destino >= 'A' && accion.destino <= 'G')
        {
            destino = indice_columna(accion.destino);
            return mover_mazo_a_columna(tablero, destino, accion.fila_destino);
        }

        destino = indice_palo_ordenado(accion.destino);
        return mover_mazo_a_palo(tablero, destino);
    }

    if(accion.origen >= 'A' && accion.origen <= 'G')
    {
        if(accion.destino >= 'A' && accion.destino <= 'G')
        {
            return mover_columna_a_columna(tablero, accion);
        }

        return mover_columna_a_palo(tablero, accion);
    }

    if(accion.destino >= 'A' && accion.destino <= 'G')
    {
        return mover_palo_a_columna(tablero, accion);
    }

    return 0;
}

void imprimir_carta(Carta carta)
{
    if(carta.visible == 0)
    {
        imprimir_negro();
        printf("## ");
        return;
    }

    if(carta.color == 0)
    {
        imprimir_rojo();
    }
    else
    {
        imprimir_negro();
    }

    printf("%-3s", carta.texto);
    imprimir_negro();
}

void imprimir_tope(Nodo *lista)
{
    if(lista == NULL)
    {
        printf("## ");
    }
    else
    {
        imprimir_carta(lista->carta);
    }
}

void imprimir_tablero(Tablero *tablero)
{
    Nodo *nodo;
    int fila;
    int columna;

    imprimir_negro();
    printf("M                         P       T       R       S\n");

    imprimir_tope(tablero->descarte);
    printf("                        ");
    imprimir_tope(tablero->palos[0]);
    printf("     ");
    imprimir_tope(tablero->palos[1]);
    printf("     ");
    imprimir_tope(tablero->palos[2]);
    printf("     ");
    imprimir_tope(tablero->palos[3]);
    printf("\n\n");

    printf("     A       B       C       D       E       F       G\n");

    for(fila = 1; fila <= 19; fila++)
    {
        printf("%-3d ", fila);

        for(columna = 0; columna < 7; columna++)
        {
            nodo = obtener_nodo(tablero->columnas[columna], fila);

            if(nodo == NULL)
            {
                printf("        ");
            }
            else
            {
                imprimir_carta(nodo->carta);
                printf("     ");
            }
        }

        printf("\n");
    }

    printf("\nPuntos: %d\n", tablero->puntos);
}

void liberar_tablero(Tablero *tablero)
{
    int i;

    liberar_lista(&tablero->mazo);
    liberar_lista(&tablero->descarte);

    for(i = 0; i < 7; i++)
    {
        liberar_lista(&tablero->columnas[i]);
    }

    for(i = 0; i < 4; i++)
    {
        liberar_lista(&tablero->palos[i]);
    }
}
