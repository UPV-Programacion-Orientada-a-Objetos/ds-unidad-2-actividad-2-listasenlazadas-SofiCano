#ifndef LISTA_DE_CARGA_H
#define LISTA_DE_CARGA_H

// Nodo de la lista doblemente enlazada
struct NodoCarga {
    char dato;
    NodoCarga* siguiente;
    NodoCarga* previo;
    
    NodoCarga(char c);
};

// Lista doblemente enlazada para almacenar caracteres decodificados
class ListaDeCarga {
private:
    NodoCarga* cabeza;
    NodoCarga* cola;
    
public:
    ListaDeCarga();
    ~ListaDeCarga();
    
    void insertarAlFinal(char dato);
    void imprimirMensaje();
    void imprimirEstado();
};

#endif
