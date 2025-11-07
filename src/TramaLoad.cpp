#include "TramaLoad.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"
#include <iostream>

using namespace std;

TramaLoad::TramaLoad(char c) : caracter(c) {}

void TramaLoad::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    char decodificado = rotor->getMapeo(caracter);
    carga->insertarAlFinal(decodificado);
    
    cout << "Trama recibida: [L," << caracter << "] -> Procesando... -> ";
    cout << "Fragmento '" << caracter << "' decodificado como '" << decodificado << "'. ";
    cout << "Mensaje: ";
    carga->imprimirEstado();
    cout << endl;
}
