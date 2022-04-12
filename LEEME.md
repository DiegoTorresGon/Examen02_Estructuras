# IMP: Un lenguaje de programación simple e imperativo

Los programas de computadora suelen ser representados en memoria como
árboles (llamados árboles de sintaxis). Utilizar esta estructura
permite manipular, transformar y ejecutar programas de manera mas
sencilla a que en su representación textual (como aparecen en el
archivo donde programas).

En esta serie de clases vamos a implementar un pequeño intérprete para
un lenguaje de programación simple e imperativo llamado IMP. La
sintaxis del lenguaje es de la siguiente forma:

El conjunto de terminales es:
```
{ :=, (, ), ;, while, do, if, then, else,
  true, false, =, <, and, or, not,
  +, -, *, x, [, ],
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
```

El conjunto de no-terminales (o categorías sintácticas) es:
```
{ P, B, A, X, N }
```

que representan respecivamente a programas **P**, expresiones
Booleanas **B**, expresiones aritméticas **A**, localidades de memoria
**X** y números naturales **N**.

El no-terminal inicial es `P`.

Las producciones de la gramática corresponden a las siguientes reglas:
```
P -> skip | X := A | (P ; P) | (while B do P) | (if B then P else P)
B -> true | false | (A = A) | (A < A) | (B and B) | (B or B) | not B
A -> N | X | (A + A) | (A - A) | (A * A)
X -> x[A]
N -> cualquier natural
```

## Cómo trabajar en esta base de código

A continuación se muestra la estructura del directorio raíz:
```
.
├── include
│   ├── imp.h
│   └── tests.h
├── LEEME.md
├── Makefile
├── src
│   └── imp.c
└── test
    └── imp.c
```

El archivo `include/imp.h` es la cabecera de la biblioteca con la
especificación de los tipos de datos y operaciones definidas sobre
ellos:
- Constructores: operaciones que crean objetos
- Predicados: operaciones booleanas sobre alguna propiedad de los objetos
- Selectores: operaciones que permiten inspeccionar la estructura de los objetos
- Destructores: operaciones que liberan la memoria ocupada por objetos
- Evaluadores: operaciones que interpretan expresiones del lenguaje

La definición de la estructura interna de los objetos y la
implementación de las operaciones se encuentra en el archivo
`src/imp.c`.

Los archivos de prueba se encuentran en el archivo `test/imp.c` y
utilizan los macros para pruebas unitarias de la cabecera
`include/tests.h`.

El archivo `Makefile` contiene las reglas para compilar la biblioteca
IMP y ejecutar las pruebas unitarias.

### Ciclo de desarrollo

Para trabajar sobre esta base de código se recomienda utilizar una
consola/terminal que pueda utilizar el programa GNU Make.

1. Escribe una o más pruebas unitarias que verifiquen que el cambio
   que planeas realizar es correcto.
2. Ejecuta el comando `make` en la consola para observar que las
   pruebas fallan.
3. Modificar el código y repetir paso 2 hasta que todas las pruebas
   sean exitosas.
4. Regresar al paso 1.

Es posible que dependiendo del compilador y el sistema operativo que
utilices debas realizar algunos cambios en el archivo `Makefile`, en
particular las opciones `-fsanitize` y `-fno-sanitize-recover` no
tienen soporte en las versiones de Windows de `GCC`.

Como alternativa puedes modificar:
```
TESTFLAGS=-g3 -O0
```
y eliminar las opciones mencionadas arriba, por otro lado vas a
necesitar buscar en internet de qué forma puedes verificar que estás
liberando toda la memoria que reservas durante la ejecución de tu
programa.

## Historia de versiones

## 2022-03-29
Se ha implementado las expresiones aritméticas sin localidades de memoria
```
A -> N | (A + A) | (A - A) | (A * A)
```

## 2022-03-30
Posiblemente implementar expresiones booleanas
```
B -> true | false | (A = A) | (A < A) | (B and B) | (B or B) | not B
```
