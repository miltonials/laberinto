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



// Función para verificar si el laberinto tiene salida
int tieneSalida(FILE *archivo) {
  // recorrer el archivo para verificar si tiene salida debe haber un / 
  fseek(archivo, 0, SEEK_SET);
  char caracter;
  while ((caracter = fgetc(archivo)) != EOF) {
    printf("%c", caracter);
    if (caracter == '/') {
      return 1;
    }
  }
  printf("\nError: El laberinto no tiene salida.\n");
  return 0;
}

// Función para verificar si el laberinto solo tiene caracteres permitidos
int caracteresPermitidos(FILE *archivo) {
  fseek(archivo, 0, SEEK_SET);
  char caracter;
  // recorrer el archivo para verificar si tiene caracteres permitidos /, *, saltos de linea y espacio en blanco
  while ((caracter = fgetc(archivo)) != EOF) {
    printf("%c", caracter);
    if (caracter == '/' || caracter == '*' || caracter == '\n' || caracter == ' ' || caracter == '\r') {
      continue;
    } else {
      printf("\nError: El laberinto contiene caracteres no permitidos.\n");
      printf("%c", "El caracter no permitido es: ", caracter);
      return 0;
    }
  }
  return 1;
}

// Función para verificar que no haya saltos de línea vacíos
int noSaltosLineaVacios(FILE *archivo) {
  fseek(archivo, 0, SEEK_SET);
  char caracter;
  while ((caracter = fgetc(archivo)) != EOF) {
    if (caracter == '\n' && fgetc(archivo) == '\n') {
      printf("\nError: El archivo contiene saltos de línea vacíos.\n");
      return 0;
    }
  }
  return 1;
}

// Función para verificar que la posición 0,0 esté vacía
int posicionInicialVacia(FILE *archivo) {
  fseek(archivo, 0, SEEK_SET);
  if (fgetc(archivo) != ' ') {
    printf("\nError: La posición 0,0 no está vacía.\n");
    return 0;
  }
  return 1;
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
  // imprimir laberinto
  char caracter;
  int contador = 0;
  while ((caracter = fgetc(archivo)) != EOF) {
    printf("%c", caracter);
    printf("%d", contador);
    contador++;
  }

  // caracteres permitidos /, *, saltos de linea y espacio en blanco
  // Validar condiciones adicionales
  if (!tieneSalida(archivo) || !caracteresPermitidos(archivo) || !noSaltosLineaVacios(archivo) || !posicionInicialVacia(archivo)) {
    fclose(archivo);
    menuPrincipal();
    return;
  }
  
  

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
