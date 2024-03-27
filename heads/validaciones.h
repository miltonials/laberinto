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

bool mismaCantidadCaracteres(char *contenido) {
  int cantidadCaracteres = 0;
  int filaAnterior = 0;
  for (int i = 0; i < strlen(contenido); i++) {
    if (contenido[i] == '\n') {
      if (filaAnterior == 0) {
        filaAnterior = cantidadCaracteres;
      } else {
        if (filaAnterior != cantidadCaracteres) {
          printf("\nError: No se cuenta con la misma cantidad de caracteres en todas las filas.\n");
          return false;
        }
      }
      cantidadCaracteres = 0;
    } else {
      cantidadCaracteres++;
    }
  }
  return true;
}

bool laberintoPermitido(char *contenido) {
  
  return (tieneSalida(contenido) && caracteresPermitidos(contenido) && mismaCantidadCaracteres(contenido) && posicionInicialVacia(contenido));
}

#endif