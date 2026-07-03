#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "solitario.h"

void esperar_enter(void)
{
    char linea[4];

    printf("\nPresione Enter...");
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
    srand((unsigned int)time(NULL));
    inicializar_tablero(&tablero);
    cargar_tablero(&tablero);
    continuar = 1;

    while(continuar == 1)
    {
        limpiar_pantalla();
        imprimir_tablero(&tablero);
        printf("Jugada: ");

        if(fgets(jugada, sizeof(jugada), stdin) == NULL)
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
            printf("\nJugada invalida. Ejemplos: M, M-P, P-A4, M-A2, B3-G7.\n");
            esperar_enter();
        }
        else if(accion.tipo == 1)
		{
		    avanzar_mazo(&tablero);
		    esperar_enter();
		}
		else
		{
		    printf("\n");
		    imprimir_accion(accion);
		    /*printf("Este comando ya fue interpretado. El movimiento con validaciones se agrega en la siguiente fase.\n");*/
		    esperar_enter();
		}
    }

    liberar_tablero(&tablero);
    imprimir_negro();
    printf("\n");

    return 0;
}


