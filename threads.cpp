#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <random>
#include <algorithm>

using namespace std;

list<int> linkedList;
mutex listMutex;

void eliminar() {
    for (int i = 0; i < 10; ++i) {
        int valor = rand() % 100;
        {
            std::lock_guard<std::mutex> lock(listMutex);
            auto it = std::find_if(linkedList.begin(), linkedList.end(), [valor](int element) {
                return element == valor;
            });
            if (it != linkedList.end()) {
                linkedList.erase(it);
                std::cout << "Eliminando: " << valor << std::endl;
            } else {
                std::cout << "No se eliminó " << valor << std::endl;
            }
        }
    }
}

void insertar() {
    for (int i = 0; i < 10; ++i) {
        int valor = rand() % 100;
        {
            lock_guard<mutex> lock(listMutex);
            linkedList.push_back(valor);
            cout << "Insertando: " << valor << endl;
        }
    }
}

void buscar() {
    for (int i = 0; i < 10; ++i) {
        int valor = rand() % 100;
        {
            lock_guard<mutex> lock(listMutex);
            auto it = find(linkedList.begin(), linkedList.end(), valor);
            if (it != linkedList.end()) {
                cout << "Buscado: " << valor << endl;
            } else {
                cout << "No encontrado: " << valor << endl;
            }
        }
    }
}

void modificar() {
    for (int i = 0; i < 10; ++i) {
        int valor = rand() % 100;
        int cantidad = rand() % 10;
        {
            lock_guard<mutex> lock(listMutex);
            auto it = find(linkedList.begin(), linkedList.end(), valor);
            if (it != linkedList.end()) {
                *it += cantidad;
                cout << "Modificando " << valor << " a " << *it << endl;
            } else {
                cout << "No se encontró " << valor << endl;
            }
        }
    }
}

int main() {
    // Se utiliza srand para inicializar la semilla del generador de números aleatorios
    srand(static_cast<unsigned>(time(nullptr)));

    // Se crean cuatro objetos de tipo std::thread, uno para cada función (eliminar, insertar, buscar, modificar)
    std::thread threadEliminar(eliminar);
    std::thread threadInsertar(insertar);
    std::thread threadBuscar(buscar);
    std::thread threadModificar(modificar);

    // Se utiliza el método join para esperar a que cada hilo termine su ejecución antes de continuar
    threadEliminar.join();
    threadInsertar.join();
    threadBuscar.join();
    threadModificar.join();

    // Se devuelve 0 para indicar que el programa terminó correctamente
    return 0;
}