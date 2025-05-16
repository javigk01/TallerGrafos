#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <cmath>
#include <queue>
#include <set>
#include <limits>
#include <functional>
#include <algorithm>
#include "Nodo.h"

class Grafo {
private:
    std::vector<Nodo> nodos;
    std::vector<std::vector<float>> distancias;

    float calcularDistancia(const Nodo& a, const Nodo& b) {
        return std::sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
    }

public:
    Grafo() {}

    void agregarNodo(const Nodo& nodo) {
        nodos.push_back(nodo);
    }

    void construirGrafoCompleto() {
        int n = nodos.size();
        distancias.resize(n, std::vector<float>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                distancias[i][j] = (i == j) ? 0 : calcularDistancia(nodos[i], nodos[j]);
            }
        }
    }

    float obtenerDistancia(int i, int j) const {
        return distancias[i][j];
    }

    int cantidadNodos() const {
        return nodos.size();
    }

    const Nodo& obtenerNodo(int i) const {
        return nodos[i];
    }

    const std::vector<std::vector<float>>& obtenerMatrizDistancias() const {
        return distancias;
    }

    std::vector<int> prim(int inicio = 0) {
        int n = cantidadNodos();
        std::vector<bool> visitado(n, false);
        std::vector<int> padre(n, -1);
        std::vector<float> clave(n, std::numeric_limits<float>::max());
        clave[inicio] = 0;
    
        for (int count = 0; count < n - 1; ++count) {
            // Buscar el nodo con clave mínima no visitado
            float min = std::numeric_limits<float>::max();
            int u = -1;
            for (int v = 0; v < n; ++v) {
                if (!visitado[v] && clave[v] < min) {
                    min = clave[v];
                    u = v;
                }
            }
    
            visitado[u] = true;
    
            // Actualizar claves y padres
            for (int v = 0; v < n; ++v) {
                float peso = distancias[u][v];
                if (!visitado[v] && peso < clave[v]) {
                    padre[v] = u;
                    clave[v] = peso;
                }
            }
        }
    
        return padre; // Representa el MST
    }
    
    std::vector<float> dijkstra(int origen) {
        int n = cantidadNodos();
        std::vector<float> distancia(n, std::numeric_limits<float>::max());
        std::vector<bool> visitado(n, false);
        distancia[origen] = 0;
    
        for (int i = 0; i < n - 1; ++i) {
            // Nodo con menor distancia no visitado
            float min = std::numeric_limits<float>::max();
            int u = -1;
            for (int v = 0; v < n; ++v) {
                if (!visitado[v] && distancia[v] < min) {
                    min = distancia[v];
                    u = v;
                }
            }
    
            if (u == -1) break;
            visitado[u] = true;
    
            for (int v = 0; v < n; ++v) {
                float peso = distancias[u][v];
                if (!visitado[v] && distancia[u] + peso < distancia[v]) {
                    distancia[v] = distancia[u] + peso;
                }
            }
        }
    
        return distancia;
    }

std::vector<int> recorridoDFSporMST() {
    std::vector<int> mst = prim();
    int n = cantidadNodos();

    // Construir lista de adyacencia del MST
    std::vector<std::vector<int>> adyacencia(n);
    for (int i = 0; i < n; ++i) {
        if (mst[i] != -1) {
            adyacencia[i].push_back(mst[i]);
            adyacencia[mst[i]].push_back(i);
        }
    }

    // Encontrar nodo más cercano a (0,0)
    int inicio = 0;
    float minDist = std::numeric_limits<float>::max();
    Nodo origen(0, 0);
    for (int i = 0; i < n; ++i) {
        float d = std::sqrt((nodos[i].x - origen.x)*(nodos[i].x - origen.x) +
                            (nodos[i].y - origen.y)*(nodos[i].y - origen.y));
        if (d < minDist) {
            minDist = d;
            inicio = i;
        }
    }

    std::vector<bool> visitado(n, false);
    std::vector<int> recorrido;

    // DFS recursiva con vecinos ordenados por distancia
    std::function<void(int)> dfs = [&](int u) {
        visitado[u] = true;
        recorrido.push_back(u);

        // Ordenar vecinos por distancia creciente desde u
        std::sort(adyacencia[u].begin(), adyacencia[u].end(), [&](int a, int b) {
            return obtenerDistancia(u, a) < obtenerDistancia(u, b);
        });

        for (int v : adyacencia[u]) {
            if (!visitado[v]) dfs(v);
        }
    };

    dfs(inicio);
    return recorrido;
}
    
};

#endif
