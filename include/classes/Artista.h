
#ifndef TALLER1_ESTRUCTURA_ARTISTA_H
#define TALLER1_ESTRUCTURA_ARTISTA_H

#include <string>
#include "../../include/classes/Cancion.hpp"
#include "data_structures/ArbolAVL.hpp"

using namespace std;

class Artista {
private:
    string nombre;
    int contadorCanciones;
    Cancion* startCancionesArtista;
    Artista* siguienteArtista;

    ArbolAVL* cancionesAVL;

public:
    Artista(string nombre);

    string getNombre() const;
    int getContador() const;
    Cancion* getStartCanciones() const;
    Artista* getSiguienteArtista() const;

    void agregarCancion(Cancion* cancion);
    bool quitarCancion(int idCancion);
    void sumarReproduccion(int cantidad = 1);
    int contarCanciones() const;
    void setSiguienteArtista(Artista* siguiente);

    ArbolAVL* getCancionesAVL() const;
};
#endif //TALLER1_ESTRUCTURA_ARTISTA_H