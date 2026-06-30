//
// Created by pc on 30-06-2026.
//

#include "../../include/data_structures/ArbolAVL.hpp"

int ArbolAVL::obtenerAltura(NodoAVL *nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return nodo->altura;
}

int ArbolAVL::obtenerBalance(NodoAVL *nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return obtenerAltura(nodo->izq) - obtenerAltura(nodo->der);
}