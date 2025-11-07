#ifndef ROTOR_DE_MAPEO_H
#define ROTOR_DE_MAPEO_H

// Nodo de la lista circular doblemente enlazada
struct NodoRotor {
    char dato;
    NodoRotor* siguiente;
    NodoRotor* previo;
    
    NodoRotor(char c);
};

// Lista circular doblemente enlazada que actua como disco de cifrado
class RotorDeMapeo {
private:
    NodoRotor* cabeza;
    
public:
    RotorDeMapeo();
    ~RotorDeMapeo();
    
    void rotar(int n);
    char getMapeo(char in);
};

#endif
