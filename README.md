# Snoopify ❨･¨⬮                                                                      

**Desarrollado por:**
* Ninibeth Pérez Cortés - papaFritaUwU
* Rodrigo Reyes Alfaro - rodrigoreyes-bit
* Josefa Vargas Cortés - josefa-v

## Descripción del Proyecto
Snoopify es un reproductor de música basado en consola desarrollado en C++ para el curso de Estructuras de Datos. Este taller es una extensión del taller anterior, por lo que esta versión extiende la aplicación base mediante la implementación manual de estructuras avanzadas de árboles creadas dinámicamente en memoria al iniciar el sistema, en el que el reproductor permite una navegación eficiente de pistas, gestión de listas de reproducción, búsquedas complejas y un sistema de clasificaciones TOP 10 de reproducciones.

## Taller 4 consideraciones
Como este taller es la continuación del anterior, al hacer una copia del repo anterior se copiaron los commits también, por lo que la realización de este taller es desde el commit 97 en adelante.

## Diagrama de Clases y Estructuras
* **Cancion:** Almacena los datos de la pista (ID, nombre, artista, duración, etc.) y mantiene el contador de reproducciones en tiempo real.
* **Artista:** Gestiona de forma individual el catálogo de canciones de un mismo autor, almacenándolas de forma interna y alfabética.
* **Nodo / NodoAVL:** Clases base y de soporte para las estructuras enlazadas y ramificadas.
* **Almacenamiento:** Gestiona el catálogo de la biblioteca global conectando la lista principal con la lista de artistas.
* **ListaReproduccion:** Controla la cola actual mediante una lista doblemente enlazada, el puntero a la pista en reproducción y los estados del sistema.
* **Configuracion:** Modula la carga y guardado del archivo de estados `status.cfg`.
* **MaxHeapCancion / MaxHeapArtistas:** Estructuras de montículo (Heap) para calcular y extraer de manera eficiente los rankings TOP 10.
* **ArbolAVL:** Árbol auto-balanceado implementado en cada artista para mantener y desplegar sus canciones en un estricto orden alfabético (A-Z).
  
## Compilación
* Para compilar este proyecto, se requiere un compilador de C++ (GCC/G++) instalado en su sistema.
* Desde la raíz del proyecto (donde se encuentra el archivo `main.cpp`) ejecutar el programa

* **Nota IMPORTANTE:** Si se compila en CLion o VSCode, el programa requiere que la carpeta data/ esté presente en el mismo **Working Directory** para cargar correctamente `music_source.txt` y `status.cfg`.
Para cambiar el **Working Directory** en CLion se tiene que:
1.- Ir a *Run*, click derecho y clickear *Edit Configurations..*.
2.- Seleccionar *Working Directory*.
3.- Hacer click en el icono de la carpeta y seleccionar la *carpeta* raíz del proyecto *"Taller1_Estructura"*.
4.- Apply y OK!!.

## Compilación y Ejecución desde la Consola
Para compilar y ejecutar este proyecto de forma manual sin depender de un IDE, asegúrese de abrir su terminal o consola de comandos en la **carpeta raíz del proyecto** (donde se ubica el archivo `main.cpp`).

#### Comando de Compilación
Ejecute el siguiente comando utilizando el compilador `g++` para compilar todos los módulos del programa:

**En Windows:**
```bash
g++ -std=c++14 src/main.cpp src/data_structures/ListaReproduccion.cpp src/data_structures/Nodo.cpp src/data_structures/MaxHeapCancion.cpp src/data_structures/MaxHeapArtistas.cpp src/data_structures/ArbolAVL.cpp src/classes/Almacenamiento.cpp src/classes/Cancion.cpp src/classes/Configuracion.cpp src/classes/Artista.cpp -o Snoopify.exe
```
#### Comando de ejecución:
```
Snoopify.exe
```

## Funcionamiento del programa
Al iniciar, el programa carga los datos desde la carpeta data/. El usuario dispone de las siguientes opciones principales en el menú:  

* **W (Reproducir/Pausar):** Alterna el estado de reproducción de la canción actual.
* **Q / E (Navegación):** Permite retroceder a la pista anterior o avanzar a la siguiente. Si la cola se agota, 'E' genera una remezcla aleatoria basada en la biblioteca total.
* **S (Modo Aleatorio):** Mezcla las canciones restantes en la cola actual una sola vez usando el algoritmo Fisher-Yates sobre los nodos.
* **R (Repetición):** Cicla de forma interactiva entre los modos desactivado (0), repetir una pista (R1) y repetir la lista completa (RA).
* **A (Lista Actual):** Despliega el submenú de canciones pendientes y permite usar `S<num>` para saltar descartando pistas intermedias.
* **L (Listado General):** Permite interactuar directamente con la biblioteca (Reproducción inmediata `R<num>`, adición final `A<num>`, eliminar `D<num>` o registrar una nueva pista `N`).
* **F (Buscar Canciones):** Permite la búsqueda alfanumérica parcial o completa sobre los campos de nombres de canción y artistas.
* **T (TOP 10 Artistas y Canciones):** Despliega el menú de clasificaciones. Permite visualizar el Top 10 de canciones más escuchadas (con desempate alfabético) o el Top 10 de artistas más populares. Desde el Top de artistas se puede acceder a sus canciones ordenadas alfabéticamente de la A a la Z mediante la estructura AVL interna de cada autor.
* **X (Salir):** Finaliza la ejecución volcando de manera segura las configuraciones en `status.cfg` y las estadísticas en `song_ranking.txt`.
