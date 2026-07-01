//
// Created by pc on 30-06-2026.
//

#include "../../include/data_structures/ArbolAVL.hpp"

#include <iostream>

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
    return obtenerAltura(nodo->izq) - obtenerAltura(nodo->der);
}

int ArbolAVL::maximo(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

NodoAVL* ArbolAVL::rotacionSimpleDerecha(NodoAVL *y) {
    NodoAVL* x = y->izq;
    NodoAVL* subArbol = x->der;

    x->der = y;
    y->izq = subArbol;

    y->altura = maximo(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;
    x->altura = maximo(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;

    return x;
}

NodoAVL* ArbolAVL::rotacionSimpleIzquierda(NodoAVL *x) {
    NodoAVL* y = x->der;
    NodoAVL* subArbol = y->izq;

    y->izq = x;
    x->der = subArbol;

    x->altura = maximo(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;
    y->altura = maximo(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;

    return y;
}

NodoAVL *ArbolAVL::insertarRec(NodoAVL *actual, Cancion *cancion) {
    if (actual = nullptr) {
        return new NodoAVL(cancion);
    }

    if (cancion->getNombre() < actual->cancion->getNombre()) {
        actual->izq = insertarRec(actual->izq, cancion);
    }else {
        actual->der = insertarRec(actual->der, cancion);
    }

    actual->altura = 1 + maximo(obtenerAltura(actual->izq), obtenerAltura(actual->der));

    int balance = obtenerBalance(actual);

    if (balance > 1 && cancion->getNombre() < actual->izq->cancion->getNombre()) {
        return rotacionSimpleDerecha(actual);
    }

    if (balance < -1 && cancion->getNombre() > actual->der->cancion->getNombre()) {
        return rotacionSimpleIzquierda(actual);
    }

    if (balance > 1 && cancion->getNombre() > actual->izq->cancion->getNombre()) {
        actual->izq = rotacionSimpleIzquierda(actual->izq);
        return rotacionSimpleDerecha(actual);
    }

    if (balance < -1 && cancion->getNombre() < actual->der->cancion->getNombre()) {
        actual->der = rotacionSimpleDerecha(actual->der);
        return rotacionSimpleIzquierda(actual);
    }

    return actual;
}

void ArbolAVL::insertar(Cancion *cancion) {
    this->raiz = insertarRec(this->raiz, cancion);
}

void ArbolAVL::InOrden(NodoAVL *nodo, int &cont) {
    if (nodo != nullptr) {
        InOrden(nodo->izq, cont);
        std::cout << "  " << cont << ". " << nodo->cancion->getNombre() << endl;
        cont++;
        InOrden(nodo->der, cont);
    }
}

void ArbolAVL::mostrarInOrden() {
    int contador = 1;
    InOrden(raiz, contador);
}
//holi
