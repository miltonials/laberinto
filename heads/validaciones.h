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
/*
Función que verifica si el laberinto tiene salida.
Entrada: contenido, contenido del laberinto.
Salida: true si el laberinto tiene salida, false en caso contrario.
*/
bool tieneSalida(char *contenido) {
  if (strpbrk(contenido, "/") == NULL) {
    printf("\nError: El laberinto no tiene salida.\n");
    return false;
  }
  return true;
}

// Función para verificar si el laberinto solo tiene caracteres permitidos
/*
Función que verifica si el laberinto solo tiene caracteres permitidos.
Entrada: contenido, contenido del laberinto.
Salida: true si el laberinto solo tiene caracteres permitidos, false en caso contrario.
*/
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
/*
Función que verifica que la posición 0,0 esté vacía.
Entrada: contenido, contenido del laberinto.
Salida: true si la posición 0,0 está vacía, false en caso contrario.
*/
int posicionInicialVacia(char *contenido) {
  if (contenido[0] != ' ') {
    printf("\nError: La posición 0,0 no está vacía.\n");
    return false;
  }
  return true;
}

/*
Función que verifica si todas las filas tienen la misma cantidad de caracteres.
Entrada: laberinto, estructura Laberinto.
Salida: true si todas las filas tienen la misma cantidad de caracteres, false en caso contrario.
*/
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

/*
Función que verifica si el laberinto es permitido.
Entrada: laberinto, estructura Laberinto.
Salida: true si el laberinto es permitido, false en caso contrario.
*/
bool laberintoPermitido(struct Laberinto *laberinto) {
  return tieneSalida(laberinto -> mapa) &&
         caracteresPermitidos(laberinto -> mapa) &&
         mismaCantidadCaracteres(laberinto) &&
         posicionInicialVacia(laberinto -> mapa);
}

#endif