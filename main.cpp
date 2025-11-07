// Decodificador de Protocolo Industrial PRT-7
// Implementa listas circulares y doblemente enlazadas
// Usa polimorfismo para procesar tramas LOAD y MAP

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

// Declaraciones adelantadas
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

// Nodo de la lista circular doblemente enlazada del rotor
struct NodoRotor {
    char dato;              // Caracter almacenado (A-Z o espacio)
    NodoRotor* siguiente;   // Puntero al siguiente nodo
    NodoRotor* previo;      // Puntero al nodo anterior
    
    NodoRotor(char c) : dato(c), siguiente(nullptr), previo(nullptr) {}
};

// Lista circular doblemente enlazada que actua como disco de cifrado
// Contiene el alfabeto A-Z y el espacio, puede rotar para cambiar el mapeo
class RotorDeMapeo {
private:
    NodoRotor* cabeza;  // Puntero a la posicion "cero" actual del rotor
    
public:
    // Constructor que inicializa el rotor con el alfabeto A-Z y espacio
    RotorDeMapeo() {
        // Inicializar con A-Z y espacio (27 caracteres)
        const char alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
        int longitud = 27;
        
        NodoRotor* primero = nullptr;
        NodoRotor* ultimo = nullptr;
        
        // Crear la lista circular
        for (int i = 0; i < longitud; i++) {
            NodoRotor* nuevoNodo = new NodoRotor(alfabeto[i]);
            
            if (primero == nullptr) {
                primero = nuevoNodo;
                ultimo = nuevoNodo;
                cabeza = primero; // La cabeza apunta a 'A'
            } else {
                ultimo->siguiente = nuevoNodo;
                nuevoNodo->previo = ultimo;
                ultimo = nuevoNodo;
            }
        }
        
        // Cerrar el circulo
        ultimo->siguiente = primero;
        primero->previo = ultimo;
    }
    
    // Rota el rotor N posiciones (positivo = adelante, negativo = atras)
    // Mueve el puntero cabeza N posiciones de forma circular
    void rotar(int n) {
        if (n > 0) {
            // Rotar hacia adelante
            for (int i = 0; i < n; i++) {
                cabeza = cabeza->siguiente;
            }
        } else if (n < 0) {
            // Rotar hacia atras
            for (int i = 0; i > n; i--) {
                cabeza = cabeza->previo;
            }
        }
    }
    
    // Obtiene el caracter mapeado segun la rotacion actual del rotor
    // Busca el caracter 'in' y retorna el caracter mapeado
    char getMapeo(char in) {
        // Buscar el caracter en el rotor
        NodoRotor* actual = cabeza;
        int posicion = 0;
        bool encontrado = false;
        
        // Primera vuelta completa para encontrar el caracter
        NodoRotor* inicio = cabeza;
        do {
            if (actual->dato == in) {
                encontrado = true;
                break;
            }
            posicion++;
            actual = actual->siguiente;
        } while (actual != inicio);
        
        if (!encontrado) {
            // Si no se encuentra, devolver el mismo caracter
            return in;
        }
        
        // El mapeo es: la posicion del caracter desde la cabeza actual
        // determina que caracter del alfabeto original representa
        return cabeza->dato;
    }
    
    // Destructor que libera toda la memoria de la lista circular
    ~RotorDeMapeo() {
        if (cabeza == nullptr) return;
        
        NodoRotor* actual = cabeza->siguiente;
        NodoRotor* temp;
        
        // Romper el circulo
        cabeza->siguiente = nullptr;
        
        while (actual != nullptr) {
            temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
        delete cabeza;
    }
};

// Nodo de la lista doblemente enlazada de carga
struct NodoCarga {
    char dato;              // Caracter decodificado almacenado
    NodoCarga* siguiente;   // Puntero al siguiente nodo
    NodoCarga* previo;      // Puntero al nodo anterior
    
    NodoCarga(char c) : dato(c), siguiente(nullptr), previo(nullptr) {}
};

// Lista doblemente enlazada para almacenar los caracteres decodificados
// Mantiene el orden de los caracteres y permite construir el mensaje final
class ListaDeCarga {
private:
    NodoCarga* cabeza;  // Puntero al primer nodo
    NodoCarga* cola;    // Puntero al ultimo nodo
    
public:
    // Constructor que inicializa la lista vacia
    ListaDeCarga() : cabeza(nullptr), cola(nullptr) {}
    
    // Inserta un caracter al final de la lista
    void insertarAlFinal(char dato) {
        NodoCarga* nuevoNodo = new NodoCarga(dato);
        
        if (cabeza == nullptr) {
            // Lista vacia
            cabeza = nuevoNodo;
            cola = nuevoNodo;
        } else {
            // Insertar al final
            cola->siguiente = nuevoNodo;
            nuevoNodo->previo = cola;
            cola = nuevoNodo;
        }
    }
    
    // Imprime el mensaje completo almacenado en la lista
    void imprimirMensaje() {
        cout << "\n---" << endl;
        cout << "MENSAJE OCULTO ENSAMBLADO:" << endl;
        
        NodoCarga* actual = cabeza;
        while (actual != nullptr) {
            cout << actual->dato;
            actual = actual->siguiente;
        }
        
        cout << "\n---" << endl;
    }
    
    // Imprime el contenido actual de la lista entre corchetes
    void imprimirEstado() {
        NodoCarga* actual = cabeza;
        while (actual != nullptr) {
            cout << "[" << actual->dato << "]";
            actual = actual->siguiente;
        }
    }
    
    // Destructor que libera toda la memoria de la lista
    ~ListaDeCarga() {
        NodoCarga* actual = cabeza;
        NodoCarga* temp;
        
        while (actual != nullptr) {
            temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }
};

// Trama de carga que contiene un caracter a decodificar
// Representa una trama del tipo "L,X" donde X es un caracter
class TramaLoad : public TramaBase {
private:
    char caracter;  // Caracter recibido en la trama
    
public:
    TramaLoad(char c) : caracter(c) {}
    
    // Procesa la trama LOAD: decodifica el caracter y lo añade a la lista
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override {
        char decodificado = rotor->getMapeo(caracter);
        carga->insertarAlFinal(decodificado);
        
        cout << "Trama recibida: [L," << caracter << "] -> Procesando... -> ";
        cout << "Fragmento '" << caracter << "' decodificado como '" << decodificado << "'. ";
        cout << "Mensaje: ";
        carga->imprimirEstado();
        cout << endl;
    }
};

// Trama de mapeo que rota el rotor de cifrado
// Representa una trama del tipo "M,N" donde N es un entero
class TramaMap : public TramaBase {
private:
    int rotacion;  // Numero de posiciones a rotar (puede ser negativo)
    
public:
    TramaMap(int n) : rotacion(n) {}
    
    // Procesa la trama MAP: rota el rotor N posiciones
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override {
        rotor->rotar(rotacion);
        
        cout << "\nTrama recibida: [M," << rotacion << "] -> Procesando... -> ";
        cout << "ROTANDO ROTOR ";
        if (rotacion > 0) cout << "+";
        cout << rotacion << ".\n" << endl;
    }
};

// Elimina espacios en blanco al inicio y final de una cadena
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

// Parsea una linea de trama y crea el objeto correspondiente
// Formato esperado: "L,X" o "M,N"
// Retorna puntero a TramaBase o nullptr si hay error
TramaBase* parsearTrama(char* linea) {
    // Limpiar la linea
    trim(linea);
    
    // Verificar longitud minima
    if (strlen(linea) < 3) {
        return nullptr;
    }
    
    char tipo = linea[0];
    
    // Verificar que tiene coma
    if (linea[1] != ',') {
        return nullptr;
    }
    
    // Obtener el valor despues de la coma
    char* valor = linea + 2;
    
    if (tipo == 'L' || tipo == 'l') {
        // Trama LOAD
        char caracter = valor[0];
        
        // Manejar caso especial de "Space"
        if (strcmp(valor, "Space") == 0 || strcmp(valor, "space") == 0 || 
            strcmp(valor, "SPACE") == 0) {
            caracter = ' ';
        }
        
        return new TramaLoad(caracter);
    } 
    else if (tipo == 'M' || tipo == 'm') {
        // Trama MAP
        int rotacion = atoi(valor);
        return new TramaMap(rotacion);
    }
    
    return nullptr;
}

// Funcion principal del decodificador PRT-7
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
