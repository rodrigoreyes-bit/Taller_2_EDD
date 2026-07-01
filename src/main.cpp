#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../include/classes/Almacenamiento.hpp"
#include "../include/data_structures/ListaReproduccion.hpp"
#include "../include/classes/Configuracion.hpp"
#include "../include/data_structures/MaxHeapCancion.h"
#include "data_structures/MaxHeapArtistas.hpp"

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
    cout << "  F - Buscar canciones" << endl;
    cout << "  T - TOP 10 Artistas y Canciones" << endl;
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
void ejecutarmenuF(Almacenamiento* alm, Configuracion* c, ListaReproduccion* lr) {
    bool volverPrincipal = false;

    while (!volverPrincipal) {
        clearScreen();
        cout << "Busqueda de canciones" << endl << endl;
        cout << "Buscar canciones que contengan: ";
        cin.ignore();
        string texto;
        getline(cin, texto);

        if (texto.empty()) {
            return;
        }

        string textoLower = texto;
        for (char &ch : textoLower) ch = tolower(ch);

        int total = 0;
        Nodo* cursor = alm->getPrimerNodo();
        while (cursor != nullptr) {
            string nombreLower = cursor->dato->getNombre();
            string artistaLower = cursor->dato->getArtista();
            for (char &ch : nombreLower) ch = tolower(ch);
            for (char &ch : artistaLower) ch = tolower(ch);

            if (nombreLower.find(textoLower) != string::npos ||
                artistaLower.find(textoLower) != string::npos) {
                total++;
            }
            cursor = cursor->siguiente;
        }

        if (total == 0) {
            cout << endl << "No se encontraron canciones ni artistas que coincidan con \""
                 << texto << "\"." << endl;
            cout << "Presione Enter para intentar con otro texto...";
            cin.get();
            continue;
        }

        Cancion** resultados = new Cancion*[total];
        int idx = 0;
        cursor = alm->getPrimerNodo();
        while (cursor != nullptr) {
            string nombreLower = cursor->dato->getNombre();
            string artistaLower = cursor->dato->getArtista();
            for (char &ch : nombreLower) ch = tolower(ch);
            for (char &ch : artistaLower) ch = tolower(ch);

            if (nombreLower.find(textoLower) != string::npos ||
                artistaLower.find(textoLower) != string::npos) {
                resultados[idx++] = cursor->dato;
            }
            cursor = cursor->siguiente;
        }

        bool repetirBusqueda = false;
        while (!repetirBusqueda && !volverPrincipal) {
            clearScreen();
            cout << "Busqueda de canciones" << endl << endl;
            cout << "Canciones que contienen \"" << texto << "\":" << endl;
            for (int i = 0; i < total; i++) {
                cout << " " << (i + 1) << ". " << resultados[i]->getNombre()
                     << " - " << resultados[i]->getArtista() << endl;
            }
            cout << endl << "Opciones:" << endl;
            cout << "R<num> - Reproducir cancion seleccionada" << endl;
            cout << "A<num> - Agregar cancion seleccionada al final de la lista de reproduccion actual" << endl;
            cout << "F - Repetir busqueda con un texto diferente" << endl;
            cout << "V - Volver al menu principal" << endl;
            cout << "Ingrese Opcion: ";

            string subInput;
            cin >> subInput;
            char subOp = toupper(subInput[0]);
            int num = -1;

            if (subInput.length() > 1) {
                try {
                    num = stoi(subInput.substr(1));
                } catch (...) {
                    cout << "Formato no valido (ej: R1, A2)." << endl;
                    continue;
                }
            }

            if (subOp == 'V') {
                volverPrincipal = true;
            } else if (subOp == 'F') {
                repetirBusqueda = true;
            } else if (subOp == 'R' && num >= 1 && num <= total) {
                Cancion* elegida = resultados[num - 1];
                lr->reproducirCancionMezclar(elegida, c, alm);
                cout << "Reproduciendo ahora: " << elegida->getNombre() << endl;
                cout << "Presione Enter para continuar...";
                cin.ignore();
                cin.get();
            } else if (subOp == 'A' && num >= 1 && num <= total) {
                Cancion* elegida = resultados[num - 1];
                lr->agregarAlFinal(elegida);
                cout << "Cancion agregada a la lista de reproduccion actual: "
                     << elegida->getNombre() << endl;
                cout << "Presione Enter para continuar...";
                cin.ignore();
                cin.get();
            } else {
                cout << "Opcion no valida o indice fuera de rango." << endl;
            }
        }

        delete[] resultados;
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

            case 'F':
                ejecutarmenuF(listaAlmacenamiento, config1, lista);
                break;

            case 'T':
                {
                bool volverTop = false;
                while (!volverTop) {
                    cout << "Ranking TOP" << endl;
                    cout << "C - Top 10 canciones más escuchadas" << endl;
                    cout << "A - Top 10 artistas más escuchados" << endl;
                    cout << "X - Salir" << endl;
                    cout << "Ingrese Opción: ";
                    string entradita;
                    cin >> entradita;
                    char cTop = toupper(entradita[0]);

                    if (cTop == 'X') {
                        volverTop = true;
                    }
                    else if (cTop == 'C') {
                        bool volverCanciones = false;
                        while (!volverCanciones) {
                            clearScreen();
                            cout << "Ranking TOP 10 Canciones más escuchadas:" << endl;

                            //1) contar cuántas canciones existen en total en el almacenamiento
                            int totalCanciones = 0;
                            Nodo* cursorContar = listaAlmacenamiento->getPrimerNodo();
                            while (cursorContar != nullptr) {
                                totalCanciones++;
                                cursorContar = cursorContar->siguiente;
                            }

                            if (totalCanciones == 0) {
                                cout << "No hay canciones registradas en la biblioteca." << endl;
                            } else {
                                // 2) instanciar el maxheap con la capacidad total calculada
                                MaxHeapCancion* heapCanciones = new MaxHeapCancion(totalCanciones);

                                // 3) insertar todas las canciones de la biblioteca en el Heap
                                Nodo* cursorLlenar = listaAlmacenamiento->getPrimerNodo();
                                while (cursorLlenar != nullptr) {
                                    heapCanciones->insertar(cursorLlenar->dato, cursorLlenar->dato->getReproducciones());
                                    cursorLlenar = cursorLlenar->siguiente;
                                }

                                // 4) det cuantas mostrar (N = un máximo de 10)
                                int canttt;
                                if (totalCanciones < 10) {
                                    canttt = totalCanciones;
                                } else {
                                    canttt = 10;
                                }

                                // Arreglo dinámico auxiliar para guardar las top canciones en orden y permitir R<num> o A<num>
                                Cancion** topArray = new Cancion*[canttt];

                                // 5) extraer ordenadamente del heap y mostrar en pantalla
                                for (int i = 0; i < canttt; i++) {
                                    int reps = 0;
                                    Cancion* topC = heapCanciones->extraerMaximo(reps);
                                    topArray[i] = topC;

                                    cout << (i + 1) << ". [" << reps << "] "
                                         << topC->getNombre() << " - " << topC->getArtista() << endl;
                                }

                                cout << "\nOpciones:" << endl;
                                cout << "  R<num> - Reproducir canción seleccionada (ej: R1)" << endl;
                                cout << "  A<num> - Agregar canción seleccionada al final de la lista" << endl;
                                cout << "  A      - Top 10 artistas más escuchados" << endl;
                                cout << "  V      - Volver al menú principal" << endl;
                                cout << "Ingrese Opción: ";

                                string subOp;
                                cin >> subOp;
                                char accion = toupper(subOp[0]);

                                int indice = -1;
                                if (subOp.length() > 1) {
                                    try {
                                        indice = stoi(subOp.substr(1));
                                    } catch (...) { indice = -1; }
                                }

                                if (accion == 'V') {
                                    volverCanciones = true;
                                    volverTop = true; // Regresa al menú principal del reproductor
                                }
                                else if (accion == 'A' && indice == -1) {
                                    // Cambiar directamente al Top 10 de artistas (rompe este ciclo para ir al menú TOP)
                                    volverCanciones = true;
                                }
                                else if (accion == 'R' && indice >= 1 && indice <= canttt) {
                                    Cancion* elegida = topArray[indice - 1];
                                    lista->reproducirAltiro(elegida, config1, listaAlmacenamiento);

                                    cancionActual = elegida->getNombre();
                                    artistaActual = elegida->getArtista();
                                    albumActual = elegida->getAlbum();
                                    anioActual = elegida->getAnio();

                                    cout << "Reproduciendo ahora: " << cancionActual << endl;
                                    volverCanciones = true;
                                    volverTop = true;
                                }
                                else if (accion == 'A' && indice >= 1 && indice <= canttt) {
                                    Cancion* elegida = topArray[indice - 1];
                                    lista->agregarAlFinal(elegida);
                                    cout << "Cancion agregada: " << elegida->getNombre() << endl;
                                } else {
                                    cout << "Opción inválida." << endl;
                                }

                                // limpieza de memoria dinamica local
                                delete[] topArray;
                                delete heapCanciones;
                            }
                        }
                    }
                    else if (cTop == 'A') {
                        int totalArtistas = 0;
                        Artista* artistaActual = listaAlmacenamiento->getPrimerArtista();

                        while (artistaActual != nullptr) {
                            totalArtistas++;
                            artistaActual = artistaActual->getSiguienteArtista();
                        }

                        if (totalArtistas == 0) {
                            cout << "No hay artistas registrados en el sistema.\n";
                        } else {
                            MaxHeapArtistas heapArtistas(totalArtistas);

                            artistaActual = listaAlmacenamiento->getPrimerArtista();
                            while (artistaActual != nullptr) {
                                heapArtistas.insertar(artistaActual, artistaActual->getContador());
                                artistaActual = artistaActual->getSiguienteArtista();
                            }

                            cout << "   RANKING TOP 10 ARTISTAS MAS ESCUCHADOS\n";

                            int limite = (heapArtistas.getTamano() < 10) ? heapArtistas.getTamano() : 10;

                            Artista** topMostrados = new Artista*[limite];

                            for (int i = 1; i <= limite; i++) {
                                int reprosSalida = 0;
                                Artista* topArtista = heapArtistas.extraerMaximo(reprosSalida);

                                if (topArtista != nullptr) {
                                    cout << "  " << i << ". [" << reprosSalida << " reprod.] " << topArtista->getNombre() << "\n";
                                    topMostrados[i - 1] = topArtista; // Guardamos la referencia
                                }
                            }
                            cout << "=========================================\n\n";

                            cout << "¿Deseas seleccionar un artista para ver sus canciones alfabéticamente? (S/N): ";
                            char respuesta;
                            cin >> respuesta;

                            if (respuesta == 'S' || respuesta == 's') {
                                cout << "Ingresa el número del artista (1 al " << limite << "): ";
                                int num;
                                cin >> num;

                                if (num >= 1 && num <= limite) {
                                    Artista* seleccionado = topMostrados[num - 1];
                                    cout << "\n-----------------------------------------\n";
                                    cout << " Canciones de: " << seleccionado->getNombre() << " (Orden A-Z):\n";
                                    cout << "-----------------------------------------\n";

                                    // LLAMADA AL INORDEN DEL AVL PRIVADO DEL ARTISTA
                                    seleccionado->getCancionesAVL()->mostrarEnOrden();

                                    cout << "-----------------------------------------\n\n";
                                } else {
                                    cout << "Número inválido.\n\n";
                                }
                            }

                            delete[] topMostrados;
                        }
                    }//fjfjf




                    }
                }
                break;
            }

            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
        }
    }
    delete listaAlmacenamiento;
    delete lista;
    return 0;
}
