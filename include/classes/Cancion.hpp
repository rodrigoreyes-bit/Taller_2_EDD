#ifndef TALLER1_ESTRUCTURA_CANCION_HPP
#define TALLER1_ESTRUCTURA_CANCION_HPP
#include <string>

using namespace std;

class Cancion {
private:
    int id;
    string nombre;
    string artista;
    string album;
    int anio;
    int duracion;
    string ubicacion;
    Cancion* siguienteCancionArtista;
    int contadorReproducciones; //contador de cuantas veces se reprodujo esta cancion (para el top 10 canciones más escuchadas)

public:
    Cancion(int id, string nombre, string artista, string album, int anio, int duracion, string ubicacion);

    int getId() const;
    string getNombre() const;
    string getArtista() const;
    string getAlbum() const;
    int getAnio() const;
    int getDuracion() const;
    string getUbicacion() const;
    void setId(int id);
    void setNombre(string nombre);
    void setArtista(string artista);
    void setAlbum(string album);
    void setAnio(int anio);
    void setDuracion(int duracion);
    void setUbicacion(string ubicacion);
    int getReproducciones() const;
    Cancion* getSiguienteCancionArtista() const;
    void setReproducciones(int cantidad);
    void incrementarReproduccion();
    void setSiguienteCancionArtista(Cancion* siguiente);
};

#endif //TALLER1_ESTRUCTURA_CANCION_HPP