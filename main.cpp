#include <iostream>
#include <vector>
#include "Grafo.h"
#include "Nodo.h"
#include "Circuito.h"
#include <fstream>
#include <sstream>

// Function prototype for guardarSalida
void guardarSalida(const std::string& nombreArchivo, const std::vector<int>& secuencia, const Grafo& grafo);
std::vector<Circuito> leerEntrada(const std::string& nombreArchivo);

int main() {
    std::vector<Circuito> circuitos = leerEntrada("entrada.txt");

    for (int i = 0; i < circuitos.size(); ++i) {
        Grafo grafo;

        // Agregar nodos del circuito actual
        for (const Nodo& nodo : circuitos[i].agujeros) {
            grafo.agregarNodo(nodo);
        }

        grafo.construirGrafoCompleto();

        // Obtener secuencia de perforación
        std::vector<int> secuencia = grafo.recorridoDFSporMST();

        // Guardar salida individual para cada circuito
        std::string nombreSalida = "salida_circuito_" + std::to_string(i + 1) + ".txt";
        guardarSalida(nombreSalida, secuencia, grafo);
    }

    return 0;
}


std::vector<Circuito> leerEntrada(const std::string& nombreArchivo) {
    std::ifstream in(nombreArchivo);
    if (!in.is_open()) {
        std::cerr << "Error: no se pudo abrir el archivo de entrada.\n";
        return {};
    }

    int n; // número de circuitos
    in >> n;

    std::vector<Circuito> circuitos;

    for (int i = 0; i < n; ++i) {
        int mi; // cantidad de agujeros
        in >> mi;

        Circuito c;
        for (int j = 0; j < mi; ++j) {
            float x, y;
            in >> x >> y;
            c.agujeros.push_back(Nodo(x, y));
        }
        circuitos.push_back(c);
    }

    in.close();
    return circuitos;
}

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
