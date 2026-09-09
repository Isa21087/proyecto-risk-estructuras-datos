#include "Partida.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
// Inicializa la partida sin datos cargados.

Partida::Partida(){

    inicializada = false;
    terminada = false;
    ganador = "";

}

// Inicializa la partida desde un archivo.
EstadoComando Partida::inicializar(string nombreArchivo){

    // No permite cargar otra partida si ya hay una inicializada.
    if(inicializada){
        return JUEGO_EN_CURSO;
    }

    ifstream archivo(nombreArchivo);

    if(!archivo.is_open()){
        return ARCHIVO_ERRONEO;
    }

    string linea;

    if(!getline(archivo, linea)){
        archivo.close();
        return ARCHIVO_VACIO;
    }

    // Salta las lineas vacias al inicio.
    while(linea.empty() && getline(archivo, linea)){
    }

    if(linea.empty()){
        archivo.close();
        return ARCHIVO_VACIO;
    }

    // Lee la cantidad de jugadores.
    istringstream lineaJugadores(linea);
    int cantidadJugadores;
    string datoExtra;

    if(!(lineaJugadores >> cantidadJugadores)){
        archivo.close();
        return ARCHIVO_SIN_FORMATO;
    }

    // La linea solo debe tener la cantidad de jugadores.
    if(lineaJugadores >> datoExtra){
        archivo.close();
        return ARCHIVO_SIN_FORMATO;
    }

    if(cantidadJugadores < 3 || cantidadJugadores > 6){
        archivo.close();
        return ARCHIVO_SIN_FORMATO;
    }

    vector<Jugador> jugadoresLeidos;

    // Lee el nombre y el color de cada jugador.
    for(int i = 0; i < cantidadJugadores; i++){

        if(!getline(archivo, linea)){
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        while(linea.empty() && getline(archivo, linea)){
        }

        if(linea.empty()){
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        istringstream lineaJugador(linea);
        string nombre;
        string color;

        if(!(lineaJugador >> nombre >> color)){
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        if(lineaJugador >> datoExtra){
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        // El nombre puede tener hasta 8 caracteres.
        if(nombre.length() > 8){
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        // Revisa que el color sea uno de los permitidos.
        if(color != "verde" &&
           color != "azul" &&
           color != "rojo" &&
           color != "amarillo" &&
           color != "negro" &&
           color != "gris"){

            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        // No permite nombres ni colores repetidos.
        for(int j = 0; j < jugadoresLeidos.size(); j++){

            if(jugadoresLeidos[j].obtenerNombre() == nombre ||
               jugadoresLeidos[j].obtenerColor() == color){

                archivo.close();
                return ARCHIVO_SIN_FORMATO;
            }
        }

        jugadoresLeidos.push_back(Jugador(nombre, color));
    }

    // Prepara el tablero para cargar los territorios.
    Tablero tableroLeido;
    tableroLeido.inicializarEstructura();

    vector<int> unidadesJugadores;

    for(int i = 0; i < cantidadJugadores; i++){
        unidadesJugadores.push_back(0);
    }

    vector<string> territoriosLeidos;

    // Lee los 42 territorios.
    for(int i = 0; i < 42; i++){

        if(!getline(archivo, linea)){
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        while(linea.empty() && getline(archivo, linea)){
        }

        if(linea.empty()){
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        istringstream lineaTerritorio(linea);
        string codigo;
        string color;
        int unidades;

        if(!(lineaTerritorio >> codigo >> color >> unidades)){
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        if(lineaTerritorio >> datoExtra){
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        // Revisa que el territorio exista.
        if(!tableroLeido.existeTerritorio(codigo)){
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        // Revisa que el territorio no se haya leido antes.
        bool repetido = false;

        for(int j = 0; j < territoriosLeidos.size(); j++){

            if(territoriosLeidos[j] == codigo){
                repetido = true;
            }
        }

        if(repetido){
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        territoriosLeidos.push_back(codigo);

        // Cada territorio debe tener al menos una unidad.
        if(unidades <= 0){
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        // Busca el jugador que tiene ese color.
        int posicionJugador = -1;

        for(int j = 0; j < jugadoresLeidos.size(); j++){

            if(jugadoresLeidos[j].obtenerColor() == color){
                posicionJugador = j;
            }
        }

        if(posicionJugador == -1){
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        // Asigna el propietario y las unidades.
        if(!tableroLeido.configurarTerritorio(codigo, color, unidades)){
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        // Acumula las unidades del jugador.
        unidadesJugadores[posicionJugador] += unidades;
    }

    // No permite mas datos despues de los 42 territorios.
    while(getline(archivo, linea)){

        istringstream lineaRestante(linea);

        if(lineaRestante >> datoExtra){
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }
    }

    // Define las unidades iniciales por jugador.
    int unidadesIniciales = 0;

    if(cantidadJugadores == 3){
        unidadesIniciales = 35;
    }
    else if(cantidadJugadores == 4){
        unidadesIniciales = 30;
    }
    else if(cantidadJugadores == 5){
        unidadesIniciales = 25;
    }
    else if(cantidadJugadores == 6){
        unidadesIniciales = 20;
    }

    // Revisa el total de unidades de cada jugador.
    for(int i = 0; i < cantidadJugadores; i++){

        if(unidadesJugadores[i] != unidadesIniciales){
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }
    }

    // Revisa que todo el tablero este configurado.
    if(!tableroLeido.todosLosTerritoriosConfigurados()){
        archivo.close();
        return ARCHIVO_SIN_FORMATO;
    }

    // Guarda los datos cuando todo el archivo es valido.
    jugadores = jugadoresLeidos;
    tablero = tableroLeido;

        // El primer jugador del archivo empieza el turno.
    turno.iniciar(0);

    inicializada = true;
    terminada = false;
    ganador = "";

    archivo.close();

    return COMANDO_CORRECTO;
}
// Revisa si se puede consultar la partida.
EstadoComando Partida::validarEstadoJuego() const{

    if(!inicializada){
        return JUEGO_NO_INICIALIZADO;
    }

    if(terminada){
        return JUEGO_TERMINADO;
    }

    return COMANDO_CORRECTO;

}

// Muestra los jugadores, el turno actual y el tablero.
void Partida::mostrarEstadoJuego() const{

    if(validarEstadoJuego() != COMANDO_CORRECTO){
        return;
    }

    cout << "========== ESTADO DEL JUEGO ==========" << endl;
    cout << "Cantidad de jugadores: " << jugadores.size() << endl;

    for(int i = 0; i < jugadores.size(); i++){

        cout << "Jugador: " << jugadores[i].obtenerNombre()
             << " | Color: " << jugadores[i].obtenerColor() << endl;

    }

    int posicionActual = turno.obtenerPosicionJugadorActual();

    cout << "Turno actual: "
         << jugadores[posicionActual].obtenerNombre() << endl;

    tablero.mostrarTablero();

}
// Busca al jugador por su nombre.
int Partida::buscarPosicionJugador(string nombreJugador) const{

    for(int i = 0; i < jugadores.size(); i++){

        if(jugadores[i].obtenerNombre() == nombreJugador){
            return i;
        }

    }

    return -1;

}

// Revisa el turno y permite repartir las unidades nuevas.
EstadoComando Partida::obtenerUnidades(string nombreJugador){

    EstadoComando estado = validarEstadoJuego();

    if(estado != COMANDO_CORRECTO){
        return estado;
    }

    int posicion = buscarPosicionJugador(nombreJugador);

    if(posicion == -1){
        return JUGADOR_NO_VALIDO;
    }

    if(posicion != turno.obtenerPosicionJugadorActual()){
        return JUGADOR_FUERA_DE_TURNO;
    }

    if(turno.obtenerEtapaActual() != ETAPA_OBTENER_UNIDADES){
        return JUGADOR_YA_OBTUVO_UNIDADES;
    }

    // El canje de cartas queda pendiente.
    int bonificacionCartas = 0;

    if(!turno.ejecutarObtencionUnidades(jugadores[posicion], tablero, bonificacionCartas)){
        return ENTRADA_CERRADA;
    }

    return COMANDO_CORRECTO;

}
// Revisa si un jugador conquisto todo el tablero.
bool Partida::comprobarGanador(){

    if(!inicializada){
        return false;
    }

    for(int i = 0; i < jugadores.size(); i++){

        if(tablero.contarTerritorios(jugadores[i].obtenerColor()) == 42){

            terminada = true;
            ganador = jugadores[i].obtenerNombre();

            return true;

        }

    }

    return false;

}

// Controla la etapa de ataque del jugador.
EstadoComando Partida::atacar(string nombreJugador){

    EstadoComando estado = validarEstadoJuego();

    if(estado != COMANDO_CORRECTO){
        return estado;
    }

    int posicion = buscarPosicionJugador(nombreJugador);

    if(posicion == -1){
        return JUGADOR_NO_VALIDO;
    }

    if(posicion != turno.obtenerPosicionJugadorActual()){
        return JUGADOR_FUERA_DE_TURNO;
    }

    if(turno.obtenerEtapaActual() == ETAPA_OBTENER_UNIDADES){
        return JUGADOR_NO_HA_UBICADO_UNIDADES;
    }

    if(turno.obtenerEtapaActual() == ETAPA_FORTIFICAR){
        return JUGADOR_YA_TERMINO_ATAQUE;
    }

    bool continuar = true;

    while(continuar){

        cout << "Desea realizar un ataque? (s/n): ";

        string respuesta;

        if(!getline(cin, respuesta)){
            return ENTRADA_CERRADA;
        }

        if(respuesta == "n" || respuesta == "N"){
            continuar = false;
        }
        else if(respuesta == "s" || respuesta == "S"){

            ResultadoAtaque resultado = ataque.ejecutar(jugadores[posicion], tablero);

            // Comprueba la victoria despues de una conquista.
            if(resultado.conquistoTerritorio){

                if(comprobarGanador()){
                    cout << "El ganador es " << ganador << "." << endl;
                    return COMANDO_CORRECTO;
                }

            }

            if(!cin){
                return ENTRADA_CERRADA;
            }

        }
        else{
            cout << "Escriba s para atacar o n para terminar la etapa." << endl;
        }

    }

    turno.registrarAtaqueTerminado();

    return COMANDO_CORRECTO;

}
// Permite fortificar y termina el turno del jugador.
EstadoComando Partida::fortificar(string nombreJugador){

    EstadoComando estado = validarEstadoJuego();

    if(estado != COMANDO_CORRECTO){
        return estado;
    }

    int posicion = buscarPosicionJugador(nombreJugador);

    if(posicion == -1){
        return JUGADOR_NO_VALIDO;
    }

    if(posicion != turno.obtenerPosicionJugadorActual()){
        return JUGADOR_FUERA_DE_TURNO;
    }

    if(turno.obtenerEtapaActual() != ETAPA_FORTIFICAR){
        return JUGADOR_NO_HA_ATACADO;
    }

    if(!turno.ejecutarFortificacion(jugadores[posicion], tablero)){
        return ENTRADA_CERRADA;
    }

    // Avanza hasta encontrar un jugador que conserve territorios.
    do{
        turno.finalizarTurno(jugadores.size());
    }while(tablero.contarTerritorios(
        jugadores[turno.obtenerPosicionJugadorActual()].obtenerColor()) == 0);

    return COMANDO_CORRECTO;

}