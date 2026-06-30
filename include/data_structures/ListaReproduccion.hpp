#ifndef TALLER1_ESTRUCTURA_LISTAREPRODUCCION_HPP
#define TALLER1_ESTRUCTURA_LISTAREPRODUCCION_HPP
#include "../classes/Almacenamiento.hpp"
#include "Nodo.h"
class Configuracion;

class ListaReproduccion {
private:
    Nodo* inicio;
    Nodo* actual;


public:
    ListaReproduccion();

    Cancion* getCancionActual();
    void cambiarEstadoReproduccion(Configuracion* c);
    void pistaAnterior(Configuracion* c, Almacenamiento* alm);
    void pistaSiguiente(Configuracion* c, Almacenamiento* alm);
    void generarListaAleatoria(Almacenamiento* alm, Configuracion* c);
    void mezclarCola();
    void agregarAlFinal(Cancion* cancion);
    void mostrarListaReproduccion();
    void saltarACancion(int pos, Configuracion* c, Almacenamiento* alm);
    void reproducirAltiro(Cancion* cancion, Configuracion* c, Almacenamiento* alm);
    void repetirCanciones(int modoRepe, Configuracion* c, Almacenamiento* alm, ListaReproduccion* lista);
    void mezclarListaRepeticion(Almacenamiento* alm, ListaReproduccion* lr, Configuracion* c);


};
#endif //TALLER1_ESTRUCTURA_LISTAREPRODUCCIÓN_HPP
