#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "solitario.h"

void esperar_enter(void)
{
    int c;

    printf("\nPresione Enter...");

    while((c = getchar()) != '\n' && c != EOF)
    {
    }

    getchar();
}

void limpiar_pantalla(void)
{
    limpiar_consola();
}

int main(void)
{
    Tablero tablero;
    Accion accion;
    char jugada[30];
    int continuar;

    configurar_consola();
    srand(time(NULL));
    inicializar_tablero(&tablero);
    cargar_tablero(&tablero);
    continuar = 1;

    while(continuar == 1)
    {
        limpiar_pantalla();
        imprimir_tablero(&tablero);
        printf("Jugada: ");

        if(scanf("%29s", jugada) != 1)
        {
            break;
        }

        quitar_salto(jugada);
        convertir_mayusculas(jugada);

        if(strcmp(jugada, "SALIR") == 0)
        {
            continuar = 0;
        }
        else if(interpretar_accion(jugada, &accion) == 0)
        {
            printf("\nJugada invalida.\n");
            esperar_enter();
        }
        else if(accion.tipo == 1)
		{
		    avanzar_mazo(&tablero);
		}
		else
		{
		    if(realizar_movimiento(&tablero, accion)== 0)
            {
                printf("\nJugada invalida.\n");
                esperar_enter();
            }
		}
    }

    liberar_tablero(&tablero);
    imprimir_negro();
    printf("\n");

    return 0;
}


