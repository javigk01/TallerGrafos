#include <iostream>
#include <vector>
#include "Grafo.h"
#include "Nodo.h"

// Function prototype for guardarSalida
void guardarSalida(const std::string& nombreArchivo, const std::vector<int>& secuencia, const Grafo& grafo);

int main() {
    Grafo grafo;

    // Coordenadas de ejemplo
    grafo.agregarNodo(Nodo(0, 0));
    grafo.agregarNodo(Nodo(10, 10));
    grafo.agregarNodo(Nodo(20, 5));
    grafo.agregarNodo(Nodo(5, 20));
    grafo.agregarNodo(Nodo(15, 15));

    grafo.construirGrafoCompleto();

    // Recorrido con heurística basada en MST + DFS
    std::vector<int> secuencia = grafo.recorridoDFSporMST();
    // Mostrar en consola
std::cout << "Secuencia de perforación:\n";
for (int idx : secuencia) {
    const Nodo& p = grafo.obtenerNodo(idx);
    std::cout << "(" << p.x << ", " << p.y << ")\n";
}

// Guardar en archivo de salida
guardarSalida("salida.txt", secuencia, grafo);

    return 0;

}


#include <fstream>

void guardarSalida(const std::string& nombreArchivo, const std::vector<int>& secuencia, const Grafo& grafo) {
    std::ofstream out(nombreArchivo);
    if (!out.is_open()) {
        std::cerr << "Error: no se pudo abrir el archivo de salida.\n";
        return;
    }

    // Solo un circuito para este caso
    out << "1\n";                       // Número de circuitos
    out << secuencia.size() << "\n";   // Número de agujeros

    for (int idx : secuencia) {
        const Nodo& nodo = grafo.obtenerNodo(idx);
        out << nodo.x << " " << nodo.y << "\n";
    }

    out.close();
    std::cout << "Archivo '" << nombreArchivo << "' generado exitosamente.\n";
}
