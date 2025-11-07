#ifndef TRAMA_MAP_H
#define TRAMA_MAP_H

#include "TramaBase.h"

// Trama de mapeo que rota el rotor de cifrado
class TramaMap : public TramaBase {
private:
    int rotacion;
    
public:
    TramaMap(int n);
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif
