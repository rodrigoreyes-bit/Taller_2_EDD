#ifndef TALLER1_ESTRUCTURA_ALMACENAMIENTO_HPP
#define TALLER1_ESTRUCTURA_ALMACENAMIENTO_HPP
#include <iostream>
#include <string>
#include "../data_structures/Nodo.h"

using namespace std;


class Almacenamiento {
public:
    Nodo* str = nullptr;
    Nodo* getPrimerNodo() {
        return str;
    }
    Almacenamiento();
    void crearCanción(int id, string nombre, string artista, string album, int ano, int duracion, string ubicacion);
    Cancion* getCancionIndice(int indice);
    void eliminarCancion(int id);
    void mostrarListaCanciones();
    bool existeID(int id);
    void guardarEnArchivo();
    void crearArtista(string artista); //crear artista y además crear una lista enlazada de artistas
};


#endif //TALLER1_ESTRUCTURA_ALMACENAMIENTO_HPP