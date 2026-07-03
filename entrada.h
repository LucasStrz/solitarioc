typedef struct Accion
{
    int tipo;
    char origen;
    int fila_origen;
    char destino;
    int fila_destino;
} Accion;

void quitar_salto(char texto[]);
void convertir_mayusculas(char texto[]);
int interpretar_accion(char texto[], Accion *accion);
void imprimir_accion(Accion accion);

