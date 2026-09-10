#include "Carta.h"
using namespace std;

// Crea una carta comodin sin territorio asociado.
Carta::Carta()
{
    tipo = CARTA_COMODIN;
    codigoTerritorio = "";
}

// Crea una carta con su tipo y territorio.
Carta::Carta(TipoCarta nuevoTipo, string nuevoCodigoTerritorio)
{
    tipo = nuevoTipo;
    codigoTerritorio = nuevoCodigoTerritorio;
}

// Retorna el tipo de la carta.
TipoCarta Carta::obtenerTipo() const
{
    return tipo;
}

// Retorna el codigo del territorio asociado.
string Carta::obtenerCodigoTerritorio() const
{
    return codigoTerritorio;
}

// Revisa si la carta es un comodin.
bool Carta::esComodin() const
{
    return tipo == CARTA_COMODIN;
}