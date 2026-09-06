#ifndef CONTINENTE_H
#define CONTINENTE_H
#include <string>
#include <vector>
using namespace std;
class Tablero;
class Continente {
private:
    string codigo;
    string nombre;
    int bonificacion;
    vector<string> codigosTerritorios;
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
    void agregarTerritorio(string codigoTerritorio);
    const vector<string>& obtenerTerritorios() const;
    bool estaControladoPor(
        string colorJugador,
        const Tablero& tablero
    ) const;
};
#endif