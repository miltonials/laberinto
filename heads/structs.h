#ifndef STRUCTS_H
#define STRUCTS_H


struct ThreadPoint {
  int x;
  int y;
  int direccion; // 0: arriba, 1: derecha, 2: abajo, 3: izquierda
};

struct Laberinto {
  char **mapa;
  int filas;
  int columnas;
};

#endif