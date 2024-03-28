#ifndef STRUCTS_H
#define STRUCTS_H



struct Laberinto {
  char *mapa;
  char **tablero;
  int filas;
  int columnas;
  int cantidadHilosCreados;
  int cantidadHilosMuertos;
};

struct ThreadPoint {
  int id;
  int fila;
  int columna;
  int dir; // 0: arriba, 1: derecha, 2: abajo, 3: izquierda
  struct Laberinto *gps;
  pthread_t thread;
};

#endif