#ifndef HILOSLABERINTO_H
#define HILOSLABERINTO_H


// #include <pthread.h>
//mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//gcc main.c -o main -lpthread
void imprimirTablero(struct Laberinto *laberinto) {
  int filas = laberinto -> filas, columnas = laberinto -> columnas;

  for (int i = 0; i < filas ; i++) {
    printf("|");
    for (int j = 0; j < columnas ; j++) {
      printf("%c", laberinto -> tablero[i][j]);
    }
    printf("|\n");
  }
}

void *iniciarHilo(void *puntox);

void crearHiloTablero(struct Laberinto *laberinto, int fila, int columna, int dir, int pasos) {
    pthread_t t1;
    struct ThreadPoint hiloTablero;
    pthread_mutex_lock(&mutex);
    laberinto->cantidadHilosCreados++;
    pthread_mutex_unlock(&mutex);
    hiloTablero.id = laberinto->cantidadHilosCreados;
    hiloTablero.columna = columna;
    hiloTablero.fila = fila;
    hiloTablero.dir = dir;
    hiloTablero.gps = laberinto;
    hiloTablero.thread = t1;
    hiloTablero.pasos = pasos;
    hiloTablero.isFinished = false;
    pthread_create(&t1, NULL, iniciarHilo,(void*) &hiloTablero);
    pthread_join(t1, NULL);
}

void crearHilosDerivados(struct ThreadPoint *punto) {
  int columna = punto->columna, fila = punto->fila, dir = punto->dir;
  int columnasTablero = punto->gps->columnas;
  int filasTablero = punto->gps->filas;
  struct Laberinto *laberinto = punto->gps;
  bool puedeCrearHiloArriba = dir != 0 && fila - 1 >= 0 && (laberinto->tablero[fila - 1][columna] == ' ' || laberinto->tablero[fila - 1][columna] == '\r');
  
  bool puedeCrearHiloDerecha = dir != 1 && columna + 1 < columnasTablero && (laberinto->tablero[fila][columna + 1] == ' ' || laberinto->tablero[fila][columna + 1] == '\r');
  
  bool puedeCrearHiloAbajo = dir != 2 && fila + 1 < filasTablero && laberinto->tablero[fila + 1][columna] == ' ';
  
  bool puedeCrearHiloIzquierda = dir != 3 && columna - 1 >= 0 && (laberinto->tablero[fila][columna - 1] == ' ' || laberinto->tablero[fila][columna - 1] == '\n');

  if (puedeCrearHiloDerecha) {
    crearHiloTablero(laberinto, fila, columna + 1, 1, punto->pasos + 1);
  }
  if (puedeCrearHiloIzquierda) {
    crearHiloTablero(laberinto, fila, columna - 1, 3, punto->pasos + 1);
  }
  if (puedeCrearHiloAbajo) {
    crearHiloTablero(laberinto, fila + 1, columna, 2, punto->pasos + 1);
  }
  if (puedeCrearHiloArriba) {
    crearHiloTablero(laberinto, fila - 1, columna, 0, punto->pasos + 1);
  }

}

void *iniciarHilo(void *puntox) {
  struct ThreadPoint *punto = (struct ThreadPoint *) puntox;
  printf("%d Hilo creado\n",punto->id);

  bool puedeAvanzar = true;
  while (puedeAvanzar) {
    if(punto->gps->tablero[punto->fila][punto->columna] == '*') {
      pthread_exit(NULL);
      crearHilosDerivados(punto);
      puedeAvanzar = false;
    }
    if (punto->gps->tablero[punto->fila][punto->columna] == ' ') {
      // aumentar pasos
      punto->pasos++;
      pthread_mutex_lock(&mutex);
      punto->gps->tablero[punto->fila][punto->columna] = '0' + punto->id - 1;
      pthread_mutex_unlock(&mutex);
      crearHilosDerivados(punto);
      if (punto->dir == 0) { //arriba
        if (punto->fila - 1 < punto->gps->filas) {
          punto->fila--;
          if (punto->fila < 0) {
            punto->fila = 0;
          }
        } else {
          puedeAvanzar = false;
        }
      } else if (punto->dir == 1) { //derecha
        if (punto->columna + 1 < punto->gps->columnas) {
          punto->columna++;
        } else {
          puedeAvanzar = false;
        }
      } else if (punto->dir == 2) { //abajo
        
        // imprimirTablero(punto->gps);
        if (punto->fila + 1 < punto->gps->filas) {
          punto->fila++;
        } else {
          puedeAvanzar = false;
        }
      } else if (punto->dir == 3) {//izquierda
        if (punto->columna - 1 >= 0) {
          punto->columna--;
          if (punto->columna < 0) {
            punto->columna = 0;
          }
        } else {
          puedeAvanzar = false;
        }
      }
    } else {
      puedeAvanzar = false;
    }
    if (punto->gps->tablero[punto->fila][punto->columna] == '/') {
      printf("Hilo %d ha llegado a la meta\n", punto->id);
      printf("Pasos: %d\n", punto->pasos);
      // cambiar estado a terminado
      punto->isFinished = true;
      // mensaje de cantidad de pasos 
      printf("La cantidad de pasos es: %d\n", punto->pasos);
      // imprimir tablero
      // imprimirTablero(punto->gps);
      // terminar hilo
      puedeAvanzar = false;
      // break;
    }
  }

  pthread_join((pthread_t) punto->thread, NULL);
  pthread_mutex_lock(&mutex);
  punto->gps->cantidadHilosMuertos++;
  pthread_mutex_unlock(&mutex);
  printf("%d Hilo muerto\n",punto->id);
  // if (punto->gps->cantidadHilosCreados == punto->gps->cantidadHilosMuertos) {
    // printf("Todos los hilos han terminado\n");
    printf("Tablero final\n");
    imprimirTablero(punto->gps);
    printf("\n");
    printf("Cantidad de hilos creados: %d\n", punto->gps->cantidadHilosCreados);
    printf("Cantidad de hilos muertos: %d\n", punto->gps->cantidadHilosMuertos);
    printf("------------------------------------------------------------\n");
  // }

  pthread_exit(NULL);
}

#endif