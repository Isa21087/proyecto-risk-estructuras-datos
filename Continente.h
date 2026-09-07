#ifndef CONTINENTE_H
#define CONTINENTE_H
#include <string>
#include <vector>
#include "Territorio.h"
using namespace std;
class Tablero;
class Continente {
private:
    string codigo;
    string nombre;
    int bonificacion;
    vector<Territorio> territorios;
public:
    Continente();
    Continente(
        string nuevoCodigo,
        string nuevoNombre,
        int nuevaBonificacion
    );
    string obtenerCodigo() const;
    string obtenerNombre() const;
    int obtenerBonificacion() const;
    void agregarTerritorio(const Territorio& territorio);
    const vector<Territorio>& obtenerTerritorios() const;
    bool estaControladoPor(string colorJugador) const;
    const Territorio* buscarTerritorio(string codigo) const;
};
#endif