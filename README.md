# Snoopify ❨･¨⬮                                                                      

**Desarrollado por:**
* Ninibeth Pérez Cortés - papaFritaUwU
* Rodrigo Reyes Alfaro - rodrigoreyes-bit
* Josefa Vargas Cortés - josefa-v

## Descripción del Proyecto
Snoopify es un reproductor de música basado en consola desarrollado en C++ para el curso de Estructuras de Datos. El sistema permite gestionar un catálogo de música desde un archivo fuente y controlar una lista de reproducción dinámica. Utiliza estructuras de datos personalizadas, como listas doblemente enlazadas, para ofrecer una navegación fluida entre canciones, permitiendo reproducir, pausar y gestionar colas de reproducción de forma eficiente.

## Taller 4 consideraciones
Como este taller es la continuación del anterior, al hacer una copia del repo anterior se copiaron los commits también, por lo que la realización de este taller es desde el commit 97 en adelante.

## Diagrama de Clases
* **Cancion:** Almacena los metadatos (ID, nombre, artista, duración, etc.).
* **Nodo:** Clase base para la estructura de lista enlazada.
* **Almacenamiento:** Gestiona el catálogo completo de canciones disponibles en el sistema.
* **ListaReproduccion:** Controla la cola actual, el puntero a la canción en reproducción y los estados.
* **Configuracion:** Gestiona el archivo status.cfg en el proyecto.
* **ACTUALIZAAAAAAAAAAAAAAAAAR**
  
## Compilación y ejecución
* Para compilar este proyecto, se requiere un compilador de C++ (GCC/G++) instalado en su sistema.
* Desde la raíz del proyecto (donde se encuentra el archivo `main.cpp`) ejecutar el programa

* **Nota IMPORTANTE:** Si se compila en CLion o VSCode, el programa requiere que la carpeta data/ esté presente en el mismo **Working Directory** para cargar correctamente `music_source.txt` y `status.cfg`.
Para cambiar el **Working Directory** en CLion se tiene que:
1.- Ir a *Run*, click derecho y clickear *Edit Configurations..*.
2.- Seleccionar *Working Directory*.
3.- Hacer click en el icono de la carpeta y seleccionar la *carpeta* raíz del proyecto *"Taller1_Estructura"*.
4.- Apply y OK!!.

## Funcionamiento del programa
Al iniciar, el programa carga los datos desde la carpeta data/. El usuario dispone de las siguientes opciones principales en el menú:  

* W (Reproducir/Pausar): Alterna el estado actual de la pista.  
* Q / E (Navegación): Permite retroceder a la pista anterior o avanzar a la siguiente. Si la lista se agota, la opción E genera una nueva cola aleatoria basada en el almacenamiento total.
* A (Lista Actual): Abre un submenú para visualizar la cola de reproducción y saltar a pistas específicas.
* L (Listado General): Permite interactuar con la base de datos completa de canciones: reproducir una inmediatamente, agregarla a la cola, eliminarla del registro o registrar una nueva pista.
* X (Salir): Finaliza la ejecución y guarda automáticamente el estado actual en status.cfg[.

