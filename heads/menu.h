#ifndef MENU_H
#define MENU_H

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

#endif