#include "Continente.h"

Continente::Continente()
    : codigo(""),
      nombre(""),
      bonificacion(0)
{
}

Continente::Continente(
        string nuevoCodigo,
        string nuevoNombre,
        int nuevaBonificacion
)
    : codigo(nuevoCodigo),
      nombre(nuevoNombre),
      bonificacion(nuevaBonificacion)
{
}
string Continente::obtenerCodigo() const{
    return codigo;
}
string Continente::obtenerNombre() const{
    return nombre;
}
int Continente::obtenerBonificacion() const{
    return bonificacion;
}
void Continente::agregarTerritorio(Territorio territorio){
    territorios.push_back(territorio);
}

const vector<Territorio>& Continente::obtenerTerritorios() const{
    return territorios;
}
bool Continente::estaControladoPor(string colorJugador, const Tablero& tablero) const{
    
}