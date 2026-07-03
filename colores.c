#include <stdio.h>
#include <stdlib.h>
#include "colores.h"

void configurar_consola(void)
{
    system("color 20");
}

void limpiar_consola(void)
{
    system("cls");
    imprimir_negro();
}

void imprimir_rojo(void)
{
    printf("\x1b[31m");
}

void imprimir_negro(void)
{
    printf("\x1b[30m");
}

