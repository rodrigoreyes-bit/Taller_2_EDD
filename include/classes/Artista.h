
#ifndef TALLER1_ESTRUCTURA_ARTISTA_H
#define TALLER1_ESTRUCTURA_ARTISTA_H

#include <string>
#include "../../include/classes/Cancion.hpp"

using namespace std;

class Artista {
private:
    string nombre;
    int contadorCanciones; //contador de cuantas veces se reprodujo esta cancion (para el top 10 canciones más escuchadas)
    Cancion* startCancionesArtista;

public:
    Artista(string nombre);
    //hacer un string de canciones del artista separado por comas (despues se leerá con splits y se comparará con la l,ista enlazada de canciones)
    string getNombre;
    int getContador;

#endif //TALLER1_ESTRUCTURA_ARTISTA_H
