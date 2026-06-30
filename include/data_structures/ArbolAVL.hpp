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

    NodoAVL(Cancion* cancion) {
        this->cancion = cancion;
        this->izq = nullptr;
        this->der = nullptr;

    }


};





class ArbolAVL {
private:
    NodoAVL* raiz;




};



#endif //TALLER1_ESTRUCTURA_ARBOLAVL_HPP
