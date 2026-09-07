#include "Territorio.h"

// Constructor de Territorio
Territorio::Territorio()
    : codigo(""),
      nombre(""),
      codigoContinente(""),
      colorPropietario(""),
      unidades(0)
{
}

// Constructor con datos iniciales del territorio.
Territorio::Territorio(
    string nuevoCodigo,
    string nuevoNombre,
    string nuevoContinente
) : codigo(nuevoCodigo),
    nombre(nuevoNombre),
    codigoContinente(nuevoContinente),
    colorPropietario(""),
    unidades(0)
{
}

string Territorio::obtenerCodigo() const {
    return codigo;
}

string Territorio::obtenerNombre() const {
    return nombre;
}

string Territorio::obtenerCodigoContinente() const {
    return codigoContinente;
}

string Territorio::obtenerColorPropietario() const {
    return colorPropietario;
}

int Territorio::obtenerUnidades() const {
    return unidades;
}

// Asigna un nuevo propietario al territorio.
void Territorio::asignarPropietario(string nuevoColor) {
    colorPropietario = nuevoColor;
}

// Establece la cantidad de unidades del territorio.
void Territorio::asignarUnidades(int nuevaCantidad) {
    unidades = nuevaCantidad;
}

// Agrega vecino al territorio.
void Territorio::agregarVecino(string codigoVecino) {
    codigosVecinos.push_back(codigoVecino);
}

bool Territorio::esVecino(string codigoTerritorio) const{
    vector<string>::const_iterator buscar = codigosVecinos.begin();
    for(; buscar != codigosVecinos.end(); ++buscar){
        if(*buscar == codigoTerritorio){
            return true;
        }
    }
    return false;
}

// Retorna la lista completa de vecinos, sin permitir modificarla.
const vector<string>& Territorio::obtenerVecinos() const {
    return codigosVecinos;
}   

bool Territorio::agregarUnidades(int cantidad){


    if(cantidad <=0){
        return false;
    }
    unidades+=cantidad;
    return true;
}

bool Territorio::retirarUnidades(int cantidad, int minimoRestante){
    if(unidades - cantidad < minimoRestante){
        return false;
    }
    unidades-=cantidad;
    return true;
}

bool Territorio::cambiarPropietario(string color, int cantidadAnadir){
    
    if(unidades != 0){
        return false;
    }

    colorPropietario=color;
    
    if(cantidadAnadir <= 0 ){
        return false;
    }

    agregarUnidades(cantidadAnadir);
    return true;
}