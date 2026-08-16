#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct DatosComando { //Para la informacion de tendra cada comando  
    string nombre; //nombre del comando 
    int minArgs; //cantidad minima de argumentos que recibe el comando
    int maxArgs; //cantidad maxima de argumentos que recibe el comando
    string ayuda; //informacion de ayuda del comando o sea el que hace el comando y como se usa
};

// Vector de tipo DatosComando que contiene la informacion de todos los comandos disponibles en el juego, se hace const para que la tabla no pueda ser modificada en tiempo de ejecucion.
const vector<DatosComando> TABLA_COMANDOS = { 

    {"inicializar", 1, 1,
     "Inicializa el juego desde un archivo. "
     "Uso: inicializar [archivo_inicio]"},

    {"obtener_unidades", 1, 1,
     "Realiza la obtencion y ubicacion de nuevas unidades para un jugador. "
     "Uso: obtener_unidades [nombre_jugador]"},

    {"atacar", 1, 1,
     "Realiza la fase de ataque del jugador. "
     "Uso: atacar [nombre_jugador]"},

    {"fortificar", 1, 1,
     "Realiza la fase de fortificacion del jugador. "
     "Uso: fortificar [nombre_jugador]"},

    {"estado_juego", 0, 0,
     "Muestra un resumen del estado actual del juego. "
     "Uso: estado_juego"},

    {"salir", 0, 0,
     "Termina la ejecucion de la aplicacion. "
     "Uso: salir"},

    {"guardar", 1, 1,
     "Guarda el estado actual del juego en un archivo de texto. "
     "Uso: guardar [nombre_archivo]"},

    {"guardar_comprimido", 1, 1,
     "Guarda el estado actual del juego en un archivo binario comprimido. "
     "Uso: guardar_comprimido [nombre_archivo]"},

    {"costo_conquista", 2, 2,
     "Calcula el costo para conquistar un territorio. "
     "Uso: costo_conquista [nombre_jugador] [territorio]"},

    {"conquista_mas_barata", 1, 1,
     "Calcula la conquista con el menor costo. "
     "Uso: conquista_mas_barata [nombre_jugador]"},

    {"ayuda", 0, 1,
     "Muestra los comandos disponibles o la ayuda de un comando. "
     "Uso: ayuda o ayuda [comando]"}
};


//se crea una funcion que reciba un string y busque en la tabla de comandos si existe un comando con ese nombre, si lo encuentra devuelve la posicion del comando en la tabla, si no lo encuentra devuelve -1
int buscarComando(string nombre) { 

    for (int i = 0; i < TABLA_COMANDOS.size(); i++) { //TABLA_COMANDOS.size() da la cantidad de elementos que hay dentro del vector TABLA_COMANDOS para hacer un for que diga desde 0 hasta la cantidad de elementos que hay en la tabla de comandos

        //Entra a la posición i de la tabla y toma el nombre del comando
        if (TABLA_COMANDOS[i].nombre == nombre) {
            return i;
        }
    }

    return -1;
}

bool validarCantidadParametros(int posicion, int cantidad) {

    if (cantidad < TABLA_COMANDOS[posicion].minArgs || cantidad > TABLA_COMANDOS[posicion].maxArgs) {

        cout << "(Parametros incorrectos) El comando '" << TABLA_COMANDOS[posicion].nombre << "' no recibe esa cantidad de parametros." << endl;

        return false;
    }

    return true;
}

bool validarComando(string nombre, int cantidadArgumentos) {

    int posicion = buscarComando(nombre);

    if (posicion == -1) {

        cout << "(Comando invalido) El comando '" << nombre<< "' no existe." << endl;

        return false;
    }

    if (!validarCantidadParametros(posicion, cantidadArgumentos)) {
        return false;
    }

    return true;
}