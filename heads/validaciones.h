#ifndef VALIDACIONES_H
#define VALIDACIONES_H

// bool caracteresPermitidos(char *contenido) {
//   char* allowedChars = " */\n\0\r";
//   int longitudValida = strspn(contenido, allowedChars);

//   printf("longitudValida: %d\n", longitudValida);
//   printf("strlen(contenido): %ld\n", strlen(contenido));

//   return (longitudValida == strlen(contenido));
// }

// Función para verificar si el laberinto tiene salida
bool tieneSalida(char *contenido) {
  if (strpbrk(contenido, "/") == NULL) {
    printf("\nError: El laberinto no tiene salida.\n");
    return false;
  }
  return true;
}

// Función para verificar si el laberinto solo tiene caracteres permitidos
bool caracteresPermitidos(char *contenido) {
  for (int i = 0; i < strlen(contenido); i++) {
    if (contenido[i] != '/' && contenido[i] != '*' && contenido[i] != '\n' && contenido[i] != ' ' && contenido[i] != '\r') {
      printf("\nError: El laberinto contiene caracteres no permitidos.\n");
      printf("El caracter no permitido es: %c\n", contenido[i]);
      return false;
    }
  }
  return true;
}

// Función para verificar que la posición 0,0 esté vacía
int posicionInicialVacia(char *contenido) {
  if (contenido[0] != ' ') {
    printf("\nError: La posición 0,0 no está vacía.\n");
    return false;
  }
  return true;
}

bool mismaCantidadCaracteres(struct Laberinto *laberinto) {
  int cantidadCaracteres = 0;
  int columnasFilaAnterior = 0;
  int cantidadFilas = 0;

  for (int i = 0; i < strlen(laberinto -> mapa); i++) {
    if (laberinto -> mapa[i] == '\n') {
      if (columnasFilaAnterior == 0) {
        columnasFilaAnterior = cantidadCaracteres;
      } else {
        if (columnasFilaAnterior != cantidadCaracteres) {
          printf("\nError: No se cuenta con la misma cantidad de caracteres en todas las filas.\n");
          return false;
        }
      }
      cantidadFilas++;
      cantidadCaracteres = 0;
    } else {
      cantidadCaracteres++;
    }
  }

  laberinto -> filas = cantidadFilas;
  laberinto -> columnas = columnasFilaAnterior - 1; // cuenta el salto de linea como 1

  return true;
}

bool laberintoPermitido(struct Laberinto *laberinto) {
  return tieneSalida(laberinto -> mapa) &&
         caracteresPermitidos(laberinto -> mapa) &&
         mismaCantidadCaracteres(laberinto) &&
         posicionInicialVacia(laberinto -> mapa);
}

#endif