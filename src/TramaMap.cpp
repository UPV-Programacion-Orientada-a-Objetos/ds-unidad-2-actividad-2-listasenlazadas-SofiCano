#include "TramaMap.h"
#include "RotorDeMapeo.h"
#include <iostream>

using namespace std;

TramaMap::TramaMap(int n) : rotacion(n) {}

void TramaMap::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    rotor->rotar(rotacion);
    
    cout << "\nTrama recibida: [M," << rotacion << "] -> Procesando... -> ";
    cout << "ROTANDO ROTOR ";
    if (rotacion > 0) cout << "+";
    cout << rotacion << ".\n" << endl;
}
