#ifndef GRAFO_HXX
#define GRAFO_HXX

#include <cmath>
#include <limits>
#include <algorithm>

Grafo::Grafo() {}

float Grafo::calcularDistancia(const Nodo& a, const Nodo& b) {
    return std::sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

void Grafo::agregarNodo(const Nodo& nodo) {
    nodos.push_back(nodo);
}

void Grafo::construirGrafoCompleto() {
    int n = nodos.size();
    distancias.resize(n, std::vector<float>(n, 0));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            distancias[i][j] = (i == j) ? 0 : calcularDistancia(nodos[i], nodos[j]);
        }
    }
}

float Grafo::obtenerDistancia(int i, int j) const {
    return distancias[i][j];
}

int Grafo::cantidadNodos() const {
    return nodos.size();
}

const Nodo& Grafo::obtenerNodo(int i) const {
    return nodos[i];
}

const std::vector<std::vector<float>>& Grafo::obtenerMatrizDistancias() const {
    return distancias;
}

std::vector<int> Grafo::prim(int inicio) {
    int n = cantidadNodos();
    std::vector<bool> visitado(n, false);
    std::vector<int> padre(n, -1);
    std::vector<float> clave(n, std::numeric_limits<float>::max());
    clave[inicio] = 0;
    
    for(int count = 0; count < n-1; ++count) {
        float min = std::numeric_limits<float>::max();
        int u = -1;
        
        for(int v = 0; v < n; ++v) {
            if(!visitado[v] && clave[v] < min) {
                min = clave[v];
                u = v;
            }
        }
        
        if(u == -1) break;
        visitado[u] = true;
        
        for(int v = 0; v < n; ++v) {
            float peso = distancias[u][v];
            if(!visitado[v] && peso < clave[v]) {
                padre[v] = u;
                clave[v] = peso;
            }
        }
    }
    return padre;
}

std::vector<float> Grafo::dijkstra(int origen) {
    int n = cantidadNodos();
    std::vector<float> distancia(n, std::numeric_limits<float>::max());
    std::vector<bool> visitado(n, false);
    distancia[origen] = 0;
    
    for(int i = 0; i < n-1; ++i) {
        float min = std::numeric_limits<float>::max();
        int u = -1;
        
        for(int v = 0; v < n; ++v) {
            if(!visitado[v] && distancia[v] < min) {
                min = distancia[v];
                u = v;
            }
        }
        
        if(u == -1) break;
        visitado[u] = true;
        
        for(int v = 0; v < n; ++v) {
            float peso = distancias[u][v];
            if(!visitado[v] && distancia[u] + peso < distancia[v]) {
                distancia[v] = distancia[u] + peso;
            }
        }
    }
    return distancia;
}

std::vector<int> Grafo::recorridoDFSporMST() {
    std::vector<int> mst = prim(0);
    int n = cantidadNodos();
    
    std::vector<std::vector<int>> adyacencia(n);
    for(int i = 0; i < n; ++i) {
        if(mst[i] != -1) {
            adyacencia[i].push_back(mst[i]);
            adyacencia[mst[i]].push_back(i);
        }
    }
    
    int inicio = 0;
    float minDist = std::numeric_limits<float>::max();
    Nodo origen(0, 0);
    
    for(int i = 0; i < n; ++i) {
        float d = calcularDistancia(nodos[i], origen);
        if(d < minDist) {
            minDist = d;
            inicio = i;
        }
    }
    
    std::vector<bool> visitado(n, false);
    std::vector<int> recorrido;
    
    std::function<void(int)> dfs = [&](int u) {
        visitado[u] = true;
        recorrido.push_back(u);
        
        std::sort(adyacencia[u].begin(), adyacencia[u].end(), 
            [&](int a, int b) {
                return obtenerDistancia(u, a) < obtenerDistancia(u, b);
            });
        
        for(int v : adyacencia[u]) {
            if(!visitado[v]) dfs(v);
        }
    };
    
    dfs(inicio);
    return recorrido;
}

#endif