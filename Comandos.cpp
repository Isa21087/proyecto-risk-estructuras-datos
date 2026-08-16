#include "Comandos.h"
#include <iostream>
using namespace std;

// Vector de tipo DatosComando que contiene la informacion de todos los comandos disponibles en el juego, se hace const para que la tabla no pueda ser modificada en tiempo de ejecucion.
//Alejo: nombres de los comandos y cantidades de parametros.
//Saul: categorias y explicaciones de los comandos.
const vector<DatosComando> TABLA_COMANDOS = {

    {"inicializar",
     "CONFIGURACION DEL JUEGO",
     1,
     1,
     "Inicializa el juego con la informacion contenida en el archivo indicado.",
     "inicializar [nombre_archivo]",
     "inicializar partida.txt"},

    {"obtener_unidades",
     "CONFIGURACION DEL JUEGO",
     1,
     1,
     "Informa cuantas unidades adicionales puede reclamar el jugador y permite indicar donde desea asignarlas.",
     "obtener_unidades [nombre_jugador]",
     "obtener_unidades Isabella"},

    {"atacar",
     "CONFIGURACION DEL JUEGO",
     1,
     1,
     "Permite seleccionar desde que territorio se quiere atacar, hacia que territorio se realizara el ataque e informa las unidades que se ganan o pierden.",
     "atacar [nombre_jugador]",
     "atacar Oreo"},

    {"fortificar",
     "CONFIGURACION DEL JUEGO",
     1,
     1,
     "Permite seleccionar los territorios vecinos para la fortificacion y la cantidad de unidades que se trasladaran.",
     "fortificar [nombre_jugador]",
     "fortificar Isabella"},

    {"estado_juego",
     "CONFIGURACION DEL JUEGO",
     0,
     0,
     "Presenta un resumen de la situacion actual del juego.",
     "estado_juego",
     "estado_juego"},

    {"guardar",
     "ALMACENAMIENTO",
     1,
     1,
     "Guarda el estado actual del juego en un archivo de texto plano.",
     "guardar [nombre_archivo]",
     "guardar partida.txt"},

    {"guardar_comprimido",
     "ALMACENAMIENTO",
     1,
     1,
     "Guarda el estado actual del juego en un archivo binario con la informacion comprimida.",
     "guardar_comprimido [nombre_archivo]",
     "guardar_comprimido partida"},

    {"costo_conquista",
     "ESTRATEGIAS DE JUEGO",
     2,
     2,
     "Calcula el costo y la secuencia de territorios necesarios para conquistar el territorio indicado.",
     "costo_conquista [nombre_jugador] [territorio]",
     "costo_conquista Isabella Brasil"},

    {"conquista_mas_barata",
     "ESTRATEGIAS DE JUEGO",
     1,
     1,
     "Calcula cual conquista puede implicar el menor numero de unidades perdidas.",
     "conquista_mas_barata [nombre_jugador]",
     "conquista_mas_barata Isabella"},

    {"ayuda",
     "GENERAL",
     0,
     1,
     "Muestra los comandos disponibles o la ayuda de un comando especifico.",
     "ayuda o ayuda [nombre_comando]",
     "ayuda atacar"},

    {"salir",
     "GENERAL",
     0,
     0,
     "Termina la ejecucion de la aplicacion.",
     "salir",
     "salir"}
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

//Isa agrego
//A partir de la posicion del comando en la tabla, valida si la cantidad de parametros que se le paso al comando es correcta, si es correcta devuelve true, si no es correcta devuelve false y muestra un mensaje de error
bool validarCantidadParametros(int posicion, int cantidad) {

    //Guarda la cantidad minima de parametros que recibe el comando encontrado
    int minimo = TABLA_COMANDOS[posicion].minArgs;

    //Guarda la cantidad maxima de parametros que recibe el comando encontrado
    int maximo = TABLA_COMANDOS[posicion].maxArgs;

    //Guarda el nombre del comando para poder utilizarlo en los mensajes
    string nombre = TABLA_COMANDOS[posicion].nombre;

    //Si la cantidad recibida es menor que la minima significa que faltan parametros
    if (cantidad < minimo) {

        //Calcula cuantos parametros le faltaron al usuario
        int faltan = minimo - cantidad;

        //Si falta solamente uno muestra parametro en singular
        if (faltan == 1) {
            cout << "(Parametros incorrectos) Falta 1 parametro para ejecutar '" << nombre << "'." << endl;
        }

        //Si falta mas de uno muestra parametros en plural
        else {
            cout << "(Parametros incorrectos) Faltan " << faltan << " parametros para ejecutar '" << nombre << "'." << endl;
        }

        //Muestra la forma correcta de escribir el comando
        cout << endl;
        cout << "Uso correcto:" << endl;
        cout << "  " << TABLA_COMANDOS[posicion].uso << endl;

        //Muestra un ejemplo para que el usuario pueda corregir el error
        cout << endl;
        cout << "Ejemplo:" << endl;
        cout << "  " << TABLA_COMANDOS[posicion].ejemplo << endl;

        //Aclara que por el error no se ejecuto ninguna accion
        cout << endl;
        cout << "No se ejecuto ninguna accion. Intente nuevamente." << endl;

        //Devuelve false porque la cantidad de parametros no fue correcta
        return false;
    }

    //Si la cantidad recibida es mayor que la maxima significa que sobran parametros
    else if (cantidad > maximo) {

        //Calcula cuantos parametros adicionales escribio el usuario
        int sobran = cantidad - maximo;

        //Si sobra solamente uno muestra parametro en singular
        if (sobran == 1) {
            cout << "(Parametros incorrectos) Se escribio 1 parametro adicional que el comando '" << nombre << "' no necesita." << endl;
        }

        //Si sobra mas de uno muestra parametros en plural
        else {
            cout << "(Parametros incorrectos) Se escribieron " << sobran << " parametros adicionales que el comando '" << nombre << "' no necesita." << endl;
        }

        //Muestra la forma correcta de escribir el comando
        cout << endl;
        cout << "Uso correcto:" << endl;
        cout << "  " << TABLA_COMANDOS[posicion].uso << endl;

        //Muestra un ejemplo para que el usuario pueda corregir el error
        cout << endl;
        cout << "Ejemplo:" << endl;
        cout << "  " << TABLA_COMANDOS[posicion].ejemplo << endl;
        cout << endl;
        cout << "No se ejecuto ninguna accion. Intente nuevamente." << endl;

        //Devuelve false porque la cantidad de parametros no fue correcta
        return false;
    }

    //Si no faltan ni sobran parametros significa que la cantidad es correcta
    return true;
}

//Alejo
bool validarComando(string nombre, int cantidadArgumentos) {

    int posicion = buscarComando(nombre);

    if (posicion == -1) {

    cout << "(Comando invalido) El comando '"
         << nombre
         << "' no existe."
         << endl;

    cout << "Escriba 'ayuda' para consultar los comandos disponibles."
         << endl;

    return false;
}

    if (!validarCantidadParametros(posicion, cantidadArgumentos)) {
        return false;
    }

    return true;
}
// Isa
// Recibe una linea de texto y la separa en palabras,
// devolviendo un vector con cada palabra.
vector<string> separarEntrada(string linea) {

    // Crea el vector donde se guardaran las palabras encontradas.
    vector<string> palabras;

    // La palabra empieza vacia y se va llenando con los
    // caracteres encontrados en la linea de texto.
    string palabra = "";

    // Guarda la cantidad de caracteres que tiene la linea recibida.
    int cantidadCaracteres = linea.size();

    // Recorre la linea de texto caracter por caracter,
    // desde la posicion 0 hasta llegar al final.
    for (int i = 0; i < cantidadCaracteres; i++) {

        // Si el caracter actual es un espacio, significa que una palabra pudo haber terminado. Si no es un espacio, entra al else y agrega el caracter a la palabra que se esta construyendo.
        if (linea[i] == ' ') {

            // Si palabra no esta vacia, significa que contiene una palabra construida y entonces se guarda en el vector palabras.
            // Si esta vacia, no se guarda nada. Esto evita guardar elementos
            // vacios cuando el usuario escribe varios espacios seguidos.
            if (palabra != "") {

                // Agrega la palabra encontrada al final del vector.
                palabras.push_back(palabra);

                // Vacia palabra para comenzar a construir la siguiente.
                palabra = "";
            }
        }
        else {

            // Agrega el caracter actual a palabra. Esto permite construirla
            // caracter por caracter hasta encontrar un espacio o llegar
            // al final de la linea.
            palabra = palabra + linea[i];
        }
    }

    // Si al terminar el recorrido quedo una palabra construida,
    // la guarda porque posiblemente no habia un espacio despues de ella.
    if (palabra != "") {
        palabras.push_back(palabra);
    }

    // Devuelve el vector con todas las palabras encontradas.
    return palabras;
}

//Saul
//Muestra todos los comandos disponibles organizados por categorias
void mostrarAyudaGeneral() {

    cout << endl;
    cout << "================ AYUDA DEL JUEGO ================" << endl;
    cout << endl;
    cout << "Los titulos de las secciones no son comandos." << endl;

    //Guarda la categoria que se esta mostrando en el momento
    string categoriaActual = ""; //empieza vacia porque todavia no se ha mostrado ninguna categoria

    //Guarda la cantidad de comandos que tiene la tabla para poder recorrerla
    int cantidadComandos = TABLA_COMANDOS.size();

    //Recorre todos los comandos guardados en la tabla
    for (int i = 0; i < cantidadComandos; i++) {

        //Compara la categoria del comando actual con la ultima categoria mostrada
        //si son diferentes significa que se debe mostrar un nuevo titulo
        if (TABLA_COMANDOS[i].categoria != categoriaActual) {

            //Guarda la nueva categoria como la categoria que se esta mostrando
            categoriaActual = TABLA_COMANDOS[i].categoria;

            //Deja un espacio y muestra el nombre de la nueva categoria
            cout << endl;
            cout << categoriaActual << endl;
        }

        //Muestra la forma correcta de escribir cada comando
        cout << "  " << TABLA_COMANDOS[i].uso << endl;
    }

    //Explica como pedir la ayuda especifica de un comando
    cout << endl;
    cout << "Para consultar la ayuda de un comando escriba:" << endl;
    cout << "  ayuda [nombre_comando]" << endl;

    //Muestra un ejemplo para que el usuario sepa que debe reemplazar
    cout << endl;
    cout << "Ejemplo:" << endl;
    cout << "  ayuda atacar" << endl;
    cout << endl;
    cout << "=================================================" << endl;
}

//Saul
//Muestra la explicacion y el uso correcto de un comando
void mostrarAyudaComando(string nombre) {

    //Busca el comando recibido y guarda la posicion que tiene dentro de la tabla
    int posicion = buscarComando(nombre);

    //Si buscarComando devuelve -1 significa que el comando no existe
    if (posicion == -1) {

        //Le informa al usuario que el comando solicitado no existe
        cout << "(Comando invalido) El comando '" << nombre << "' no existe." << endl;

        //Le indica al usuario como puede consultar los comandos que si existen
        cout << "Escriba 'ayuda' para consultar los comandos disponibles." << endl;

        //Aclara que el error no ocasiono que se ejecutara alguna accion
        cout << "No se ejecuto ninguna accion. Intente nuevamente." << endl;
    }
    else {

        //Si el comando existe muestra un titulo con su nombre
        cout << endl;
        cout << "================ COMANDO: " << TABLA_COMANDOS[posicion].nombre << " ================" << endl;
        cout << endl;

        //Muestra la descripcion que explica para que sirve el comando
        cout << "Que hace:" << endl;
        cout << "  " << TABLA_COMANDOS[posicion].descripcion << endl;
        cout << endl;

        //Muestra la forma correcta de escribir el comando
        cout << "Uso:" << endl;
        cout << "  " << TABLA_COMANDOS[posicion].uso << endl;
        cout << endl;

        //Muestra un ejemplo completo para orientar al usuario
        cout << "Ejemplo:" << endl;
        cout << "  " << TABLA_COMANDOS[posicion].ejemplo << endl;
        cout << endl;

        //Si la cantidad minima y maxima son iguales significa que
        //el comando siempre recibe una cantidad exacta de parametros
        if (TABLA_COMANDOS[posicion].minArgs == TABLA_COMANDOS[posicion].maxArgs) {

            //Si la cantidad es cero el comando no necesita parametros
            if (TABLA_COMANDOS[posicion].minArgs == 0) {
                cout << "Este comando no necesita parametros." << endl;
            }

            //Si la cantidad es uno se escribe parametro en singular
            else if (TABLA_COMANDOS[posicion].minArgs == 1) {
                cout << "Este comando necesita 1 parametro." << endl;
            }

            //Si necesita mas de uno se escribe parametros en plural
            else {
                cout << "Este comando necesita "
                     << TABLA_COMANDOS[posicion].minArgs
                     << " parametros."
                     << endl;
            }
        }
        else {

            cout << "Este comando puede utilizarse sin parametros o con 1 parametro." << endl;
        }

        cout << endl;
        cout << "=================================================" << endl;
    }
}