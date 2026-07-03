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

void avanzar_mazo(Tablero *tablero)
{
    Carta carta;

    if(retirar_primero(&tablero->mazo, &carta) == 0)
    {
        if(tablero->descarte == NULL)
        {
            printf("\nNo quedan cartas en el mazo ni en el descarte.\n");
            return;
        }

        reciclar_descarte(tablero);
        printf("\nSe reciclo el descarte al mazo.\n");
        return;
    }

    carta.visible = 1;
    insertar_inicio(&tablero->descarte, carta);

    printf("\nSe mostro la siguiente carta del mazo: ");
    printf("%s\n", carta.texto);
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

