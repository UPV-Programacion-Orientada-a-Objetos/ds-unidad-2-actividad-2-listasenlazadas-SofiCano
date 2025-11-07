#ifndef TRAMA_LOAD_H
#define TRAMA_LOAD_H

#include "TramaBase.h"

// Trama de carga que contiene un caracter a decodificar
class TramaLoad : public TramaBase {
private:
    char caracter;
    
public:
    TramaLoad(char c);
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif
