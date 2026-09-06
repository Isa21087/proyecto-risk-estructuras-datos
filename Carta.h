#ifndef CARTA_H
#define CARTA_H
#include <string>
#include "Tipos.h"
using namespace std;
class Carta {
private:
    TipoCarta tipo;
    string codigoTerritorio;
public:
    Carta();
    Carta(TipoCarta nuevoTipo, string nuevoCodigoTerritorio);
    TipoCarta obtenerTipo() const;
    string obtenerCodigoTerritorio() const;
    bool esComodin() const;
};
#endif
