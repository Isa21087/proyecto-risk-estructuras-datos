#ifndef TABLERO_H
#define TABLERO_H
#include <string>
#include <vector>
#include "Territorio.h"
#include "Continente.h"
using namespace std;
class Tablero {
private:
    vector<Continente> continentes;
public:
    Tablero();
    void inicializarEstructura();
    Territorio* buscarTerritorio(string codigo);
    const Territorio* buscarTerritorio(string codigo) const;
    bool existeTerritorio(string codigo) const;
    bool configurarTerritorio(string codigo, string colorPropietario, int unidades);
    bool sonVecinos(string codigoOrigen, string codigoDestino) const;
    int contarTerritorios(string colorJugador) const;
    int sumarUnidades(string colorJugador) const;
    int calcularBonificacionContinentes(string colorJugador) const;
    bool agregarUnidades(string codigoTerritorio, string colorJugador, int cantidad);
    bool trasladarUnidades(string codigoOrigen, string codigoDestino, string colorJugador, int cantidad, int minimoRestante);
    bool cambiarPropietario(string codigoTerritorio, string nuevoColor, int cantidad);
    bool todosLosTerritoriosConfigurados() const;
    void mostrarTablero() const;
};
#endif

