Hola!

1. El programa se compila con:

g++ main.cpp functions.cpp mergeSort.cpp quadMergeSort.cpp triMergeSort.cpp -o ejecutable

2. Para llamar al programa se debe ejecutar:

./ejecutable input.txt output.txt

3. Notas Extra:
  - Cada función de functions cuenta con un verificador que garantiza el orden de
    los resultados

  - El programa cuenta con una pequeña interfaz, pero no está pensada para manejar
    distintos inputs del usuario, Por lo que se ruega seguir las instrucciones.

  - Por defecto se creará un arreglo con tamaño de 10.000.000 de elementos.
    Este puede ser cambiado facilmente en el programa main.cpp. Sin embargo,
    por favor mantenga la capacidad en un mínimo de 100.000 elementos, puesto
    que hay funcionalidades del archivo functions.cpp que pueden verse afectadas
    de otra manera.
