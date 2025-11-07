#include "SerialPort.h"
#include "TramaLoad.h"
#include "TramaMap.h"
#include <cstring>
#include <cstdlib>

void trim(char* str) {
    int inicio = 0;
    int fin = strlen(str) - 1;
    
    // Eliminar espacios al inicio
    while (str[inicio] == ' ' || str[inicio] == '\t' || 
           str[inicio] == '\n' || str[inicio] == '\r') {
        inicio++;
    }
    
    // Eliminar espacios al final
    while (fin >= inicio && (str[fin] == ' ' || str[fin] == '\t' || 
           str[fin] == '\n' || str[fin] == '\r')) {
        fin--;
    }
    
    // Mover la cadena al inicio
    int i;
    for (i = 0; inicio <= fin; i++, inicio++) {
        str[i] = str[inicio];
    }
    str[i] = '\0';
}

TramaBase* parsearTrama(char* linea) {
    trim(linea);
    
    if (strlen(linea) < 3) {
        return nullptr;
    }
    
    char tipo = linea[0];
    
    if (linea[1] != ',') {
        return nullptr;
    }
    
    char* valor = linea + 2;
    
    if (tipo == 'L' || tipo == 'l') {
        char caracter = valor[0];
        
        if (strcmp(valor, "Space") == 0 || strcmp(valor, "space") == 0 || 
            strcmp(valor, "SPACE") == 0) {
            caracter = ' ';
        }
        
        return new TramaLoad(caracter);
    } 
    else if (tipo == 'M' || tipo == 'm') {
        int rotacion = atoi(valor);
        return new TramaMap(rotacion);
    }
    
    return nullptr;
}
