#include "ListaDeCarga.h"
#include <iostream>
#include <cstddef>

using namespace std;

NodoCarga::NodoCarga(char c) : dato(c), siguiente(nullptr), previo(nullptr) {}

ListaDeCarga::ListaDeCarga() : cabeza(nullptr), cola(nullptr) {}

ListaDeCarga::~ListaDeCarga() {
    NodoCarga* actual = cabeza;
    NodoCarga* temp;
    
    while (actual != nullptr) {
        temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
}

void ListaDeCarga::insertarAlFinal(char dato) {
    NodoCarga* nuevoNodo = new NodoCarga(dato);
    
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    } else {
        cola->siguiente = nuevoNodo;
        nuevoNodo->previo = cola;
        cola = nuevoNodo;
    }
}

void ListaDeCarga::imprimirMensaje() {
    cout << "\n---" << endl;
    cout << "MENSAJE OCULTO ENSAMBLADO:" << endl;
    
    NodoCarga* actual = cabeza;
    while (actual != nullptr) {
        cout << actual->dato;
        actual = actual->siguiente;
    }
    
    cout << "\n---" << endl;
}

void ListaDeCarga::imprimirEstado() {
    NodoCarga* actual = cabeza;
    while (actual != nullptr) {
        cout << "[" << actual->dato << "]";
        actual = actual->siguiente;
    }
}
