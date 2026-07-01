#include "../../include/data_structures/MaxHeapCancion.h"

MaxHeapCancion::MaxHeapCancion(int cap) {
    this->capacidad = cap;
    this->tamano = 0;
    this->heap = new ElementoCancion[cap];
}

MaxHeapCancion::~MaxHeapCancion() {
    delete[] heap;
}

//compara dos elementos bajo el criterio de lo q dice el enunciado
bool MaxHeapCancion::esMayor(ElementoCancion a, ElementoCancion b) {
    if (a.reproducciones != b.reproducciones) {
        return a.reproducciones > b.reproducciones;
    }
    //desempate 1-> orden alfabético de la canción (A-Z)
    if (a.cancion->getNombre() != b.cancion->getNombre()) {
        return a.cancion->getNombre() < b.cancion->getNombre();
    }
    //desempate 2-> orden alfabético del artista (A-Z)
    return a.cancion->getArtista() < b.cancion->getArtista();
}

void MaxHeapCancion::ordenarHaciaArriba(int idx) {
    while (idx > 0) {
        int padre = (idx - 1) / 2;
        if (esMayor(heap[idx], heap[padre])) {
            ElementoCancion temp = heap[idx];
            heap[idx] = heap[padre];
            heap[padre] = temp;
            idx = padre;
        } else {
            break;
        }
    }
}

void MaxHeapCancion::ordenarHaciaAbajo(int idx) {
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
        ElementoCancion temp = heap[idx];
        heap[idx] = heap[mayor];
        heap[mayor] = temp;
        ordenarHaciaAbajo(mayor);
    }
}

void MaxHeapCancion::insertar(Cancion* c, int reps) {
    if (tamano >= capacidad) return;
    
    heap[tamano].cancion = c;
    heap[tamano].reproducciones = reps;
    tamano++;
    ordenarHaciaArriba(tamano - 1);
}

Cancion* MaxHeapCancion::extraerMaximo(int& repsOut) {
    if (tamano <= 0) return nullptr;
    
    Cancion* maxCancion = heap[0].cancion;
    repsOut = heap[0].reproducciones;
    
    heap[0] = heap[tamano - 1];
    tamano--;
    ordenarHaciaAbajo(0);
    
    return maxCancion;
}