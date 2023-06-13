#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

#include "global.h"
#include "administrador.h"

int obtenerCodLibros(){
    archivo = fopen("libros.dat", "rb");
    if (archivo==NULL)
    {
        exit(1);
    }

    fseek(archivo, -sizeof(tlibros),SEEK_END);
    tlibros libros;
    fread(&libros, sizeof(tlibros), 1, archivo);

    fclose(archivo);

    return libros.codLibro;
} 

void agregarLibro(){

    archivo = fopen("libros.dat", "ab");
    if (archivo==NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    fclose(archivo);
    
    tlibros libros;
    int ultimoCod = obtenerCodLibros();
    libros.codLibro=ultimoCod+1;
    printf("Ingrese el nombre del libro: ");
    gets(libros.nombreLibro);
    printf("Ingrese el autor del libro: ");
    gets(libros.autorLibro);
    printf("Ingrese la cantidad existente en la biblioteca: ");
    scanf("%i", &libros.cantidadTotal);
    libros.cantidadDisponible=libros.cantidadTotal;
    fflush(stdin);
    archivo = fopen("libros.dat", "ab");
    if (archivo==NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    fwrite(&libros, sizeof(tlibros), 1, archivo);  
    printf("Libro agregado de forma exitosa\n");  
    fclose(archivo);
   
    fflush(stdin);
    system("pause");
    system("cls");
}

void editarLibro(int codLibroEditar){

    FILE *archivo = fopen("libros.dat", "r+b");
    if (archivo == NULL) {
        return;
    }

    tlibros libros;
    while (fread(&libros, sizeof(tlibros), 1, archivo)==1) {
        if (libros.codLibro == codLibroEditar) {
            printf("Ingrese el nuevo nombre del libro: ");
            gets(libros.nombreLibro);
            printf("Ingrese el autor del libro: ");
            gets(libros.autorLibro);
            printf("Ingrese la nueva cantidad de libros disponible: ");
            scanf("%i", &libros.cantidadTotal);
            libros.cantidadDisponible = libros.cantidadTotal;
            fseek(archivo, -sizeof(tlibros),SEEK_CUR);
            fwrite(&libros, sizeof(tlibros), 1, archivo);
        }
        fseek(archivo, 0, SEEK_CUR);
    }

    fclose(archivo);
    system("pause");
    system("cls");
}

RET buscarCodLibros(int codEliminar){

    archivo = fopen("libros.dat", "rb");
    if (archivo == NULL) {
        exit(1);
    }

    tlibros libros;
    fread(&libros, sizeof(tlibros), 1, archivo);
    while (!feof(archivo)) {
        if (libros.codLibro == codEliminar) {
            fclose(archivo);
            return RET_OK;
        }
        fread(&libros, sizeof(tlibros), 1, archivo);
    }
 
    fclose(archivo);
    return RET_FAIL;
}

void eliminarLibro(int codEliminar) {
    archivo = fopen("libros.dat", "rb");
    if (archivo == NULL) {
        return;
    }

    FILE *archivoTemporal = fopen("temp.dat", "wb");
    if (archivoTemporal == NULL) {
        return;
    }

    tlibros libro;

    while (fread(&libro, sizeof(tlibros), 1, archivo) == 1) {
        if (libro.codLibro != codEliminar) {
            fwrite(&libro, sizeof(tlibros), 1, archivoTemporal);
        }
    }

    fclose(archivo);
    fclose(archivoTemporal);

    if (remove("libros.dat") == 0) {
        if (rename("temp.dat", "libros.dat") != 0) {
            printf("No se pudo renombrar el archivo temporal\n");
            return;
        }
    } else {
        printf("Error al eliminar el archivo original\n");
        return;
    }

    printf("Libro eliminado con exito.\n");

    system("pause");
    system("cls");
}

void vistaLibros(){

    archivo = fopen("libros.dat", "rb");
    if (archivo==NULL)
    {
        exit(1);
    }

    tlibros libros;
    fread(&libros, sizeof(tlibros), 1, archivo);
    while (!feof(archivo))  {
       printf("Cod. %i | Nombre Libro: %s | Autor: %s | Cant. Total: %i | Cant. Disponible: %i |\n", libros.codLibro, libros.nombreLibro, libros.autorLibro, 
       libros.cantidadTotal, libros.cantidadDisponible);
       fread(&libros, sizeof(tlibros), 1, archivo);
    }

    fclose(archivo);
    system("pause");
    system("cls");
}

void vistaLibrosPrestados(){
     archivo = fopen("librosPrestados.dat", "rb");
    if (archivo==NULL)
    {
        return;
    }

    tlibrosprestados librosPrestados;
    librosPrestados.usuario[10];

    printf("Lista por libros prestados: \n");
    while (fread(&librosPrestados, sizeof(tlibrosprestados), 1, archivo)==1)  {
        printf("%s \n", librosPrestados.nombreLibro);
                printf("|> Usuario: %s | Fecha Entrega: %i/%i/%i |\n", librosPrestados.usuario,
                librosPrestados.dd, librosPrestados.mm, librosPrestados.aa);
    }
    fclose(archivo);

    system("pause");
    system("cls");
}
void vistaUsuariosConLibros(){

}
void menuUsuarioAdministrador(){
    int opcMenu;
    do
    {
        printf("¿Que desea realizar?\n");
        printf("1. Agregar Libros\n");
        printf("2. Eliminar un libro\n");
        printf("3. Editar informacion del libro\n");
        printf("4. Ver todos los libros\n");
        printf("5. Ver los libros prestados\n");
        printf("6. Ver los usuarios y los libros que tienen\n");
        printf("7. Ver usuarios retrasados con la entrega del libro\n");
        printf("8. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%i", &opcMenu);
        fflush(stdin);
        switch (opcMenu)
        {
        case 1:
            agregarLibro();
            break;
        case 2: 
            printf("Ingrese el codigo del libro que desea eliminar: ");
            int codEliminar;
            scanf("%i", &codEliminar);
            fflush(stdin);
            if (buscarCodLibros(codEliminar)==RET_OK)
            {
                eliminarLibro(codEliminar);
            }else
            {
                printf("No existe un libro con ese codigo\n");
                system("pause");
                system("cls");
            }
            break;
        case 3:
            printf("Ingrese el codigo del libro que desea editar: ");
            int codLibEditar;
            scanf("%i", &codLibEditar);
            fflush(stdin);
            editarLibro(codLibEditar);
            break;
        case 4:
            vistaLibros();
            break;
        case 5:
            vistaLibrosPrestados();
            break;
        default:
            break;
        }
    } while (opcMenu!=8);
    
}