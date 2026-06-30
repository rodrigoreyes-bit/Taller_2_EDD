#ifndef TALLER1_ESTRUCTURA_ALMACENAMIENTO_HPP
#define TALLER1_ESTRUCTURA_ALMACENAMIENTO_HPP
#include <iostream>
#include <string>
#include "../data_structures/Nodo.h"
#include "../classes/Artista.h"

using namespace std;


class Almacenamiento {
public:
    Artista* artistas = nullptr;
    Artista* getPrimerArtista() { return artistas; }
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
    Artista* buscarArtista(string nombre);
    void registrarReproduccion(Cancion* cancion);
    void cargarReproducciones();
    void guardarReproducciones();
};




#endif //TALLER1_ESTRUCTURA_ALMACENAMIENTO_HPP