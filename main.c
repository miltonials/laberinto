#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función para mostrar el menú principal
void menuPrincipal() {
  int opcion;
  do {
    system("cls"); // Limpiar la pantalla
    printf("**** Laberinto ****\n\n");
    printf("1. Cargar laberinto\n");
    printf("2. Salir\n\n");
    printf("Ingrese una opción: ");
    scanf("%d", &opcion);
  } while (opcion < 1 || opcion > 2);

  switch (opcion) {
    case 1:
      cargarLaberinto();
      break;
    case 2:
      printf("\n¡Hasta pronto!\n");
      exit(0);
      break;
  }
}

// Función para cargar el laberinto
void cargarLaberinto() {
  char rutaArchivo[100];
  FILE *archivo;

  // Solicitar la ruta del archivo
  printf("\nIngrese la ruta del archivo .txt: ");
  scanf("%s", rutaArchivo);

  // Validar que el archivo exista y no esté vacío
  archivo = fopen(rutaArchivo, "r");
  if (archivo == NULL) {
    printf("\nError: El archivo no existe o está vacío.\n");
    system("pause");
    menuPrincipal();
    return;
  }
  // Se llama a funciones para más validaciones aquí
  /*
  Hay que validar que el laberinto:
    1. tenga salida
    2. solo tenga caracteres permitidos
    3. No deben haber saltos de linea vacíos
    4. la posición 0,0 debe estar vacía
  */

  // Mostrar opciones Iniciar juego y Volver
  int opcion;
  do {
    system("cls");
    printf("**** Laberinto ****\n\n");
    printf("¡Laberinto cargado correctamente!\n\n");
    printf("1. Iniciar juego\n");
    printf("2. Volver\n\n");
    printf("Ingrese una opción: ");
    scanf("%d", &opcion);
  } while (opcion < 1 || opcion > 2);

  switch (opcion) {
    case 1:
      // Iniciar juego
      printf("\nHola mundo!\n");
      // Guardar "Hola mundo!" en un archivo
      FILE *resultado;
      resultado = fopen("resultado.txt", "w");
      fprintf(resultado, "Hola mundo!");
      fclose(resultado);
      system("pause");
      menuPrincipal();
      break;
    case 2:
      // Volver al menú principal
      menuPrincipal();
      break;
  }

  fclose(archivo);
}

int main() {
  menuPrincipal();
  return 0;
}
