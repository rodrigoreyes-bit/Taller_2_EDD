#include "../../include/classes/Almacenamiento.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
Almacenamiento::Almacenamiento() {
    this->str = nullptr;
}

//CREAR LISTA DE ARTISTAS

void Almacenamiento::crearCanción(int id, string nombre, string artista, string album, int ano, int duracion, string ubicacion) {
    Cancion* nuevaCancion = new Cancion(id, nombre, artista, album, ano, duracion, ubicacion);
    Nodo* nuevoNodo = new Nodo(nuevaCancion);

    if (str == nullptr) {
        str = nuevoNodo;
    } else {
        Nodo* cursor = str;
        while (cursor->siguiente != nullptr) {
            cursor = cursor->siguiente;
        }
        cursor->siguiente = nuevoNodo;
        nuevoNodo->anterior = cursor;
    }
}

void Almacenamiento::mostrarListaCanciones() {
    Nodo* cursor = str;
    if (cursor == nullptr) {
        cout << "No hay canciones disponibles." << endl;
        return;
    }
    int contador = 1;
    while (cursor != nullptr) {
        cout << contador << ". " << cursor->dato->getNombre() << " - " << cursor->dato->getArtista() << endl;
        cursor = cursor->siguiente;
        contador++;
    }
    cout << endl;
}
Cancion* Almacenamiento::getCancionIndice(int indice) {
    Nodo* aux = str;
    int cont = 1;

    while (aux != nullptr && cont < indice) {
        aux = aux->siguiente;
        cont++;
    }

    if (aux != nullptr) {
        return aux->dato;
    } else {
        return nullptr;
    }
}

void Almacenamiento::eliminarCancion(int id) {
    Nodo* aux = str;
    while (aux != nullptr) {
        if (aux->dato->getId() == id) {
            if (aux->anterior) aux->anterior->siguiente = aux->siguiente;
            else str = aux->siguiente;
            if (aux->siguiente) aux->siguiente->anterior = aux->anterior;

            delete aux->dato;
            delete aux;
            return;
        }
        aux = aux->siguiente;
    }
}
bool Almacenamiento::existeID(int id) {
    Nodo* aux = str;
    while (aux != nullptr) {
        if (aux->dato->getId() == id) {
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}
void Almacenamiento::guardarEnArchivo() {
    ofstream archivo("music_source.txt", ios::trunc);
    if (!archivo.is_open()) return;

    Nodo* aux = str;
    while (aux != nullptr) {
        Cancion* c = aux->dato;
        archivo << c->getId() << ","
                << c->getNombre() << ","
                << c->getArtista() << ","
                << c->getAlbum() << ","
                << c->getAnio() << ","
                << c->getDuracion() << ","
                << c->getUbicacion() << endl;
        aux = aux->siguiente;
    }
    archivo.close();
}
