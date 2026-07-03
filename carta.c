#include <stdio.h>
#include <stdlib.h>
#include "carta.h"

char letra_valor(int valor)
{
    switch(valor)
    {
        case 1:
            return 'A';
        case 11:
            return 'J';
        case 12:
            return 'Q';
        case 13:
            return 'K';
        default:
            return '0';
    }
}

Nodo *crear_nodo(Carta carta)
{
    Nodo *nuevo;

    nuevo = (Nodo *)malloc(sizeof(Nodo));

    if(nuevo == NULL)
    {
        return NULL;
    }

    nuevo->carta = carta;
    nuevo->siguiente = NULL;

    return nuevo;
}

void insertar_inicio(Nodo **lista, Carta carta)
{
    Nodo *nuevo;

    nuevo = crear_nodo(carta);

    if(nuevo == NULL)
    {
        return;
    }

    nuevo->siguiente = *lista;
    *lista = nuevo;
}

void insertar_final(Nodo **lista, Carta carta)
{
    Nodo *nuevo;
    Nodo *actual;

    nuevo = crear_nodo(carta);

    if(nuevo == NULL)
    {
        return;
    }

    if(*lista == NULL)
    {
        *lista = nuevo;
        return;
    }

    actual = *lista;

    while(actual->siguiente != NULL)
    {
        actual = actual->siguiente;
    }

    actual->siguiente = nuevo;
}

int retirar_primero(Nodo **lista, Carta *carta)
{
    Nodo *eliminado;

    if(*lista == NULL)
    {
        return 0;
    }

    eliminado = *lista;
    *carta = eliminado->carta;
    *lista = eliminado->siguiente;
    free(eliminado);

    return 1;
}

int retirar_posicion(Nodo **lista, int posicion, Carta *carta)
{
    Nodo *actual;
    Nodo *anterior;
    int contador;

    if(*lista == NULL || posicion < 1)
    {
        return 0;
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
        return 0;
    }

    if(anterior == NULL)
    {
        *lista = actual->siguiente;
    }
    else
    {
        anterior->siguiente = actual->siguiente;
    }

    *carta = actual->carta;
    free(actual);

    return 1;
}

int cantidad_lista(Nodo *lista)
{
    int cantidad;

    cantidad = 0;

    while(lista != NULL)
    {
        cantidad++;
        lista = lista->siguiente;
    }

    return cantidad;
}

Nodo *obtener_nodo(Nodo *lista, int posicion)
{
    int contador;

    contador = 1;

    while(lista != NULL && contador < posicion)
    {
        lista = lista->siguiente;
        contador++;
    }

    return lista;
}

void liberar_lista(Nodo **lista)
{
    Nodo *eliminado;

    while(*lista != NULL)
    {
        eliminado = *lista;
        *lista = eliminado->siguiente;
        free(eliminado);
    }
}

void generar_mazo(Nodo **mazo)
{
    Nodo *ordenadas;
    Carta carta;
    char palos[4];
    int i;
    int j;
    int posicion;
    int cantidad;

    ordenadas = NULL;
    palos[0] = 'C';
    palos[1] = 'D';
    palos[2] = 'T';
    palos[3] = 'E';

    for(i = 0; i < 4; i++)
    {
        for(j = 1; j <= 13; j++)
        {
            carta.valor = j;
            carta.palo = palos[i];
            carta.visible = 0;

            if(carta.palo == 'C' || carta.palo == 'D')
            {
                carta.color = 0;
            }
            else
            {
                carta.color = 1;
            }

            if(j == 1 || j == 11 || j == 12 || j == 13)
            {
                sprintf(carta.texto, "%c%c", letra_valor(j), carta.palo);
            }
            else
            {
                sprintf(carta.texto, "%d%c", j, carta.palo);
            }

            insertar_final(&ordenadas, carta);
        }
    }

    while(ordenadas != NULL)
    {
        cantidad = cantidad_lista(ordenadas);
        posicion = rand() % cantidad + 1;

        if(retirar_posicion(&ordenadas, posicion, &carta) == 1)
        {
            insertar_final(mazo, carta);
        }
    }
}


