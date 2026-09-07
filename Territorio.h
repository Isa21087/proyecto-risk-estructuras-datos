#ifndef TERRITORIO_H
#define TERRITORIO_H
#include <string>
#include <vector>
using namespace std;
class Territorio {
private:
    string codigo;
    string nombre;
    string codigoContinente;
    string colorPropietario;
    int unidades;
    vector<string> codigosVecinos;
public:
    Territorio();
    Territorio(
        string nuevoCodigo,
        string nuevoNombre,
        string nuevoContinente
    );
    string obtenerCodigo() const;
    string obtenerNombre() const;
    string obtenerCodigoContinente() const;
    string obtenerColorPropietario() const;
    int obtenerUnidades() const;
    void asignarPropietario(string nuevoColor);
    void asignarUnidades(int nuevaCantidad);
    bool agregarUnidades(int cantidad);
    bool retirarUnidades(int cantidad, int minimoRestante);
    void agregarVecino(string codigoVecino);
    bool esVecino(string codigoTerritorio) const;
    const vector<string>& obtenerVecinos() const;
    bool cambiarPropietario(string color, int cantidad);
};
#endif
