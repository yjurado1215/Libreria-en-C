#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<conio.h>

#include "global.h"
#include "registrarUsuarios.h"
#include "login.h"
#include "administrador.h"
#include "usuarios.h"


RET validarUsuario(char usuarioIngresado[50], char contrasenaIngresada[LONGCLAVE]){
    int numUsuarios=0;
    //FILE *archivo;
    archivo = fopen("baseDatos.txt", "r");
    if (archivo == NULL) {
        return;
    }
    
    tusuarios usuarios[MAX_USUARIOS];
    while (fscanf(archivo, "%s %s", usuarios[numUsuarios].usuario, usuarios[numUsuarios].contrasena) == 2) {
        numUsuarios++;
    }

    for (int i = 0; i < numUsuarios; i++)
    {
        if (strcmp(usuarioIngresado, usuarios[i].usuario)==0)
        {
           if (strcmp(contrasenaIngresada, usuarios[i].contrasena)==0)
           {
            return RET_OK;
           } 
        }
    }
    
    fclose(archivo);
    return RET_FAIL;
}

void loginUsuarios(){

    //FILE *archivo;
    archivo = fopen("baseDatos.txt", "r");
    if (archivo==NULL)
    {
        return;
    }
    fclose(archivo);
    tusuarios usuarios[MAX_USUARIOS];
    char usuarioIngresado[50];
    char contrasenaUsuario[LONGCLAVE];
    printf("Ingresa tu usuario: ");
    gets(usuarioIngresado);
    printf("Ingresa tu contrasena: ");
    int i =0;
    char caracter;
    while(caracter = getch()){
            if(caracter==TECLA_ENTER){
                contrasenaUsuario[i] = '\0';
                break;
            } else if(caracter==TECLA_BORRAR){
                if(i>0){
                i--;
                printf("\b \b"); //\b significa retroceso
                }
            } else {
                if (i < LONGCLAVE){
                    printf("*");
                    contrasenaUsuario[i]=caracter;
                    i++;
                }
            }
        }
        printf("\n");
   
    if (validarUsuario(usuarioIngresado, contrasenaUsuario) == RET_OK)
    {
        if (strcmp(usuarioIngresado, ADMINISTRADOR)==0 && strcmp(contrasenaUsuario, CONTRASENA)==0)
        {
            system("pause");
            system("cls");
            printf("Eres usuario Administrador\n");
            menuUsuarioAdministrador();
            
        } else
        {
            system("pause");
            system("cls");
            printf("Inicio de sesion exitosa\n");
            char *usuarioActual = malloc(strlen(usuarioActual) + 1);
            strcpy(usuarioActual, usuarioIngresado);
            menuUsuarios(usuarioActual);
        }
    } else
    {
        printf("Usuario o contrasena incorrectos\n");
    }
    
    system("pause");
    system("cls");
}
