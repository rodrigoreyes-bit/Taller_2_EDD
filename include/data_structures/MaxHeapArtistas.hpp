//
// Created by pc on 01-07-2026.
//

#ifndef TALLER1_ESTRUCTURA_MAXHEAPARTISTAS_HPP
#define TALLER1_ESTRUCTURA_MAXHEAPARTISTAS_HPP
#include "classes/Artista.h"

struct ElementoArtista {
    Artista* artista;
    int reproducciones;
};

class MaxHeapArtistas {
private:
    ElementoArtista* heap;
    int capacidad;
    int tamano;

    void ordenarHaciaArriba(int idx);
    void ordenarHaciaAbajo(int idx);

    bool esMayor(ElementoArtista a, ElementoArtista b);

public:
    MaxHeapArtistas(int cap);
    ~MaxHeapArtistas();

    void insertar(Artista* a, int reps);
    Artista* extraerMaximo(int& repsOut);
    int getTamano() const { return tamano; }
};


#endif //TALLER1_ESTRUCTURA_MAXHEAPARTISTAS_HPP
