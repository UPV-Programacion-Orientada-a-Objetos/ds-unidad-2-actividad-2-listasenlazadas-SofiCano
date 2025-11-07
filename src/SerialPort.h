#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include "TramaBase.h"

// Funciones de parseo de tramas
void trim(char* str);
TramaBase* parsearTrama(char* linea);

#endif
