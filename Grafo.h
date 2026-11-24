
#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <vector>

using namespace std;

class Grafo {
private:
    vector<string> territorios;
    vector<vector<int>> matrizCostos;

public:
    Grafo();
    bool agregarTerritorio(string codigo);
    int cantidadTerritorios() const;
    int buscarTerritorio(string codigo) const;
    string obtenerTerritorio(int posicion) const;
    void establecerCosto(int origen, int destino, int costo);
    int obtenerCosto(int origen, int destino) const;
    bool sonAdyacentes(int origen, int destino) const;
};

#endif
