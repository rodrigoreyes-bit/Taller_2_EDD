#include "../../include/classes/Almacenamiento.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
Almacenamiento::Almacenamiento() {
    this->str = nullptr;
}

//CREAR LISTA DE ARTISTAS
void Almacenamiento::crearArtista(string artista) {
    if (buscarArtista(artista) != nullptr) return;
    Artista* nuevo = new Artista(artista);
    if (artistas == nullptr) {
        artistas = nuevo;
    } else {
        Artista* cursor = artistas;
        while (cursor->getSiguienteArtista() != nullptr) cursor = cursor->getSiguienteArtista();
        cursor->setSiguienteArtista(nuevo);
    }
}
Artista* Almacenamiento::buscarArtista(string nombre) {
    Artista* cursor = artistas;
    while (cursor != nullptr) {
        if (cursor->getNombre() == nombre) return cursor;
        cursor = cursor->getSiguienteArtista();
    }
    return nullptr;
}


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
    crearArtista(artista);
    buscarArtista(artista)->agregarCancion(nuevaCancion);
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
            string nombreArtista = aux->dato->getArtista(); // capturar antes de borrar la cancion

            Artista* art = buscarArtista(nombreArtista);
            if (art != nullptr) {
                art->quitarCancion(id);
                if (art->contarCanciones() == 0) {
                    Artista* cursor = artistas;
                    Artista* prev = nullptr;
                    while (cursor != nullptr) {
                        if (cursor == art) {
                            if (prev == nullptr) artistas = cursor->getSiguienteArtista();
                            else prev->setSiguienteArtista(cursor->getSiguienteArtista());
                            delete cursor;
                            break;
                        }
                        prev = cursor;
                        cursor = cursor->getSiguienteArtista();
                    }
                }
            }
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
void Almacenamiento::registrarReproduccion(Cancion* cancion) {
    if (cancion == nullptr) return;
    cancion->incrementarReproduccion();
    Artista* art = buscarArtista(cancion->getArtista());
    if (art != nullptr) art->sumarReproduccion();
    guardarReproducciones();
}

void Almacenamiento::cargarReproducciones() {
    ifstream archivo("data/song_ranking.txt");
    if (!archivo.is_open()) return;
    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string idStr, contadorStr;
        getline(ss, idStr, ',');
        getline(ss, contadorStr, ',');
        try {
            int id = stoi(idStr);
            int contador = stoi(contadorStr);
            Nodo* cursor = str;
            while (cursor != nullptr) {
                if (cursor->dato->getId() == id) {
                    cursor->dato->setReproducciones(contador);
                    Artista* art = buscarArtista(cursor->dato->getArtista());
                    if (art != nullptr) art->sumarReproduccion(contador);
                    break;
                }
                cursor = cursor->siguiente;
            }
        } catch (const std::exception &e) { continue; }
    }
    archivo.close();
}

void Almacenamiento::guardarReproducciones() {
    ofstream archivo("data/song_ranking.txt", ios::trunc);
    if (!archivo.is_open()) return;
    Nodo* aux = str;
    while (aux != nullptr) {
        archivo << aux->dato->getId() << "," << aux->dato->getReproducciones() << endl;
        aux = aux->siguiente;
    }
    archivo.close();
}
