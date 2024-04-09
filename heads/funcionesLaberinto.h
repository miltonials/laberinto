#ifndef FUNCIONESLABERINTO_H
#define FUNCIONESLABERINTO_H

#include "validaciones.h"
#include "./hilosLaberinto.h"

/*
Funcion que asigna memoria para el tablero del laberinto
Entrada: Estructura Laberinto
Salida: No tiene
*/
void asignarMemoriaTablero(struct Laberinto *laberinto) {
  int filas = laberinto -> filas, columnas = laberinto -> columnas;

  // Asignación de memoria para las filas
  laberinto -> tablero = (char **) malloc(filas * sizeof(char *));

  // Asignación de memoria para las columnas
  for (int i = 0; i < filas; i++) {
    laberinto ->tablero[i] = (char *)malloc(columnas * sizeof(char));
  }
}

/*
Funcion que rellena el tablero del laberinto
Entrada: Estructura Laberinto
Salida: No tiene
*/
void rellenarTablero(struct Laberinto *laberinto) {
  int filas = laberinto->filas, columnas = laberinto->columnas;
  int contador = 0;

  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      // Ignora saltos de línea y retornos de carro
      while (laberinto->mapa[contador] == '\n' || laberinto->mapa[contador] == '\r') {
        contador++;
      }

      if (laberinto->mapa[contador] == '*' || laberinto->mapa[contador] == '/' ||
          laberinto->mapa[contador] == ' ') {
        laberinto->tablero[i][j] = laberinto->mapa[contador];
        printf("%c", laberinto->tablero[i][j]);
      }
      contador++;
    }
    printf("\n");
  }
  printf("soy prueba\n");
  imprimirTablero(laberinto);
}

/*
Funcion que carga el tablero del laberinto
Entrada: Estructura Laberinto
Salida: No tiene
*/
void cargarTableroLaberinto(struct Laberinto *laberinto) {
  asignarMemoriaTablero(laberinto);
  rellenarTablero(laberinto);
}

/*
Funcion que carga el laberinto
Entrada: No tiene
Salida: No tiene
*/
void cargarLaberinto() {
  struct Laberinto laberinto;
  char rutaArchivo[100];
  char *contenido;

  // Solicitar la ruta del archivo
  printf("\nIngrese la ruta del archivo .txt: ");
  scanf("%s", rutaArchivo);
  // strcpy(rutaArchivo, "./lab1.txt");

  if(!existeArchivo(rutaArchivo)){
    printf("\nError: El archivo no existe o está vacío.\n");
    return;
  }

  contenido = leerArchivo(rutaArchivo);
  laberinto.mapa = contenido;
  laberinto.cantidadHilosCreados = 0;
  laberinto.cantidadHilosMuertos = 0;
  
  if (laberintoPermitido(&laberinto)) {
    struct ThreadPoint x;
    x.id = 0;
    x.columna = 0;
    x.fila = 0;
    x.dir = 2;
    x.pasos = 0;

    printf("Mapa:\n%s\n", laberinto.mapa);
    printf("Cantidad filas: %d\n", laberinto.filas);
    printf("Cantidad columnas: %d\n", laberinto.columnas);
    cargarTableroLaberinto(&laberinto);
    printf("¡Laberinto cargado!\n");
    sleep(3);
    //iniciar juego
    crearHiloTablero(&laberinto, 0, 0, 2, &x);
    printf("El avance del laberinto fue guardado en el archivo 'resultado.txt'.\n");
    printf("Escribe una letra y presiona enter para volver al menú principal...\n");
    scanf("%s", rutaArchivo);
    system("clear");
  }
  else {
    printf("\nError: El laberinto no cumple con las condiciones necesarias.\n");
  }
}

#endif