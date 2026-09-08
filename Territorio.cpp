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

//Busca el codigo del vecino en el vecto de codigoVecino
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


    if(cantidad <=0){   //Se necesita que la cantidad que se vaya a agregar sea mayor a 0
        return false;
    }
    unidades+=cantidad; 
    return true;
}

bool Territorio::retirarUnidades(int cantidad, int minimoRestante){

    if(cantidad <= 0 ){ //Se necesita que la cantidad que se vaya a retirar sea mayor a 0
        return false;
    }
    //se tiene un minimo el cual se debe cumplir para que no hayan errores
    if(unidades - cantidad < minimoRestante){   //deben haber mas unidades que la cantidad minima puesta
        return false;                           
    }
    unidades-=cantidad;
    return true;
}

bool Territorio::cambiarPropietario(string color, int cantidadAnadir){
    //se verifica que ya no hayan unidades en el territorio
    if(unidades != 0){
        return false;
    }

    //Se puede añadir una unidad en este territorio
    if(cantidadAnadir < 0 ){
        return false;
    }

    //Se añade la unidad y se corona este territorio como conquistado
    colorPropietario=color;

    agregarUnidades(cantidadAnadir);
    return true;
}