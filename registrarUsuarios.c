#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#include "global.h"
#include "registrarUsuarios.h"


void archivoConfiguracon(){
    FILE *archivoConfig;
    archivoConfig= fopen("config.txt", "w");
    if (archivoConfig==NULL)
    {
        return;
    }
    fprintf(archivoConfig, "true");
    fclose(archivoConfig);
    
}

RET buscarUsuario(char usuarioNuevo[50]){
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
        if (strcmp(usuarioNuevo, usuarios[i].usuario)==0)
        {
           return RET_OK;
        }
    }
    
    fclose(archivo);
    return RET_FAIL;
}

void anadirUsuarioAdministrador(){
    int numUsuarios=0;
    FILE *archivoConfig;
    char bandera[10];
    archivoConfig= fopen("config.txt", "r");
    if (archivoConfig!=NULL)
    {
        fscanf(archivoConfig, "%s", bandera);
        fclose(archivoConfig);
    }
    
    tusuarios usuarios[MAX_USUARIOS];

    if (strcmp(bandera, "true") != 0)
    {
        //FILE *archivo;
        archivo = fopen("baseDatos.txt", "w");
        if (archivo==NULL)
        {
            return;
        }

        strcpy(usuarios[numUsuarios].usuario, ADMINISTRADOR);
        strcpy(usuarios[numUsuarios].contrasena, CONTRASENA);
        numUsuarios++;

        for (int i = 0; i < numUsuarios; i++) {
            
            fprintf(archivo, "%s %s\n", usuarios[i].usuario, usuarios[i].contrasena);
        }
        fclose(archivo);
        archivoConfiguracon();
    } 

}

void registrarUsuarios(){

    anadirUsuarioAdministrador();
    int numUsuarios =0;
    tusuarios usuarios[MAX_USUARIOS];
    char usuarioNuevo[50];
    char contrasenaUsuario[LONGCLAVE];
    char confirmaContrasena[LONGCLAVE];
    char caracter;
    int i, j;
    i=0;
    j=0;
    printf("Ingrese un nombre de usuario: ");
    gets(usuarioNuevo);
    if (strlen(usuarioNuevo)==0){
        printf("No se ha ingresado ningun nombre de usuario\n");

    } else if (buscarUsuario(usuarioNuevo)==RET_FAIL)
    {
        printf("Ingrese una contrasena para este usuario: ");
        while(caracter = getch()){
            if(caracter==TECLA_ENTER){
                contrasenaUsuario[i] = '\0';
                break;
            } else if(caracter==TECLA_BORRAR){
                if(i>0){
                i--;
                printf("\b \b");
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
        if (strlen(contrasenaUsuario)<=5){
        printf("Contrasena demasiado corta, intente nuevamente\n");
        }else {
            printf("Confirme su contrasena: ");
            while(caracter = getch()){
                if(caracter==TECLA_ENTER){
                    confirmaContrasena[j] = '\0';
                    break;
                } else if(caracter==TECLA_BORRAR){
                    if(j>0){
                    j--;
                    printf("\b \b");
                    }
                } else {
                    if (j < LONGCLAVE){
                        printf("*");
                        confirmaContrasena[j]=caracter;
                        j++;
                    }
                }
            }
            printf("\n");

            if (strcmp(contrasenaUsuario, confirmaContrasena)==0)
            {
                strcpy(usuarios[numUsuarios].usuario, usuarioNuevo);
                strcpy(usuarios[numUsuarios].contrasena, contrasenaUsuario);
                numUsuarios++;
                printf("Usuario registrado de manera exitosa\n");
                //FILE *archivo;
                archivo = fopen("baseDatos.txt", "a");
                if (archivo==NULL)
                {
                    return;
                } 
                for (int i = 0; i < numUsuarios; i++)
                    {
                        fprintf(archivo, "%s %s\n", usuarios[i].usuario, usuarios[i].contrasena);
                    }
                    fclose(archivo);
                
            }else{
                printf("Las contrasenas no coinciden, intente nuevamente\n");
            }
        }
    }else {
        printf("El nombre de usuario ya existe en el sistema\n");
    }

    system("pause");
    system("cls");
}

