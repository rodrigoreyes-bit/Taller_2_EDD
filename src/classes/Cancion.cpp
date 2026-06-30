#include "../../include/classes/Cancion.hpp"

Cancion::Cancion(int id, string nombre, string artista, string album, int anio, int duracion, string ubicacion) {
    this->id = id;
    this->nombre = nombre;
    this->artista = artista;
    this->album = album;
    this->anio = anio;
    this->duracion = duracion;
    this->ubicacion = ubicacion;
    this->contadorReproducciones = 0;
    this->siguienteCancionArtista = nullptr;
}

int Cancion::getId() const {
    return id;
}
string Cancion::getNombre() const {
    return nombre;
}
string Cancion::getArtista() const {
    return artista;
}
string Cancion::getAlbum() const {
    return album;
}
int Cancion::getAnio() const {
    return anio;
}
int Cancion::getDuracion() const {
    return duracion;
}
string Cancion::getUbicacion() const {
    return ubicacion;
}
void Cancion::setId(int id) {
    this->id = id;
}
void Cancion::setNombre(string nombre) {
    this->nombre = nombre;
}
void Cancion::setArtista(string artista) {
    this->artista = artista;
}
void Cancion::setAlbum(string album) {
    this->album = album;
}
void Cancion::setAnio(int anio) {
    this->anio = anio;
}
void Cancion::setDuracion(int duracion) {
    this->duracion = duracion;
}
void Cancion::setUbicacion(string ubicacion) {
    this->ubicacion = ubicacion;
}
int Cancion::getReproducciones() const {
    return contadorReproducciones;
}
Cancion* Cancion::getSiguienteCancionArtista() const {
    return siguienteCancionArtista;
}
void Cancion::setReproducciones(int cantidad) {
    contadorReproducciones = cantidad;
}
void Cancion::incrementarReproduccion() {
    contadorReproducciones++;
}
void Cancion::setSiguienteCancionArtista(Cancion* siguiente) {
    siguienteCancionArtista = siguiente;
}