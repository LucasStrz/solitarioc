#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "solitario.h"

int es_columna(char letra)
{
    if(letra >= 'A' && letra <= 'G')
    {
        return 1;
    }

    return 0;
}

int es_palo_ordenado(char letra)
{
    if(letra == 'P' || letra == 'T' || letra == 'R' || letra == 'S')
    {
        return 1;
    }

    return 0;
}

void quitar_salto(char texto[])
{
    int i;

    i = 0;

    while(texto[i] != '\0')
    {
        if(texto[i] == '\n' || texto[i] == '\r')
        {
            texto[i] = '\0';
            return;
        }

        i++;
    }
}

void convertir_mayusculas(char texto[])
{
    int i;

    i = 0;

    while(texto[i] != '\0')
    {
        texto[i] = (char)toupper((unsigned char)texto[i]);
        i++;
    }
}

int leer_area(char texto[], int *indice, char *area, int *fila)
{
    int numero;
    int tiene_numero;

    if(texto[*indice] == '\0')
    {
        return 0;
    }

    *area = texto[*indice];
    *fila = 0;

    if(*area != 'M' && es_palo_ordenado(*area) == 0 && es_columna(*area) == 0)
    {
        return 0;
    }

    *indice = *indice + 1;

    if(es_columna(*area) == 0)
    {
        return 1;
    }

    numero = 0;
    tiene_numero = 0;

    while(isdigit((unsigned char)texto[*indice]))
    {
        numero = numero * 10 + (texto[*indice] - '0');
        *indice = *indice + 1;
        tiene_numero = 1;
    }

    if(tiene_numero == 0 || numero < 1 || numero > 19)
    {
        return 0;
    }

    *fila = numero;

    return 1;
}

int interpretar_accion(char texto[], Accion *accion)
{
    int indice;
    char origen[15];
    char destino[15];

    quitar_salto(texto);
    convertir_mayusculas(texto);

    if(strcmp(texto, "M") == 0)
    {
        accion->tipo = 1;
        accion->origen = 'M';
        accion->fila_origen = 0;
        accion->destino = ' ';
        accion->fila_destino = 0;
        return 1;
    }

    if(sscanf(texto, "%14[^-]-%14s", origen, destino) != 2)
    {
        return 0;
    }

    indice = 0;

    if(leer_area(origen, &indice, &accion->origen, &accion->fila_origen) == 0)
    {
        return 0;
    }

    if(origen[indice] != '\0')
    {
        return 0;
    }

    indice = 0;

    if(leer_area(destino, &indice, &accion->destino, &accion->fila_destino) == 0)
    {
        return 0;
    }

    if(destino[indice] != '\0')
    {
        return 0;
    }

    if(accion->destino == 'M')
    {
        return 0;
    }

    if(es_palo_ordenado(accion->destino) == 1 && accion->fila_destino != 0)
    {
        return 0;
    }

    if(es_columna(accion->destino) == 1 && accion->fila_destino == 0)
    {
        return 0;
    }

    accion->tipo = 2;

    return 1;
}

void imprimir_accion(Accion accion)
{
    if(accion.tipo == 1)
    {
        printf("Accion reconocida: mostrar la siguiente carta del mazo.\n");
        return;
    }

    if(accion.fila_origen == 0 && accion.fila_destino == 0)
    {
        printf("Accion reconocida: mover de %c a %c.\n", accion.origen, accion.destino);
        return;
    }

    if(accion.fila_origen == 0)
    {
        printf("Accion reconocida: mover de %c a %c%d.\n", accion.origen, accion.destino, accion.fila_destino);
        return;
    }

    if(accion.fila_destino == 0)
    {
        printf("Accion reconocida: mover de %c%d a %c.\n", accion.origen, accion.fila_origen, accion.destino);
        return;
    }

    printf("Accion reconocida: mover de %c%d a %c%d.\n", accion.origen, accion.fila_origen, accion.destino, accion.fila_destino);
}

