#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#define ADMINISTRADOR "admin"
#define CONTRASENA "admin.123"
#define MAX_USUARIOS 100
#define LONGCLAVE 10

FILE *archivo;

typedef enum {
    RET_OK,
    RET_FAIL
}RET;

typedef struct
{
    char usuario[50];
    char contrasena[LONGCLAVE];
}tusuarios;

typedef struct
{
    int codLibro;
    char nombreLibro[200];
    char autorLibro[50];
    int cantidadTotal;
    int cantidadDisponible;
}tlibros;

typedef struct
{
    int codLibro;
    char nombreLibro[200];
    char usuario[50];
    int dd;
    int mm;
    int aa;
}tlibrosprestados;

typedef struct
{
    int codLibro;
    char nombreLibro[200];
    char autorLibro[50];
    int cantidad;
}tlibrosdisponibles;

typedef struct
{
    char usuario[50];
    tlibrosprestados LibrosPrestados;
} tlibrosUsuarios;


//void loginUsuarios();

#endif //__GLOBAL_H__
