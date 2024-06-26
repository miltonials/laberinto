#ifndef HILOSLABERINTO_H
#define HILOSLABERINTO_H

#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*
Funcion que imprime el tablero del laberinto
Entrada: Estructura Laberinto
Salida: No tiene
*/
void imprimirTablero(struct Laberinto *laberinto) {
  int filas = laberinto->filas, columnas = laberinto->columnas;
  printf("--------------------------------\n");
  for (int i = 0; i < filas; i++) {
    printf("|");
    for (int j = 0; j < columnas; j++) {
      printf("%c", laberinto->tablero[i][j]);
    }
    printf("|\n");
  }
}

void *iniciarHilo(void *puntox);

/*
Funcion que crea un hilo para el tablero
Entrada: Estructura Laberinto, fila, columna, dirección y punto
Salida: No tiene
*/
void crearHiloTablero(struct Laberinto *laberinto, int fila, int columna, int dir, struct ThreadPoint *punto) {
  pthread_mutex_init(&mutex, NULL);
  pthread_t t1;
  struct ThreadData data;

  laberinto->cantidadHilosCreados++;
  data.punto.id = laberinto->cantidadHilosCreados;
  data.punto.columna = punto->columna;
  data.punto.fila = punto->fila;
  data.punto.dir = punto->dir;
  data.punto.pasos = punto->pasos;
  data.laberinto = laberinto;
  data.punto.isFinished = false;
  printf("-----------------------------\n");
  pthread_create(&t1, NULL, iniciarHilo, (void *) &data);
  pthread_join(t1, NULL);
}

/*
Funcion que crea hilos derivados
Entrada: id, fila, columna, dirección, pasos y laberinto
Salida: No tiene
*/
void crearHilosDerivados(int id, int fila, int columna, int dir, int pasos, struct Laberinto *laberinto) {
  int columnasTablero = laberinto->columnas;
  int filasTablero = laberinto->filas;
  
  pthread_mutex_lock(&mutex);
  pthread_mutex_unlock(&mutex);

  bool canGoUp = dir != 0 && fila - 1 >= 0 &&
                  (laberinto->tablero[fila - 1][columna] == ' ' || laberinto->tablero[fila - 1][columna] == '/');
  bool canGoRigh = dir != 1 && columna + 1 < columnasTablero &&
                  (laberinto->tablero[fila][columna + 1] == ' ' || laberinto->tablero[fila][columna + 1] == '/');
  bool canGoDown = dir != 2 && fila + 1 < filasTablero &&
                  (laberinto->tablero[fila + 1][columna] == ' ' || laberinto->tablero[fila + 1][columna] == '/');
  bool canGoLeft = dir != 3 && columna - 1 >= 0 &&
                  (laberinto->tablero[fila][columna - 1] == ' ' || laberinto->tablero[fila][columna - 1] == '/');

  pthread_t th[3];
  int cuentaCreados = 0;

  if (canGoRigh) {
    pthread_t t;
    struct ThreadPoint nPunto;
    struct ThreadData data;
    pthread_mutex_lock(&mutex);
    laberinto->cantidadHilosCreados++;
    pthread_mutex_unlock(&mutex);
    data.punto.id = laberinto->cantidadHilosCreados;
    data.punto.columna = columna + 1;
    data.punto.fila = fila;
    data.punto.dir = 1;
    data.punto.gps = laberinto;
    data.laberinto = laberinto;
    data.punto.pasos = pasos;
    data.punto.isFinished = false;

    pthread_create(&t, NULL, iniciarHilo, (void *)&data);
    th[cuentaCreados++] = t;
    sleep(1);
  }
  if (canGoLeft) {
    pthread_t t;
    struct ThreadPoint nPunto;
    struct ThreadData data;
    pthread_mutex_lock(&mutex);
    laberinto->cantidadHilosCreados++;
    pthread_mutex_unlock(&mutex);
    data.punto.id = laberinto->cantidadHilosCreados;
    data.punto.columna = columna - 1;
    data.punto.fila = fila;
    data.punto.dir = 3;
    data.punto.gps = laberinto;
    data.laberinto = laberinto;
    data.punto.pasos = pasos;
    data.punto.isFinished = false;

    pthread_create(&t, NULL, iniciarHilo, (void *)&data);
    th[cuentaCreados++] = t;
    sleep(1);
  }
  if (canGoDown) {
    pthread_t t;
    struct ThreadPoint nPunto;
    struct ThreadData data;
    pthread_mutex_lock(&mutex);
    laberinto->cantidadHilosCreados++;
    pthread_mutex_unlock(&mutex);
    data.punto.id = laberinto->cantidadHilosCreados;
    data.punto.columna = columna;
    data.punto.fila = fila + 1;
    data.punto.dir = 2;
    data.punto.gps = laberinto;
    data.laberinto = laberinto;
    data.punto.pasos = pasos;
    data.punto.isFinished = false;

    pthread_create(&t, NULL, iniciarHilo, (void *)&data);
    th[cuentaCreados++] = t;
    sleep(1);
  }
  if (canGoUp) {
    pthread_t t;
    struct ThreadPoint nPunto;
    struct ThreadData data;
    pthread_mutex_lock(&mutex);
    laberinto->cantidadHilosCreados++;
    pthread_mutex_unlock(&mutex);
    data.punto.id = laberinto->cantidadHilosCreados;
    data.punto.columna = columna;
    data.punto.fila = fila - 1;
    data.punto.dir = 0;
    data.punto.gps = laberinto;
    data.laberinto = laberinto;
    data.punto.pasos = pasos;
    data.punto.isFinished = false;

    pthread_create(&t, NULL, iniciarHilo, (void *)&data);
    th[cuentaCreados++] = t;
    sleep(1);
  }
}

int getPointChar(int id) {
  int ascii = '0' + id - 1;
  ascii = (ascii - 48) % (126 - 48 + 1) + 48; // para asegurar que la impressión sea un caracter imprimible
  return ascii;
}

/*
Funcion que imprime la información de un punto
Entrada: Estructura ThreadPoint
Salida: No tiene
*/
void imprimirInformacionPunto(struct ThreadPoint punto, struct Laberinto *laberinto) {
  printf("========== Hilo %d finalizado ==========\n", punto.id - 1);
  printf("Fila: %d\n", punto.fila);
  printf("Columna: %d\n", punto.columna);
  printf("Dirección: %d\n", punto.dir);
  printf("Pasos: %d\n", punto.pasos);
  printf("Símbolo en el tablero: %c\n", getPointChar(punto.id));
  printf("¿Llegó a la meta? %s\n", punto.isFinished ? "Sí" : "No");
  if (punto.isFinished) {
    printf("=====================================\n");
    printf("¡¡¡Hilo %d llegó a la meta!!!\n", punto.id - 1);
    printf("=====================================\n");
    printf("¿Desea continuar la ejecución? (s/n): ");
    
    char continuar;
    scanf(" %c", &continuar);
    if (continuar == 'n') {
      laberinto->terminar = true;
    }
  }
  printf("=====================================\n");
}

/*
Funcion que marca el tablero con un caracter
Entrada: Estructura Laberinto y ThreadPoint
Salida: No tiene
*/
void marcarTablero(struct Laberinto *laberinto, struct ThreadPoint punto) {
  int ascii = getPointChar(punto.id);

  if (ascii == '/') {
    laberinto->tablero[punto.fila][punto.columna] = '+';
  }
  else if (ascii == '*') {
    laberinto->tablero[punto.fila][punto.columna] = '-';
  }
  else {
    laberinto->tablero[punto.fila][punto.columna] = ascii;
  }

  punto.pasos++;
}


/*
Funcion que inicia un hilo
Entrada: Puntero a void
Salida: No tiene
*/
void *iniciarHilo(void *arg) {
  pthread_mutex_lock(&mutex);
  struct ThreadData *data = (struct ThreadData *) arg;
  struct Laberinto *laberinto = data->laberinto;
  struct ThreadPoint punto = data->punto;
  pthread_mutex_unlock(&mutex);

  bool puedeAvanzar = true;
  while (puedeAvanzar && !laberinto->terminar) {
    pthread_mutex_lock(&mutex);
    if (laberinto->tablero[punto.fila][punto.columna] == ' ') {
      marcarTablero(laberinto, punto);
      escribirArchivoLaberinto(laberinto);
      // system("clear");
      // pthread_join(pthread_self(), NULL);
      imprimirTablero(laberinto);
      pthread_mutex_unlock(&mutex);
      sleep(1);
      crearHilosDerivados(punto.id, punto.fila, punto.columna, punto.dir, punto.pasos, laberinto);
      pthread_mutex_lock(&mutex);
      if (punto.dir == 0) { // arriba
        if (punto.fila - 1 < laberinto->filas) {
          punto.fila--;
          if (punto.fila < 0) {
            punto.fila = 0;
          }
        }
        else {
          puedeAvanzar = false;
        }
      }
      else if (punto.dir == 1) { // derecha
        if (punto.columna + 1 < laberinto->columnas) {
          punto.columna++;
        }
        else {
          puedeAvanzar = false;
        }
      }
      else if (punto.dir == 2) { // abajo
        if (punto.fila + 1 < laberinto->filas) {
          punto.fila++;
        }
        else {
          puedeAvanzar = false;
        }
      }
      else if (punto.dir == 3) { // izquierda
        if (punto.columna - 1 >= 0) {
          punto.columna--;
          if (punto.columna < 0) {
            punto.columna = 0;
          }
        } else {
          puedeAvanzar = false;
        }
      }
    }
    else {
      puedeAvanzar = false;
    }
    if (laberinto->tablero[punto.fila][punto.columna] == '/') {
      puedeAvanzar = false;
      punto.isFinished = true;
    }
    pthread_mutex_unlock(&mutex);
  }
  laberinto->cantidadHilosMuertos++;
  
  pthread_mutex_lock(&mutex);
  imprimirInformacionPunto(punto, laberinto);
  pthread_mutex_unlock(&mutex);
  while(laberinto->cantidadHilosMuertos < laberinto->cantidadHilosCreados) {
    pthread_mutex_lock(&mutex);
    pthread_mutex_unlock(&mutex);
  }
  pthread_exit(NULL);
}

#endif