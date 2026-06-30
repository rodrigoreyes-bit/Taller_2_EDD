
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
    Artista* siguienteArtista;

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
};
#endif //TALLER1_ESTRUCTURA_ARTISTA_H