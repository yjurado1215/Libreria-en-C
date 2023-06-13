#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

#include "global.h"
#include "registrarUsuarios.h"
#include "login.h"



int main(){

    int opcion;

    do
    {
        printf("Que desea realizar: \n");
        printf("1. Ingresar al Sistema\n");
        printf("2. Registrarse en el sistema\n");
        printf("3. Finalizar el programa\n");
        printf("Ingrese la opcion: ");
        scanf("%i", &opcion);
        fflush(stdin);
        switch (opcion)
        {
        case 1:
            loginUsuarios();
            break;
        case 2:
            registrarUsuarios();
            break;
        default:
            break;
        }
    } while (opcion!=3);
    
    system("pause");
    system("cls");
    return 0;
}