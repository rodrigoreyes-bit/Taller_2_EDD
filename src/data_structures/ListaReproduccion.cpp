#include "../../include/data_structures/ListaReproduccion.hpp"
#include <iostream>
#include "../../include/classes/Configuracion.hpp"
using namespace std;

ListaReproduccion::ListaReproduccion() {
    this->inicio = nullptr;
    this->actual = nullptr;
}

Cancion *ListaReproduccion::getCancionActual() {
    if (actual == nullptr) {
        return nullptr;
    }
    return actual->dato;
}

void ListaReproduccion::cambiarEstadoReproduccion(Configuracion *c) {
    if (actual == nullptr) {
        return;
    }
    c->setPausa(!c->getPausa());
}

void ListaReproduccion::pistaSiguiente(Configuracion *c, Almacenamiento *alm) {
    if (actual == nullptr) return;
    if (c->getRepeticion() == 1) { c->setPausa(false); return; }

    if (actual->siguiente != nullptr) {
        actual = actual->siguiente;
        c->setPausa(false);
        c->setIdCancionActual(actual->dato->getId());
        alm->registrarReproduccion(actual->dato);
    } else {
        if (c->getRepeticion() == 2) {
            if (c->getRandom()) {
                generarListaAleatoria(alm, c);
            } else {
                actual = inicio;
                if (actual != nullptr) {
                    c->setPausa(false);
                    c->setIdCancionActual(actual->dato->getId());
                    alm->registrarReproduccion(actual->dato);
                }
            }
        } else {
            generarListaAleatoria(alm, c);
        }
    }
}

void ListaReproduccion::generarListaAleatoria(Almacenamiento *alm, Configuracion *c) {
    Nodo *aux = inicio;
    while (aux != nullptr) {
        Nodo *temp = aux;
        aux = aux->siguiente;
        delete temp;
    }

    inicio = nullptr;
    actual = nullptr;

    int cantCanciones = 0;

    Nodo *canciones = alm->getPrimerNodo();
    while (canciones != nullptr) {
        cantCanciones++;
        canciones = canciones->siguiente;
    }

    if (cantCanciones == 0) {
        return;
    }

    int *listaMezcla = new int[cantCanciones];
    canciones = alm->getPrimerNodo();
    for (int i = 0; i < cantCanciones; i++) {
        listaMezcla[i] = canciones->dato->getId();
        canciones = canciones->siguiente;
    }

    for (int i = cantCanciones - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tempId = listaMezcla[i];
        listaMezcla[i] = listaMezcla[j];
        listaMezcla[j] = tempId;
    }

    for (int i = 0; i < cantCanciones; i++) {
        Nodo *buscador = alm->getPrimerNodo();
        while (buscador != nullptr) {
            if (buscador->dato->getId() == listaMezcla[i]) {
                agregarAlFinal(buscador->dato);
                break;
            }
            buscador = buscador->siguiente;
        }
    }

    delete[] listaMezcla;

    if (inicio != nullptr) {
        actual = inicio;
        c->setIdCancionActual(actual->dato->getId());
        c->setPausa(false);
        alm->registrarReproduccion(actual->dato);

    }
}

void ListaReproduccion::pistaAnterior(Configuracion *c, Almacenamiento *alm) {
    if (actual == nullptr) return;
    if (c->getRepeticion() == 1) { c->setPausa(false); return; }

    if (actual->anterior != nullptr) {
        actual = actual->anterior;
        c->setIdCancionActual(actual->dato->getId());
        c->setPausa(false);
        alm->registrarReproduccion(actual->dato);
    } else {
        if (c->getRepeticion() == 2) {
            Nodo *aux = actual;
            while (aux->siguiente != nullptr) aux = aux->siguiente;
            actual = aux;
            c->setIdCancionActual(actual->dato->getId());
            c->setPausa(false);
            alm->registrarReproduccion(actual->dato);
        }
    }
}

void ListaReproduccion::agregarAlFinal(Cancion *cancion) {
    Nodo *nuevo = new Nodo(cancion);
    if (inicio == nullptr) {
        inicio = nuevo;
        actual = inicio;
        nuevo->anterior = nullptr;
    } else {
        Nodo *aux = inicio;
        while (aux->siguiente != nullptr) {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
        nuevo->anterior = aux;
    }
}

void ListaReproduccion::mostrarListaReproduccion() {
    if (actual == nullptr) {
        cout << "Actual: Ninguna" << endl;
        cout << "Lista de reproduccion actual:" << endl;
        cout << "  Vacia" << endl;
        cout << "Opciones:" << endl;
        cout << "  V - Volver al menu principal" << endl;
        cout << "Ingrese Opcion: ";
        return;
    }

    cout << "Actual: " << actual->dato->getNombre() << " - " << actual->dato->getArtista() << endl;
    cout << "Lista de reproduccion actual:" << endl;

    Nodo *cursor = actual->siguiente;
    if (cursor == nullptr) {
        cout << "  Vacia" << endl;
    } else {
        int i = 1;
        while (cursor != nullptr) {
            cout << "  " << i << ". " << cursor->dato->getNombre() << " - " << cursor->dato->getArtista() << endl;
            cursor = cursor->siguiente;
            i++;
        }
    }
    cout << "Opciones:" << endl;
    if (actual->siguiente != nullptr) {
        cout << "  S<num> - Saltar a la cancion seleccionada" << endl;
    }
    cout << "  V - Volver al menu principal" << endl;
}

void ListaReproduccion::saltarACancion(int pos, Configuracion *c, Almacenamiento *alm) {
    if (actual == nullptr || actual->siguiente == nullptr || pos <= 0) return;
    Nodo *cursor = actual->siguiente;
    int cont = 1;
    while (cursor != nullptr && cont < pos) { cursor = cursor->siguiente; cont++; }

    if (cursor != nullptr) {
        actual = cursor;
        actual->anterior = nullptr;
        c->setIdCancionActual(actual->dato->getId());
        c->setPausa(false);
        alm->registrarReproduccion(actual->dato);
    }
}

void ListaReproduccion::reproducirAltiro(Cancion *cancion, Configuracion *c, Almacenamiento *alm) {
    Nodo *aux = inicio;
    while (aux != nullptr) { Nodo *temp = aux; aux = aux->siguiente; delete temp; }
    inicio = new Nodo(cancion);
    actual = inicio;
    c->setPausa(false);
    c->setIdCancionActual(actual->dato->getId());
    alm->registrarReproduccion(actual->dato);
}

void ListaReproduccion::repetirCanciones(int modoRepe, Configuracion *c, Almacenamiento *alm, ListaReproduccion* lista) {
    if (actual == nullptr) return;
    if (modoRepe == 1) return;

    if (actual->siguiente == nullptr) {
        if (modoRepe == 2) {
            if (c->getRandom()) {
                mezclarListaRepeticion(alm, lista, c);
            } else {
                actual = inicio;
                if (actual != nullptr) alm->registrarReproduccion(actual->dato);
            }
            return;
        } else {
            actual = nullptr;
            return;
        }
    }
    actual = actual->siguiente;
    if (actual != nullptr) alm->registrarReproduccion(actual->dato);
}

void ListaReproduccion::mezclarListaRepeticion(Almacenamiento *alm, ListaReproduccion *lr, Configuracion *c) {
    int total = 0;
    Nodo *aux = inicio;
    while (aux != nullptr) {
        total++;
        aux = aux->siguiente;
    }
    if (total == 0) { return; }

    Nodo* temp = inicio;
    while (temp != nullptr) {
        Nodo* sig = temp-> siguiente;
        delete temp;
        temp = sig;
    }
    inicio = nullptr;

    int idRandom = (rand() % total) + 1;
    Cancion *elegida = alm->getCancionIndice(idRandom);

    if (elegida != nullptr) {
        agregarAlFinal(elegida);
        for (int i = 1; i <= total; i++) {
            if (i != idRandom) {
                Cancion *otra = alm->getCancionIndice(i);
                if (otra != nullptr) {
                    agregarAlFinal(otra);
                }
            }
        }
    }
    actual = inicio;
    if (actual != nullptr) {
        c->setIdCancionActual(actual->dato->getId());
        alm->registrarReproduccion(actual->dato);
    }
}

void ListaReproduccion::mezclarCola() {
    if (actual == nullptr || actual->siguiente == nullptr) {
        return;
    }

    int count = 0;
    Nodo *cursor = actual->siguiente;
    while (cursor != nullptr) {
        count++;
        cursor = cursor->siguiente;
    }

    Cancion **canciones = new Cancion *[count];
    cursor = actual->siguiente;
    for (int i = 0; i < count; i++) {
        canciones[i] = cursor->dato;
        cursor = cursor->siguiente;
    }

    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Cancion *temp = canciones[i];
        canciones[i] = canciones[j];
        canciones[j] = temp;
    }

    cursor = actual->siguiente;
    for (int i = 0; i < count; i++) {
        cursor->dato = canciones[i];
        cursor = cursor->siguiente;
    }

    delete[] canciones;
}
