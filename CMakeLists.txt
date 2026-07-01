cmake_minimum_required(VERSION 4.2)
project(Taller1_Estructura)

set(CMAKE_CXX_STANDARD 20)

add_executable(Taller1_Estructura
        src/main.cpp

        src/data_structures/ListaReproduccion.cpp
        src/data_structures/Nodo.cpp

        src/classes/Almacenamiento.cpp
        src/classes/Cancion.cpp
        src/classes/Configuracion.cpp
        include/classes/Artista.h
        src/data_structures/ArbolAVL.cpp
        include/data_structures/ArbolAVL.hpp
        src/classes/Artista.cpp
        include/data_structures/MaxHeapCancion.h
        src/data_structures/MaxHeapCancion.cpp
        src/data_structures/MaxHeapArtistas.cpp
        include/data_structures/MaxHeapArtistas.hpp
)
target_include_directories(Taller1_Estructura PRIVATE include)
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")