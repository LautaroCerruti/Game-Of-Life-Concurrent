# Trabajo Práctico 1

Primer Trabajo Práctico de la materia *Sistemas Operativos I* para obtener la
regularización.

El trabajo consistirá en la implementación de un simulador del [Juego de la Vida
de Conway](https://es.wikipedia.org/wiki/Juego_de_la_vida). En particular se
pide que la simulación se realice implementando un programa concurrente,
tratando de optimizar la disponibilidad del hardware subyacente.
Pero principalmente:

+ evitando **estados inconsistentes del juego**. La ejecución secuencial o
  paralela debería otorgar el mismo tablero final.
+ evitando la aparición de **deadlocks**.

Para esto pueden utilizar todos los recursos vistos en la primer practica .
Implementados por ustedes, o los disponibles en la librería de *POSIX THREADS*
(y semáforos).

El trabajo se puede realizar de forma individual o de a lo sumo 2 estudiantes.
Para indicar la situación deberán completar un
[formulario](https://forms.gle/TvfeSuHqr6Y53cfW9) tanto si lo hacen de forma
grupal o individual.

## Juego de la Vida

El Juego de la Vida fue planteado por el matemático [John Horton
Congway](https://en.wikipedia.org/wiki/John_Horton_Conway) en 1970. Es un juego
sin jugadores que planteado como un *autómata celular*. Esto significa que la
única interacción está dada al comienzo del juego, planteando un tablero
inicial, y que luego el sistema evolucionará siguiendo las reglas establecidas.

### Reglas

El juego presenta un tablero bidimensional infinito compuesto por células. Las
células pueden estar *vivas* o *muertas*. Al ser un tablero bidimensional e
infinito, cada célula tiene 8 células vecinas.

En cada momento, las células pasan a estar vivas o muertas siguiendo las reglas:

+ Toda célula viva con 2 o 3 vecinos vivos sobrevive,
+ Toda célula muerta con exactamente con 3 vecinos vivo revive,
+ El resto de las células vivas mueren en la siguiente generación, como a su vez
  el resto de las células muertas se mantienen muertas.
  
El patrón inicial del tablero se le suele llamar *semilla*. La primer generación
es el resultado de aplicar las 3 reglas antes descriptas a todas las células de
la semilla, las transiciones se dan de forma simultanea. Las reglas se siguen
aplicando de la misma manera para obtener futuras generaciones.

#### Ejemplo

Concentrándonos en un fragmento del tablero, donde las células fuera del tablero
se asumen muertas. Las células vivas se codifican con una O mientras que las
muertas con una X.

| X | X | X |

| O | O | O |

| X | X | X |

Aplicando las reglas evoluciona a:

| X | O | X |

| X | O | X |

| X | O | X |

Que a su vez evoluciona a:

| X | X | X |

| O | O | O |

| X | X | X |

Y así...

## Notas para la implementación

Dado que no tenemos la posibilidad de implementar un tablero infinito en una
computadora con recursos limitados, vamos a trabajar con tablero de dimensiones finitas.
Asumimos entonces que las fronteras se comparten, doblando el tablero.
Es decir, la frontera superior **es** la frontera inferior, mientras que la
frontera de la izquierda **es** la frontera de la derecha.

En un tablero *tab* de dimensiones `4 x 4` , la quinta fila sería la primer
fila, mientras que la quinta columna volvería a ser la primer columna. El
pensamiento es similar al que se toman en los mapas para describir el mundo.

Se les presentarán dos archivos de cabecera [Board.h](./Board.h) y
[Game.h](./Game.h). Principalmente para las realización de pruebas sobre
sus programas.

El objetivo de [Board.h](./Board.h) es simplemente la implementación de un
tablero de caracteres. Mientras que [Game.h](./Game.h) define:

+ las constantes `ALIVE` y `DEAD` con un `enum`.
+ función de lectura de un *juego* desde un archivo
+ función de escritura de un tablero en un archivo
+ la ejecución del juego de la vida en 'nuproc' unidades de procesamiento.

Utilizar el archivo de cabecera *Board.h* es *opcional*.

Puede utilizar la función `get_nprocs()` para obtener la cantidad de unidades de
procesamiento disponibles.

### Lectura del Juego

La lectura del juego estará dada en un archivo respectando el siguiente formato:
en una linea 3 números enteros positivos indicando la cantidad de ciclos (C), la
cantidad de filas (M) y la cantidad de columnas (N) que tendrá el tablero, luego
el tablero descripto en formato
[RLE](https://es.wikipedia.org/wiki/Run-length_encoding), tomando los valores
'X' o 'O', representando células muertas y vivas respectivamente.

Por ejemplo, el tablero que se presentó a modo de [ejemplo](./Ejemplo.game)
esperando 10 iteraciones:

```
10 3 3
3X
3O
3X
```

La escritura de un tablero en un archivo sigue una idea similar. Dado un tablero
de N filas y M columnas, se espera encontrar en el archivo indicado N lineas con
los caracteres codificando el tablero correctamente.

### Ejecución del Simulador

La compilación de la solución deberá dejar un ejecutable en el directorio de
nombre 'simulador'. Y se espera que el ejecutable tome por entrada estándar la
dirección de una semilla:

```Bash
$>./simulador FilePath/Nombre.game
```

Y escribir el `FilePath/Nombre.final`, o generarlo en caso de que no exista, con
el tablero final luego de haber ejecutado la simulación del juego de la vida.

### Entrega del Trabajo Práctico

Se espera que el trabajo practico se presente la implementación en `C` de del
archivo de cabecera *Game.h* descripto en el enunciado, un informe del trabajo
práctico indicando las decisiones de implementación que tomaron y les parezcan
relevantes y la implementación de un archivo de compilación *Makefile*.

Los archivos deberán comprimirse en un archivo y enviarlos por mail a los
docentes de la cátedra antes del **Miércoles 21 de Abril a las 23.59**.
