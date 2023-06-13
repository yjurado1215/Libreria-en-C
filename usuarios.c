#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

#include "global.h"
#include "administrador.h"
#include "usuarios.h"

RET compararCodigo(int codLibroDisponible, char *usuarioActual){

    FILE* archivo2 = fopen("librosPrestados.dat", "rb");
    if (archivo2==NULL)
    {
        return; 
    } 

    tlibrosprestados librosPrestados;
    while (fread(&librosPrestados, sizeof(tlibrosprestados), 1, archivo2)==1)
    {
        if (codLibroDisponible==librosPrestados.codLibro && strcmp(librosPrestados.usuario, usuarioActual)==0) {
        fclose(archivo2);
            return RET_OK;
        }
    }

    fclose(archivo2);
    return RET_FAIL;

}

void librosDisponibles(char *usuarioActual){

    tlibros librosDisponibles;
    FILE *archivo2 = fopen("librosPrestados.dat", "rb");
    if (archivo2==NULL)
    {
        archivo = fopen("libros.dat", "rb");
        if (archivo==NULL)
        {
            return;
        } 
        while (fread(&librosDisponibles, sizeof(tlibros), 1, archivo)==1)
        {
            printf("Cod: %i | Nombre: %s | Autor: %s |\n", librosDisponibles.codLibro, librosDisponibles.nombreLibro, librosDisponibles.autorLibro);
        }
        fclose(archivo);
    } 
    fclose(archivo2);

    archivo = fopen("libros.dat", "rb");
    if (archivo==NULL)
    {
        return;
    }
   
    while (fread(&librosDisponibles, sizeof(tlibros), 1, archivo)==1)  {
        if (librosDisponibles.cantidadDisponible>0)
        {
           int codLibroDisponible=librosDisponibles.codLibro;

           if (compararCodigo(codLibroDisponible, usuarioActual)==RET_FAIL)
            {
              printf("Cod: %i | Nombre Libro: %s | Autor: %s |\n", librosDisponibles.codLibro, librosDisponibles.nombreLibro,
                    librosDisponibles.autorLibro);
            }
        
        } 
    }
    
    fclose(archivo);
    system("pause");
    system("cls");

}

void modificarCantLibros(tlibrosprestados *librosPrestados){

   archivo = fopen("libros.dat", "r+b");
    if (archivo == NULL) {
        return;
    }

    tlibros libros;
    while (fread(&libros, sizeof(tlibros), 1, archivo)==1)
    {
        if (librosPrestados->codLibro==libros.codLibro)
        {
        libros.cantidadDisponible = libros.cantidadDisponible-1;
        fseek(archivo, -sizeof(tlibros),SEEK_CUR);
        fwrite(&libros, sizeof(tlibros), 1, archivo);
        } 
        fseek(archivo, 0, SEEK_CUR);
    }
    fclose(archivo);
}

void modificarCantLibrosAumentar(int codLibroMod){

   archivo = fopen("libros.dat", "r+b");
    if (archivo == NULL) {
        return;
    }

    tlibros libros;
    while (fread(&libros, sizeof(tlibros), 1, archivo)==1)
    {
        if (codLibroMod==libros.codLibro)
        {
        libros.cantidadDisponible = libros.cantidadDisponible+1;
        fseek(archivo, -sizeof(tlibros),SEEK_CUR);
        fwrite(&libros, sizeof(tlibros), 1, archivo);
        } 
        fseek(archivo, 0, SEEK_CUR);
    }
    fclose(archivo);
}



void prestarLibro(char *usuarioActual){

    tlibros libros;
    tlibrosprestados librosPrestados;
    if (libros.cantidadDisponible>0) {
        librosPrestados.codLibro = libros.codLibro;
        strcpy(librosPrestados.nombreLibro, libros.nombreLibro);
        strcpy(librosPrestados.usuario, usuarioActual);
        printf("Ingrese la fecha de entrega estimada: \n");
        printf("Dia: ");
        scanf("%i", &librosPrestados.dd);
        printf("Mes: ");
        scanf("%i", &librosPrestados.mm);
        fflush(stdin);
        printf("Anio: ");
        scanf("%i", &librosPrestados.aa);
        modificarCantLibros(&librosPrestados);
       archivo = fopen("librosPrestados.dat", "ab");
        if (archivo == NULL) {
            return;
        } 
        fwrite(&librosPrestados, sizeof(tlibrosprestados), 1, archivo); 
        fclose(archivo);
        printf("Se ha registrado un prestamo exitoso\n");
    }else
    {
        printf("Libro no disponible\n");
    }

    system("pause");
    system("cls");   
}


void misLibros(char *usuarioActual){
    archivo = fopen("librosPrestados.dat", "rb");
    if (archivo==NULL)
    {
        return;
    }

    tlibrosprestados librosPrestados;
    
    while (fread(&librosPrestados, sizeof(tlibrosprestados), 1, archivo)==1)  {
        if (strcmp(librosPrestados.usuario, usuarioActual)==0)
        {
            printf("Cod: %i | Nombre Libro: %s | Fecha Entrega: %i/%i/%i |\n", librosPrestados.codLibro, librosPrestados.nombreLibro,
                librosPrestados.dd, librosPrestados.mm, librosPrestados.aa); 
        } 
    }
    
    fclose(archivo);

    system("pause");
    system("cls");
}

RET buscarCodLibPrestados(int codLibEntregar, char *usuarioActual){
    archivo = fopen("librosPrestados.dat", "rb");
    if (archivo == NULL) {
        exit(1);
    }

    tlibrosprestados librosPrestados;
    fread(&librosPrestados, sizeof(tlibrosprestados), 1, archivo);
    while (!feof(archivo)) {
        if (librosPrestados.codLibro == codLibEntregar && strcmp(librosPrestados.usuario, usuarioActual)==0) {
            fclose(archivo);
            return RET_OK;
        }
        fread(&librosPrestados, sizeof(tlibrosprestados), 1, archivo);
    }
 
    fclose(archivo);
    return RET_FAIL;

}

void entregarLibro(int codLibEntregar){

    archivo = fopen("librosPrestados.dat", "rb");
    if (archivo == NULL) {
        return;
    }

    FILE *archivoTemporal1 = fopen("temp.dat", "wb");
    if (archivoTemporal1 == NULL) {
        return;
    }

    tlibrosprestados libroPrestados;

    while (fread(&libroPrestados, sizeof(tlibrosprestados), 1, archivo) == 1) {
        if (libroPrestados.codLibro != codLibEntregar) {
            fwrite(&libroPrestados, sizeof(tlibrosprestados), 1, archivoTemporal1);
        }
    }
    
    fclose(archivo);
    fclose(archivoTemporal1);

    if (remove("librosPrestados.dat") == 0) {
        if (rename("temp.dat", "librosPrestados.dat") != 0) {
            printf("No se pudo renombrar el archivo temporal\n");
            return;
        }
    } else {
        printf("Error al eliminar el archivo original\n");
        return;
    }
   
    printf("Libro devuelto con exito.\n");
    modificarCantLibrosAumentar(codLibEntregar);
    system("pause");
    system("cls");
}

void menuUsuarios(char *usuarioActual){
    printf("Usuario Recibido %s\n", usuarioActual);
    int opcMenu;
    do
    {
        printf("Que desea realizar\n");
        printf("1. Lista de libros disponibles\n");
        printf("2. Lista de mis libros\n");
        printf("3. Sacar prestado un libro\n");
        printf("4. Entregar libro\n");
        printf("5. Salir\n");
        printf("Ingrese la opcion: ");
        scanf("%i", &opcMenu);
        fflush(stdin);
        switch (opcMenu)
        {
        case 1:
            //tlibrosprestados librosPrestados;
            librosDisponibles(usuarioActual);
            break;
        case 2:
            misLibros(usuarioActual);

            break;
        case 3:
            printf("Ingrese el codigo del libro que desea sacar prestado: ");
            int codLibro;
            scanf("%i", &codLibro);
            if (buscarCodLibros(codLibro)==RET_OK)
            {
                prestarLibro(usuarioActual);
            }else
            {
                printf("No existe un libro con ese codigo\n");
                system("pause");
                system("cls");
            }
            break;
        case 4:
            printf("Ingrese el codigo del libro que desea entregar: ");
            int codLibEntregar;
            scanf("%i", &codLibEntregar);
            if (buscarCodLibPrestados(codLibEntregar, usuarioActual)==RET_OK)
            {
                entregarLibro(codLibEntregar);
            }else
            {
                printf("No tienes un libro en tu lista con este codigo\n");
                system("pause");
                system("cls");
            }
        default:
            break;
        }

    } while (opcMenu!=5);
    
}