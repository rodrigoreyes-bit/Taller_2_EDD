#include "../../include/data_structures/ArbolAVL.hpp"

#include <iostream>

ArbolAVL::ArbolAVL() {
    this->raiz = nullptr;
}

ArbolAVL::~ArbolAVL() {
    destruirArbol(this->raiz);
}

/*void ArbolAVL::destruirArbol(NodoAVL *nodo) {
    if (nodo != nullptr) {
        destruirArbol(nodo->izq);
        destruirArbol(nodo->der);
    }
    delete nodo;
}
*/

int ArbolAVL::obtenerAltura(NodoAVL *nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return nodo->altura;
}

int ArbolAVL::obtenerBalance(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecho);
}

int ArbolAVL::maximo(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

NodoAVL* ArbolAVL::rotarDerecha(NodoAVL* y) {
    NodoAVL* x = y->izquierdo;
    NodoAVL* T2 = x->derecho;

    x->derecho = y;
    y->izquierdo = T2;

    y->altura = maximo(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;
    x->altura = maximo(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;

    return x;
}

NodoAVL* ArbolAVL::rotarIzquierda(NodoAVL* x) {
    NodoAVL* y = x->derecho;
    NodoAVL* T2 = y->izquierdo;

    y->izquierdo = x;
    x->derecho = T2;

    x->altura = maximo(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;
    y->altura = maximo(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;

    return y;
}

NodoAVL* ArbolAVL::insertarRecursivo(NodoAVL* nodo, Cancion* c) {
    if (nodo == nullptr) {
        return new NodoAVL(c);
    }

    if (c->getNombre() < nodo->cancion->getNombre()) {
        nodo->izquierdo = insertarRecursivo(nodo->izquierdo, c);
    } else {
        nodo->derecho = insertarRecursivo(nodo->derecho, c);
    }

    nodo->altura = 1 + maximo(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));
    int balance = obtenerBalance(nodo);

    if (balance > 1 && c->getNombre() < nodo->izquierdo->cancion->getNombre()) {
        return rotarDerecha(nodo);
    }
    if (balance < -1 && c->getNombre() > nodo->derecho->cancion->getNombre()) {
        return rotarIzquierda(nodo);
    }
    if (balance > 1 && c->getNombre() > nodo->izquierdo->cancion->getNombre()) {
        nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
        return rotarDerecha(nodo);
    }
    if (balance < -1 && c->getNombre() < nodo->derecho->cancion->getNombre()) {
        nodo->derecho = rotarDerecha(nodo->derecho);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

void ArbolAVL::insertar(Cancion* c) {
    raiz = insertarRecursivo(raiz, c);
}

void ArbolAVL::mostrarEnOrdenRecursivo(NodoAVL* nodo, int& contador) {
    if (nodo != nullptr) {
        mostrarEnOrdenRecursivo(nodo->izquierdo, contador);
        std::cout << "  " << contador << ". " << nodo->cancion->getNombre() << "\n";
        contador++;
        mostrarEnOrdenRecursivo(nodo->derecho, contador);
    }
}

void ArbolAVL::mostrarEnOrden() {
    int contador = 1;
    if (raiz == nullptr) {
        std::cout << "  (No hay canciones para este artista)\n";
        return;
    }
    mostrarEnOrdenRecursivo(raiz, contador);
}

Cancion* ArbolAVL::obtenerPorIndiceRecursivo(NodoAVL* nodo, int idx, int& contadorActual) {
    if (nodo == nullptr) return nullptr;

    Cancion* izq = obtenerPorIndiceRecursivo(nodo->izquierdo, idx, contadorActual);
    if (izq != nullptr) return izq;

    if (contadorActual == idx) {
        return nodo->cancion;
    }
    contadorActual++;

    return obtenerPorIndiceRecursivo(nodo->derecho, idx, contadorActual);
}

Cancion* ArbolAVL::obtenerPorIndice(int idx) {
    int contadorActual = 1;
    return obtenerPorIndiceRecursivo(raiz, idx, contadorActual);
}
