#ifndef MENU_H
#define MENU_H

#include "validaciones.h"

void cargarLaberinto();

// Función para mostrar el menú principal
void menuPrincipal() {
  int opcion;
  do {
    printf("**** Laberinto ****\n\n");
    printf("1. Cargar laberinto\n");
    printf("2. Salir\n\n");
    printf("Ingrese una opción: ");
    scanf("%d", &opcion);
    
    switch (opcion) {
      case 1:
        cargarLaberinto();
        break;
      case 2:
        printf("\n¡Hasta pronto!\n");
        exit(0);
        break;
      default:
        printf("\nError: Opción no válida.\n");
        break;
    }
  } while (opcion != 2);

}

void cargarLaberinto() {
  char rutaArchivo[100];
  char *contenido;

  // Solicitar la ruta del archivo
  printf("\nIngrese la ruta del archivo .txt: ");
  scanf("%s", rutaArchivo);

  if(!existeArchivo(rutaArchivo)){
    printf("\nError: El archivo no existe o está vacío.\n");
  }

  contenido = leerArchivo(rutaArchivo);

  if (laberintoPermitido(contenido)) {
    printf("\nINICIANDO\n");
  }
  else {
    printf("\nError: El laberinto no cumple con las condiciones necesarias.\n");
  }
}

#endif