#ifndef PERFORADORA_H
#define PERFORADORA_H

#include <vector>
#include <string>
#include "Nodo.h"
#include "Grafo.h"

class Perforadora {
public:
    void procesarCircuitosDesdeArchivo(const std::string& archivoEntrada);

private:
    std::vector<std::vector<Nodo>> leerCircuitos(const std::string& archivo);
    void guardarSalida(const std::string& archivo, const std::vector<int>& secuencia, const Grafo& grafo);
};

#include "Perforadora.hxx"

#endif
