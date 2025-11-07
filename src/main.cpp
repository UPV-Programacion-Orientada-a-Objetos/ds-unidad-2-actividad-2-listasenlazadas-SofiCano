// Decodificador de Protocolo Industrial PRT-7
// Archivo principal

#include <iostream>
#include <cstring>
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"
#include "TramaBase.h"
#include "SerialPort.h"

using namespace std;

int main() {
    cout << "======================================" << endl;
    cout << "Decodificador de Protocolo Industrial PRT-7" << endl;
    cout << "======================================" << endl;
    cout << "\nIniciando Decodificador PRT-7..." << endl;
    
    // Inicializar estructuras de datos
    ListaDeCarga miListaDeCarga;
    RotorDeMapeo miRotorDeMapeo;
    
    cout << "\nSistema inicializado. Lista de carga vacia." << endl;
    cout << "Rotor inicializado con alfabeto A-Z y espacio.\n" << endl;
    
    cout << "MODO DE ENTRADA: Simulacion por consola" << endl;
    cout << "========================================" << endl;
    cout << "Ingrese las tramas una por una (formato: L,X o M,N)" << endl;
    cout << "Ejemplos: L,H  |  M,2  |  L,Space" << endl;
    cout << "Escriba 'FIN' para terminar y ver el mensaje.\n" << endl;
    
    // Buffer para leer lineas
    const int BUFFER_SIZE = 100;
    char linea[BUFFER_SIZE];
    
    // Bucle principal de procesamiento
    while (true) {
        cout << "Trama> ";
        cin.getline(linea, BUFFER_SIZE);
        
        // Verificar si se termino la entrada
        if (strcmp(linea, "FIN") == 0 || strcmp(linea, "fin") == 0) {
            break;
        }
        
        // Parsear la trama
        TramaBase* trama = parsearTrama(linea);
        
        if (trama != nullptr) {
            // Procesar la trama usando polimorfismo
            trama->procesar(&miListaDeCarga, &miRotorDeMapeo);
            
            // Liberar memoria
            delete trama;
        } else {
            cout << "ERROR: Trama mal formada. Formato correcto: L,X o M,N" << endl;
        }
    }
    
    // Mostrar mensaje final
    cout << "\nFlujo de datos terminado." << endl;
    miListaDeCarga.imprimirMensaje();
    
    cout << "\nLiberando memoria... Sistema apagado." << endl;
    
    return 0;
}
