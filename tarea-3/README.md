### Integrantes
Miguel Soto
201973623-K
Paralelo:200

Nicolas Barahona
202173652-2
Paralelo:200

____
## Conceptos
Fork: Incluye codigo utilizando Fork/Join.
Multithreaded: Incluye codigo utilizando Multithreading.
Sequential: Incluye codigo utilizando la busqueda secuencial.

____
## Detalles

Cada carpeta tiene su propia implementacion del mismo algoritmo descrito por el PDF, por ende, cada
uno tiene su propio Makefile para evitar choques entre las distintas implementaciones de las mismas
clases. Para correr basta con correr el makefile desde la carpeta de la implementacion correspondiente
y luego ejecutar la clase _Main_ con el comando _java_.

### Ejemplo:

```console
user@desktop:~/utfsm-so/tarea-3/multithreaded$ make
javac Main.java Matriz.java Multithread.java ReadText.java
```

```console
user@desktop:~/utfsm-so/tarea-3/multithreaded$ java Main
fila 12, columna 7
Tiempo de ejecucion: 14 ms
```