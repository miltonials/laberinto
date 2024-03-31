#ifndef FUNCIONESLABERINTO_H
#define FUNCIONESLABERINTO_H

#include <unistd.h>

#include "validaciones.h"
#include "./hilosLaberinto.h"


void asignarMemoriaTablero(struct Laberinto *laberinto) {
  int filas = laberinto -> filas, columnas = laberinto -> columnas;

  // Asignación de memoria para las filas
  laberinto -> tablero = (char **) malloc(filas * sizeof(char *));

  // Asignación de memoria para las columnas
  for (int i = 0; i < filas; i++) {
    laberinto ->tablero[i] = (char *)malloc(columnas * sizeof(char));
  }
}

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
}


void cargarTableroLaberinto(struct Laberinto *laberinto) {
  asignarMemoriaTablero(laberinto);
  rellenarTablero(laberinto);
}


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
  }

  contenido = leerArchivo(rutaArchivo);
  laberinto.mapa = contenido;
  laberinto.cantidadHilosCreados = 0;
  laberinto.cantidadHilosMuertos = 0;
  
  if (laberintoPermitido(&laberinto)) {
    printf("Mapa:\n%s\n", laberinto.mapa);
    printf("Cantidad filas: %d\n", laberinto.filas);
    printf("Cantidad columnas: %d\n", laberinto.columnas);
    cargarTableroLaberinto(&laberinto);
    printf("¡Laberinto cargado!\n");
    //iniciar juego
    imprimirTablero(&laberinto);
    pthread_mutex_init(&mutex, NULL);
    // pthread_mutex_init(&mutex, NULL);
    crearHiloTablero(&laberinto, 0, 0, 1, 0);
    pthread_mutex_destroy(&mutex);
    // pthread_mutex_destroy(&mutex);
    // sleep(5);
    escribirArchivoLaberinto(&laberinto);
  }
  else {
    printf("\nError: El laberinto no cumple con las condiciones necesarias.\n");
  }
}

#endif