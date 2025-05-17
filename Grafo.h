#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <functional>
#include "Nodo.h"

class Grafo {
private:
    std::vector<Nodo> nodos;
    std::vector<std::vector<float>> distancias;

    float calcularDistancia(const Nodo& a, const Nodo& b);
    
public:
    Grafo();
    void agregarNodo(const Nodo& nodo);
    void construirGrafoCompleto();
    float obtenerDistancia(int i, int j) const;
    int cantidadNodos() const;
    const Nodo& obtenerNodo(int i) const;
    const std::vector<std::vector<float>>& obtenerMatrizDistancias() const;
    std::vector<int> prim(int inicio = 0);
    std::vector<float> dijkstra(int origen);
    std::vector<int> recorridoDFSporMST();
};

#include "Grafo.hxx" // Incluye implementaciones aquí

#endif