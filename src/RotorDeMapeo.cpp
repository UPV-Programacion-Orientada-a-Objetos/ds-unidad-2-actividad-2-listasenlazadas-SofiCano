#include "RotorDeMapeo.h"
#include <cstddef>

NodoRotor::NodoRotor(char c) : dato(c), siguiente(nullptr), previo(nullptr) {}

RotorDeMapeo::RotorDeMapeo() {
    // Inicializar con A-Z y espacio (27 caracteres)
    const char alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    int longitud = 27;
    
    NodoRotor* primero = nullptr;
    NodoRotor* ultimo = nullptr;
    
    // Crear la lista circular
    for (int i = 0; i < longitud; i++) {
        NodoRotor* nuevoNodo = new NodoRotor(alfabeto[i]);
        
        if (primero == nullptr) {
            primero = nuevoNodo;
            ultimo = nuevoNodo;
            cabeza = primero;
        } else {
            ultimo->siguiente = nuevoNodo;
            nuevoNodo->previo = ultimo;
            ultimo = nuevoNodo;
        }
    }
    
    // Cerrar el circulo
    ultimo->siguiente = primero;
    primero->previo = ultimo;
}

RotorDeMapeo::~RotorDeMapeo() {
    if (cabeza == nullptr) return;
    
    NodoRotor* actual = cabeza->siguiente;
    NodoRotor* temp;
    
    // Romper el circulo
    cabeza->siguiente = nullptr;
    
    while (actual != nullptr) {
        temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
    delete cabeza;
}

void RotorDeMapeo::rotar(int n) {
    if (n > 0) {
        // Rotar hacia adelante
        for (int i = 0; i < n; i++) {
            cabeza = cabeza->siguiente;
        }
    } else if (n < 0) {
        // Rotar hacia atras
        for (int i = 0; i > n; i--) {
            cabeza = cabeza->previo;
        }
    }
}

char RotorDeMapeo::getMapeo(char in) {
    // Buscar el caracter en el rotor
    NodoRotor* actual = cabeza;
    int posicion = 0;
    bool encontrado = false;
    
    NodoRotor* inicio = cabeza;
    do {
        if (actual->dato == in) {
            encontrado = true;
            break;
        }
        posicion++;
        actual = actual->siguiente;
    } while (actual != inicio);
    
    if (!encontrado) {
        return in;
    }
    
    return cabeza->dato;
}
