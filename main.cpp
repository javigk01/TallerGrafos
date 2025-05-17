#include <iostream>
#include "Perforadora.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: Debe especificar el nombre del archivo de entrada.\n";
        std::cerr << "Uso: " << argv[0] << " archivo_entrada.txt\n";
        return 1;
    }

    std::string archivoEntrada = argv[1];
    Perforadora p;
    p.procesarCircuitosDesdeArchivo(archivoEntrada);

    return 0;
}
