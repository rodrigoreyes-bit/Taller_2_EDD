//
// Created by pc on 01-07-2026.
//

#include "../../include/data_structures/MaxHeapArtistas.hpp"

#include "classes/Artista.h"

MaxHeapArtistas::MaxHeapArtistas(int cap) {
    this->capacidad = cap;
    this->tamano = 0;
    this->heap = new ElementoArtista[cap];
}

MaxHeapArtistas::~MaxHeapArtistas() {
    delete[] heap;
}

bool MaxHeapArtistas::esMayor(ElementoArtista a, ElementoArtista b) {
    if (a.reproducciones != b.reproducciones) {
        return a.reproducciones > b.reproducciones;
    }
    return a.artista->getNombre() < b.artista->getNombre();
}

void MaxHeapArtistas::ordenarHaciaArriba(int idx) {
    while (idx > 0) {
        int padre = (idx - 1) / 2;
        if (esMayor(heap[idx], heap[padre])) {
            ElementoArtista temp = heap[idx];
            heap[idx] = heap[padre];
            heap[padre] = temp;
            idx = padre;
        } else {
            break;
        }
    }
}

void MaxHeapArtistas::ordenarHaciaAbajo(int idx) {
    int mayor = idx;
    int izquierdo = 2 * idx + 1;
    int derecho = 2 * idx + 2;

    if (izquierdo < tamano && esMayor(heap[izquierdo], heap[mayor])) {
        mayor = izquierdo;
    }
    if (derecho < tamano && esMayor(heap[derecho], heap[mayor])) {
        mayor = derecho;
    }

    if (mayor != idx) {
        ElementoArtista temp = heap[idx];
        heap[idx] = heap[mayor];
        heap[mayor] = temp;
        ordenarHaciaAbajo(mayor);
    }
}

void MaxHeapArtistas::insertar(Artista* a, int reps) {
    if (tamano >= capacidad) return;

    heap[tamano].artista = a;
    heap[tamano].reproducciones = reps;
    tamano++;
    ordenarHaciaArriba(tamano - 1);
}

Artista* MaxHeapArtistas::extraerMaximo(int& repsOut) {
    if (tamano <= 0) return nullptr;

    Artista* maxArtista = heap[0].artista;
    repsOut = heap[0].reproducciones;

    heap[0] = heap[tamano - 1];
    tamano--;
    ordenarHaciaAbajo(0);

    return maxArtista;
}
