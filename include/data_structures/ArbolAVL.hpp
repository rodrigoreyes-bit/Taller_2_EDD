//
// Created by pc on 30-06-2026.
//

#ifndef TALLER1_ESTRUCTURA_ARBOLAVL_HPP
#define TALLER1_ESTRUCTURA_ARBOLAVL_HPP
#include "classes/Cancion.hpp"

class NodoAVL {
public:
    Cancion* cancion;
    NodoAVL* izq;
    NodoAVL* der;
    int altura;

    NodoAVL(Cancion* cancion) {
        this->cancion = cancion;
        this->izq = nullptr;
        this->der = nullptr;
        this->altura = 1;
    }

};

class ArbolAVL {
private:
    NodoAVL* raiz;
    int obtenerAltura(NodoAVL* nodo);
    int obtenerBalance(NodoAVL* nodo);




};



#endif //TALLER1_ESTRUCTURA_ARBOLAVL_HPP