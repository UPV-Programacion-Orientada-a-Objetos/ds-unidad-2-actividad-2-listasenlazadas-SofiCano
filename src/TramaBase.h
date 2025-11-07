#ifndef TRAMA_BASE_H
#define TRAMA_BASE_H

class ListaDeCarga;
class RotorDeMapeo;

// Clase base abstracta para todas las tramas
class TramaBase {
public:
    // Metodo virtual puro para procesar la trama
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
    
    // Destructor virtual para correcta limpieza polimorfica
    virtual ~TramaBase() {}
};

#endif
