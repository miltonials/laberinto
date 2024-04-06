#ifndef STRUCTS_H
#define STRUCTS_H


/*
Estructura que representa un laberinto.
datos del laberinto:
mapa: arreglo de caracteres que representa el laberinto.
tablero: arreglo de arreglos de caracteres que representa el laberinto.
filas: cantidad de filas del laberinto.
columnas: cantidad de columnas del laberinto.
cantidadHilosCreados: cantidad de hilos creados.
cantidadHilosMuertos: cantidad de hilos muertos.
*/
struct Laberinto {
  char *mapa;
  char **tablero;
  int filas;
  int columnas;
  int cantidadHilosCreados;
  int cantidadHilosMuertos;
};

/*
Estructura que representa un punto en el laberinto.
datos del punto:
id: identificador del punto.
fila: fila del punto.   
columna: columna del punto.
dir: dirección del punto. 0: arriba, 1: derecha, 2: abajo, 3: izquierda.
gps: puntero al laberinto.
pasos: cantidad de pasos que ha dado el punto.
isFinished: indica si el punto ha llegado a la salida.
*/
struct ThreadPoint {
  int id;
  int fila;
  int columna;
  int dir; // 0: arriba, 1: derecha, 2: abajo, 3: izquierda
  struct Laberinto *gps;
  int pasos;
  bool isFinished;  
};

/*
Esta estructura se utiliza para pasar los datos necesarios a los hilos.
datos del hilo:
punto: punto en el laberinto.
laberinto: laberinto.
*/
struct ThreadData {
  struct ThreadPoint punto;
  struct Laberinto *laberinto;
};

#endif