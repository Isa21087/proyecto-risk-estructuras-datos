
#include "Grafo.h"

Grafo::Grafo() {
}

bool Grafo::agregarTerritorio(string codigo) {
    if (codigo.empty() || buscarTerritorio(codigo) != -1) {
        return false;
    }

    territorios.push_back(codigo);
    int cantidad = territorios.size();

    // ampliamos las filas que ya existian para que tengan una columna nueva
    for (int i = 0; i < cantidad - 1; i++) {
        matrizCostos[i].push_back(-1);
    }

    // la fila nueva comienza sin conexiones y con cero en su diagonal
    vector<int> nuevaFila(cantidad, -1);
    nuevaFila[cantidad - 1] = 0;
    matrizCostos.push_back(nuevaFila);

    return true;
}

int Grafo::cantidadTerritorios() const {
    return territorios.size();
}

int Grafo::buscarTerritorio(string codigo) const {
    for (int i = 0; i < cantidadTerritorios(); i++) {
        if (territorios[i] == codigo) {
            return i;
        }
    }

    return -1;
}

string Grafo::obtenerTerritorio(int posicion) const {
    if (posicion < 0 || posicion >= cantidadTerritorios()) {
        return "";
    }

    return territorios[posicion];
}

void Grafo::establecerCosto(int origen, int destino, int costo) {
    int cantidad = cantidadTerritorios();

    if (origen < 0 || origen >= cantidad ||
        destino < 0 || destino >= cantidad) {
        return;
    }

    if (origen == destino || costo < 0) {
        return;
    }

    // cada sentido se actualiza aparte porque ingresar a otro territorio puede costar diferente
    matrizCostos[origen][destino] = costo;
}

int Grafo::obtenerCosto(int origen, int destino) const {
    int cantidad = cantidadTerritorios();

    if (origen < 0 || origen >= cantidad ||
        destino < 0 || destino >= cantidad) {
        return -1;
    }

    return matrizCostos[origen][destino];
}

bool Grafo::sonAdyacentes(int origen, int destino) const {
    if (origen == destino) {
        return false;
    }

    return obtenerCosto(origen, destino) >= 0;
}
