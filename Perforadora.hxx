#ifndef PERFORADORA_HXX
#define PERFORADORA_HXX

#include <fstream>
#include <iostream>
#include <sstream>

void Perforadora::procesarCircuitosDesdeArchivo(const std::string& archivoEntrada) {
    std::vector<std::vector<Nodo>> circuitos = leerCircuitos(archivoEntrada);
    for (size_t i = 0; i < circuitos.size(); ++i) {
        Grafo grafo;

        // Agregar nodo (0,0)
        grafo.agregarNodo(Nodo(0.0, 0.0));

        // Agregar agujeros del circuito
        for (const Nodo& nodo : circuitos[i]) {
            grafo.agregarNodo(nodo);
        }

        grafo.construirGrafoCompleto();

        std::vector<int> secuencia = grafo.recorridoDFSporMST();

        std::string nombreSalida = "salida_circuito_" + std::to_string(i + 1) + ".txt";
        guardarSalida(nombreSalida, secuencia, grafo);
    }
}

std::vector<std::vector<Nodo>> Perforadora::leerCircuitos(const std::string& archivo) {
    std::ifstream in(archivo);
    if (!in.is_open()) {
        std::cerr << "No se pudo abrir el archivo de entrada.\n";
        return {};
    }

    int n;
    in >> n;

    std::vector<std::vector<Nodo>> circuitos(n);
    for (int i = 0; i < n; ++i) {
        int m;
        in >> m;

        for (int j = 0; j < m; ++j) {
            float x, y;
            in >> x >> y;
            circuitos[i].emplace_back(x, y);
        }
    }

    return circuitos;
}

void Perforadora::guardarSalida(const std::string& archivo, const std::vector<int>& secuencia, const Grafo& grafo) {
    std::ofstream out(archivo);
    if (!out.is_open()) {
        std::cerr << "No se pudo abrir el archivo de salida.\n";
        return;
    }

    out << "1\n";  // Solo un circuito
    out << secuencia.size() + 1 << "\n"; // +1 para el punto (0,0) final

    // Imprimir puntos y calcular distancia
    float distanciaTotal = 0.0f;
    for (size_t i = 0; i < secuencia.size(); ++i) {
        const Nodo& actual = grafo.obtenerNodo(secuencia[i]);
        out << actual.x << " " << actual.y << "\n";

        if (i > 0) {
            const Nodo& anterior = grafo.obtenerNodo(secuencia[i - 1]);
            float dx = actual.x - anterior.x;
            float dy = actual.y - anterior.y;
            distanciaTotal += std::sqrt(dx * dx + dy * dy);
        }
    }

    // Distancia del último nodo de regreso a (0,0)
    const Nodo& ultimo = grafo.obtenerNodo(secuencia.back());
    if (!(ultimo.x == 0.0f && ultimo.y == 0.0f)) {
        out << "0 0\n";
        distanciaTotal += std::sqrt(ultimo.x * ultimo.x + ultimo.y * ultimo.y);
    }

    std::cout << "Archivo '" << archivo << "' generado exitosamente.\n";
    std::cout << "Distancia total recorrida: " << distanciaTotal << " mm\n";
}


#endif
