//
// Created by pc on 30-06-2026.
//

#ifndef TALLER1_ESTRUCTURA_ARBOLAVL_HPP
#define TALLER1_ESTRUCTURA_ARBOLAVL_HPP
#include "classes/Cancion.hpp"

struct NodoAVL {
    Cancion* cancion;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

    NodoAVL(Cancion* c) {
        cancion = c;
        izquierdo = nullptr;
        derecho = nullptr;
        altura = 1;
    }
};

class ArbolAVL {
private:
    NodoAVL* raiz;
    int obtenerAltura(NodoAVL* nodo);
    int obtenerBalance(NodoAVL* nodo);
    int maximo(int a, int b);

    NodoAVL* rotarDerecha(NodoAVL* y);
    NodoAVL* rotarIzquierda(NodoAVL* x);

    NodoAVL* insertarRecursivo(NodoAVL* nodo, Cancion* cancion);
    void mostrarEnOrdenRecursivo(NodoAVL* nodo, int& contador);
    Cancion* obtenerPorIndiceRecursivo(NodoAVL* nodo, int idx, int& contadorActual);

    void destruirArbol(NodoAVL* nodo);


public:
    ArbolAVL();
    ~ArbolAVL();

    void insertar(Cancion* cancion);
    void mostrarEnOrden();
    Cancion* obtenerPorIndice(int idx);
};

#endif