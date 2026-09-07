#include <iostream>
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

// Retorna la lista completa de vecinos, sin permitir modificarla.
const vector<string>& Territorio::obtenerVecinos() const {
    return codigosVecinos;
}

//Imprime toda la informacion del territorio
void Territorio::print() const{

cout<<"Este es el territorio " << nombre << endl;
cout<<"Con el codigo " << codigo << endl;
cout<<"En el continente " << codigoContinente << endl;

vector<string>::const_iterator vecinos = codigosVecinos.begin();
cout<<"Los vecinos de este territorio son: ";

for(; vecinos != codigosVecinos.end(); ++vecinos){
    if(vecinos == codigosVecinos.begin()){
        cout<<*vecinos;
    }
    cout<<", "<<*vecinos;
}
cout<<endl;

if(colorPropietario.empty()){
    cout<<"Actualmente no cuenta con un propietario"<<endl;
    return;
}
cout<<"Su actual propietario es " << colorPropietario << endl; 
cout<<"Y cuenta con "<<unidades<<" unidades en este territorio"<<endl;

}   

bool Territorio::agregarUnidades(int cantidad){

    if(unidades <=0){
        cout<<"No se pueden agregar unidades a este territorio"<<endl;
        return false;
    }
    unidades+=cantidad;
    cout<<"Se han añadido correctamente "<<cantidad<<" unidades al territorio"<<endl;
    return true;
}

bool Territorio::retirarUnidades(int cantidad, int minimoRestante){
    if(unidades - cantidad < minimoRestante){
        cout<<"En este territorio solo hay "<<unidades<<"unidad disponible"<<endl;
        cout<<"No se puede retirar la unidad de este territorio"<<endl;
        return false;
    }
    unidades-=cantidad;
    cout<<"Se han retirado correctamente "<<cantidad<<" unidades del este territorio"<<endl;
    cout<<"Quedan "<<unidades<<" unidades en este territorio"<<endl;
    return true;
}

bool Territorio::cambiarPropietario(string color, int cantidadAnadir){
    
    if(unidades != 0){
        cout<<"No es posible cambiar de propietario este territorio"<<endl;
        return false;
    }

    cout<<"El territorio ha sido conquistado por "<<color<<endl;;
    colorPropietario=color;
    
    if(cantidadAnadir <= 0 ){
        cout<<"Se necesita al menos una unidad en este nuevo territorio"<<endl;
        return false;
    }

    agregarUnidades(cantidadAnadir);
    return true;
}