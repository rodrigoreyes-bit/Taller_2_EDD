#include "../../include/classes/Artista.h"

Artista::Artista(string nombre) {
    this->nombre = nombre;
    this->contadorCanciones = 0;
    this->startCancionesArtista = nullptr;
    this->siguienteArtista = nullptr;
    this->cancionesAVL = new ArbolAVL();
}

string Artista::getNombre() const {
    return nombre;
}
int Artista::getContador() const {
    return contadorCanciones;
}
Cancion* Artista::getStartCanciones() const {
    return startCancionesArtista;
}
Artista* Artista::getSiguienteArtista() const {
    return siguienteArtista;
}
void Artista::setSiguienteArtista(Artista* siguiente) {
    siguienteArtista = siguiente;
}

void Artista::agregarCancion(Cancion* cancion) {
    if (startCancionesArtista == nullptr) {
        startCancionesArtista = cancion;
    } else {
        Cancion* cursor = startCancionesArtista;
        while (cursor->getSiguienteCancionArtista() != nullptr) cursor = cursor->getSiguienteCancionArtista();
        cursor->setSiguienteCancionArtista(cancion);
    }

    cancionesAVL->insertar(cancion);
}

bool Artista::quitarCancion(int idCancion) {
    Cancion* cursor = startCancionesArtista;
    Cancion* anterior = nullptr;
    while (cursor != nullptr) {
        if (cursor->getId() == idCancion) {
            if (anterior == nullptr) startCancionesArtista = cursor->getSiguienteCancionArtista();
            else anterior->setSiguienteCancionArtista(cursor->getSiguienteCancionArtista());
            cursor->setSiguienteCancionArtista(nullptr);
            return true;
        }
        anterior = cursor;
        cursor = cursor->getSiguienteCancionArtista();
    }
    return false;
}

void Artista::sumarReproduccion(int cantidad) {
    contadorCanciones += cantidad;
}

int Artista::contarCanciones() const {
    int cont = 0;
    Cancion* cursor = startCancionesArtista;
    while (cursor != nullptr) { cont++; cursor = cursor->getSiguienteCancionArtista(); }
    return cont;
}

ArbolAVL* Artista::getCancionesAVL() const {
    return cancionesAVL;
}