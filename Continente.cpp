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

void Continente::agregarTerritorio(const Territorio& territorio){
    territorios.push_back(territorio);
}

const vector<Territorio>& Continente::obtenerTerritorios() const{
    return territorios;
}

bool Continente::estaControladoPor(string colorJugador) const{
    
    if(territorios.empty()){
        return false;
    }  

    vector<Territorio>::const_iterator buscarPropietario = territorios.begin();
    for(; buscarPropietario != territorios.end() ; ++buscarPropietario){
        if(buscarPropietario->obtenerColorPropietario() != colorJugador){// Verifica si en este continente hay mas de un jugador
            return false;
        }
    }
    return true;
}

    Territorio* Continente::buscarTerritorio(string codigo){
        vector<Territorio>::iterator buscar = territorios.begin();
        for(; buscar != territorios.end(); ++buscar){
            if(buscar->obtenerCodigo() == codigo){
                return &(*buscar);
            }
        }
        return NULL;
    }
    const Territorio* Continente::buscarTerritorio(string codigo) const{
        vector<Territorio>::const_iterator buscar = territorios.begin();
        for(; buscar != territorios.end(); ++buscar){
            if(buscar ->obtenerCodigo() == codigo){
                return &(*buscar);
            }
        }
        return NULL;
    }
