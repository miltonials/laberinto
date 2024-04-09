#ifndef UTIL_H
#define UTIL_H

//archivo existe
/*
Función que verifica si un archivo existe.
entrada: nombreArchivo, nombre del archivo.
retorna: true si el archivo existe, false en caso contrario.
*/
bool existeArchivo(char *nombreArchivo) {
  FILE *archivo = fopen(nombreArchivo, "r");
  if (archivo == NULL) {
    return false;
  }
  fclose(archivo);
  return true;
}

//leer archivo
/*
Función que lee un archivo y retorna su contenido.
entrada: nombreArchivo, nombre del archivo.
retorna: contenido del archivo.
*/
char *leerArchivo(char *nombreArchivo) {
  FILE *archivo = fopen(nombreArchivo, "r");
  if (archivo == NULL) {
    printf("Error al abrir el archivo\n");
    exit(1);
  }

  fseek(archivo, 0, SEEK_END);
  long fsize = ftell(archivo);
  fseek(archivo, 0, SEEK_SET);

  char *contenido = malloc(fsize + 1);
  fread(contenido, fsize, 1, archivo);
  fclose(archivo);

  contenido[fsize] = 0;
  return contenido;
}

/*
Función que escribe un archivo con el laberinto.
entrada: laberinto, estructura Laberinto.
salida: no tiene.
*/
void escribirArchivoLaberinto(struct Laberinto *laberinto) {
  FILE *archivo = fopen("resultado.txt", "w");
  if (archivo == NULL) {
    printf("Error al abrir el archivo\n");
    exit(1);
  }

  for (int i = 0; i < laberinto->filas; i++) {
    for (int j = 0; j < laberinto->columnas; j++) {
      fprintf(archivo, "%c", laberinto->tablero[i][j]);
    }
    fprintf(archivo, "\n");
  }

  fclose(archivo);
}

#endif