#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../include/classes/Almacenamiento.hpp"
#include "../include/data_structures/ListaReproduccion.hpp"
#include "../include/classes/Configuracion.hpp"
using namespace std;

void lecturaCanciones(Almacenamiento *a) {
    ifstream archivo("data/music_source.txt");
    string linea;

    if (!archivo.is_open()) {
        cout << "No se encontro music_source.txt" << endl;
        return;
    }

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string id, nombre, artista, album, anio, duracion, ubicacion;

        getline(ss, id, ',');
        getline(ss, nombre, ',');
        getline(ss, artista, ',');
        getline(ss, album, ',');
        getline(ss, anio, ',');
        getline(ss, duracion, ',');
        getline(ss, ubicacion);

        try {
            a->crearCanción(stoi(id), nombre, artista, album, stoi(anio), stoi(duracion), ubicacion);
        } catch (const std::exception &e) {
            cout << "Error leyendo linea del archivo" << endl;
        }
    }
    archivo.close();
}

void menuOpciones(Configuracion *cfg, string cancion, string artista, string album, int anio) {
    cout << (cfg->getPausa() ? "En Pausa" : "Reproduciendo") << " (" << (cfg->getRandom() ? "S" : " ") << "-" << (
        (cfg->getRepeticion() == 1) ? "R1" : (cfg->getRepeticion() == 2) ? "RA" : " ") << "): " << cancion << endl;
    cout << "Artista: " << artista << endl;
    cout << "Album: " << album << " [" << anio << "]" << endl;
    cout << "Opciones:" << endl;
    cout << "  W - Reproducir/Pausar" << endl;
    cout << "  Q - Pista Anterior" << endl;
    cout << "  E - Pista Siguiente" << endl;
    cout << "  S - Activar/Desactivar modo aleatorio" << endl;
    cout << "  R - Repeticion (Desactivado (0) /Repetir una (1) /Repetir todas (2))" << endl;
    cout << "  A - Ver lista de reproduccion actual" << endl;
    cout << "  L - Listado de canciones" << endl;
    cout << "  X - Salir" << endl;
    cout << "Ingrese Opcion: ";
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void ejecutarmenuL(Almacenamiento *alm, Configuracion *c, ListaReproduccion *lr, string &cancionAct, string &artistaAct,
                   string &albumAct, int &anioAct) {
    string input;
    bool volver = false;

    while (volver == false) {

        Nodo *cursor = alm->getPrimerNodo();
        int i = 1;

        if (cursor == nullptr) {
            cout << "El registro esta vacio" << endl;
        }

        while (cursor != nullptr) {
            cout << i << ". " << cursor->dato->getNombre() << " - " << cursor->dato->getArtista() << endl;
            cursor = cursor->siguiente;
            i++;
        }

        cout << "  Opciones:" << endl;
        cout << "  R<num> - Reproducir cancion seleccionada (ej: R1)" << endl;
        cout << "  A<num> - Agregar cancion seleccionada al final de la cola (ej: A3)" << endl;
        cout << "  N      - Agregar nueva cancion al registro" << endl;
        cout << "  D<num> - Eliminar cancion seleccionada (ej: D5)" << endl;
        cout << "  V      - Volver al menu principal" << endl;
        cout << "Ingrese Opcion: ";
        cin >> input;

        char subOpcion = toupper(input[0]);
        int idx = -1;

        if (input.length() > 1) {
            try {
                idx = stoi(input.substr(1));
            } catch (...) {
                cout << "Formato no valido." << endl;
                continue;
            }
        }

        if (subOpcion == 'V') {
            volver = true;
        } else if (subOpcion == 'R' && idx != -1) {
            Cancion *elegida = alm->getCancionIndice(idx);
            if (elegida != nullptr) {
                lr->reproducirAltiro(elegida, c, alm);

                cancionAct = elegida->getNombre();
                artistaAct = elegida->getArtista();
                albumAct = elegida->getAlbum();
                anioAct = elegida->getAnio();

                cout << "Reproduciendo ahora: " << cancionAct << endl;
            } else {
                cout << "Indice no encontrado en la lista." << endl;
            }
        } else if (subOpcion == 'A' && idx != -1) {
            Cancion *elegida = alm->getCancionIndice(idx);
            if (elegida != nullptr) {
                lr->agregarAlFinal(elegida);
                cout << "Cancion agregada a la lista de reproduccion actual: " << elegida->getNombre() << endl;
            } else {
                cout << "Indice no encontrado" << endl;
            }
        } else if (subOpcion == 'N') {
            string nom, art, alb, ubi;
            int id, an, dur;
            bool idValido = false;

            while (idValido == false) {
                cout << "Ingrese ID interno: ";
                cin >> id;
                if (alm->existeID(id) == true) {
                    cout << "Error: El ID " << id << " ya existe. Intente con otro." << endl;
                } else {
                    idValido = true;
                }
            }

            cout << "Nombre de la cancion: ";
            cin.ignore();
            getline(cin, nom);
            cout << "Artista: ";
            getline(cin, art);
            cout << "Album: ";
            getline(cin, alb);
            cout << "Anio: ";
            cin >> an;
            cout << "Duracion (segundos): ";
            cin >> dur;
            cout << "Ubicacion del archivo: ";
            cin.ignore();
            getline(cin, ubi);

            alm->crearCanción(id, nom, art, alb, an, dur, ubi);
            alm->guardarEnArchivo();
            cout << "Cancion registrada correctamente" << endl;
        } else if (subOpcion == 'D' && idx != -1) {
            Cancion *elegida = alm->getCancionIndice(idx);
            if (elegida != nullptr) {
                alm->eliminarCancion(elegida->getId());
                alm->guardarEnArchivo();
                cout << "Cancion eliminada del registro y del archivo." << endl;
            } else {
                cout << "Indice no encontrado en la lista." << endl;
            }
        } else {
            cout << "Opcion no valida o falta el numero (ej: R1, A2, D3)." << endl;
        }
    }
}


int main() {
    Configuracion *config1 = new Configuracion();
    config1->cargarArchivoConfig();

    srand(time(0));

    Almacenamiento *listaAlmacenamiento = new Almacenamiento();
    lecturaCanciones(listaAlmacenamiento);
    listaAlmacenamiento->cargarReproducciones();


    string entradaMenu;
    bool salir = false;

    ListaReproduccion *lista = new ListaReproduccion();

    string cancionActual = "Ninguna";
    string artistaActual = "Desconocido";
    string albumActual = "Ninguno";
    int anioActual = 0;

    while (salir == false) {
        Cancion* c = lista->getCancionActual();
        if (c != nullptr) {
            cancionActual = c->getNombre();
            artistaActual = c->getArtista();
            albumActual = c->getAlbum();
            anioActual = c->getAnio();
        } else {
            cancionActual = "Ninguna";
            artistaActual = "Desconocido";
            albumActual = "Ninguno";
            anioActual = 0;
        }
        menuOpciones(config1, cancionActual, artistaActual, albumActual, anioActual);

        cin >> entradaMenu;
        char opcion = toupper(entradaMenu[0]);

        switch (opcion) {
            case 'W':
                lista->cambiarEstadoReproduccion(config1);
                break;

            case 'Q':
                lista->pistaAnterior(config1, listaAlmacenamiento);
                break;

            case 'E':
                lista->pistaSiguiente(config1, listaAlmacenamiento);
                break;

            case 'S': {
                bool nuevoEstado = !config1->getRandom();
                config1->setRandom(nuevoEstado);

                if (nuevoEstado) {
                    lista->mezclarCola();
                }
            }
            break;
            case 'R': {
                cout << "Ingrese Opción (0, 1 o 2): ";
                int eleccion;
                cin >> eleccion;
                config1->setRepeticion(eleccion);
                lista->repetirCanciones(eleccion, config1, listaAlmacenamiento, lista);
            }
            break;
            case 'A': {
                string subInput;
                bool volverA = false;

                while (!volverA) {
                    lista->mostrarListaReproduccion();
                    cout << "Ingrese Opción: ";
                    cin >> subInput;

                    if (toupper(subInput[0]) == 'V') {
                        volverA = true;
                    }
                    else if (toupper(subInput[0]) == 'S' && subInput.length() > 1) {
                        try {
                            int num = stoi(subInput.substr(1));
                            lista->saltarACancion(num, config1, listaAlmacenamiento);

                            volverA = true;
                        } catch (...) {
                            cout << "Formato inválido (Ejemplo: S2)" << endl;
                        }
                    }
                }
                break;
            }
            case 'L':
                ejecutarmenuL(listaAlmacenamiento, config1, lista, cancionActual, artistaActual, albumActual,
                              anioActual);
                break;
            case 'X':
                salir = true;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
        }
    }
    delete listaAlmacenamiento;
    delete lista;
    return 0;
}
