#ifndef MAX_HEAP_CANCION_HPP
#define MAX_HEAP_CANCION_HPP

#include "../classes/Cancion.hpp"
#include <string>

struct ElementoCancion {
    Cancion* cancion;
    int reproducciones;
};

class MaxHeapCancion {
private:
    ElementoCancion* heap;
    int capacidad;
    int tamano;

    // funciones auxiliares de ordenamiento (Hhapify)
    void ordenarHaciaArriba(int idx);
    void ordenarHaciaAbajo(int idx);
    
    //funcion para comparar dos elementos segun las reglas de desempate
    bool esMayor(ElementoCancion a, ElementoCancion b);

public:
    MaxHeapCancion(int cap);
    ~MaxHeapCancion();
    
    void insertar(Cancion* c, int reps);
    Cancion* extraerMaximo(int& repsOut);
    int getTamano() const { return tamano; }
};

#endif