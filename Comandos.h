#ifndef COMANDOS_H
#define COMANDOS_H
#include <string>
#include <vector>
using namespace std;

//Alejo
struct DatosComando { //Para la informacion que tendra cada comando
    string nombre; //nombre del comando
    //Saul
    string categoria; //categoria a la que pertenece el comando
    int minArgs; //cantidad minima de argumentos que recibe el comando
    int maxArgs; //cantidad maxima de argumentos que recibe el comando
    //Saul
    string descripcion; //informacion de ayuda que explica que hace el comando
    string uso; //forma correcta de escribir el comando
    string ejemplo; //ejemplo de como se utiliza el comando
};

//Buscar el comando en la tabla de comandos, si lo encuentra devuelve la posicion del comando en la tabla, si no lo encuentra devuelve -1
int buscarComando(string nombre);

//Isa agrego
//A partir de la posicion del comando en la tabla, valida si la cantidad de parametros que se le paso al comando es correcta, si es correcta devuelve true, si no es correcta devuelve false y muestra un mensaje de error
bool validarCantidadParametros(int posicion, int cantidad);

//Alejo
//Valida si el comando existe y si la cantidad de parametros que se le paso es correcta, si es correcta devuelve true, si no es correcta devuelve false y muestra un mensaje de error
bool validarComando(string nombre, int cantidadArgumentos);

//Isa
//Recibe una linea de texto y la separa en palabras, devolviendo un vector con cada palabra
vector<string> separarEntrada(string linea);

//Saul
//Muestra todos los comandos disponibles organizados por categorias
void mostrarAyudaGeneral();

//Saul
//Muestra la explicacion y el uso correcto de un comando
void mostrarAyudaComando(string nombre);

#endif