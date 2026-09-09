#include "Turno.h"
#include "Jugador.h"
#include "Tablero.h"
#include <iostream>
#include <sstream>
using namespace std;

// Inicializa el turno empezando desde el primer jugador
// y en la etapa inicial de obtener unidades.
Turno::Turno()
{
    posicionJugadorActual = 0;
    etapaActual = ETAPA_OBTENER_UNIDADES;
}

// Inicia el turno desde la posicion indicada.
void Turno::iniciar(int primeraPosicion)
{
    posicionJugadorActual = primeraPosicion;
    etapaActual = ETAPA_OBTENER_UNIDADES;
}
// Retorna la posicion del jugador que tiene el turno.
int Turno::obtenerPosicionJugadorActual() const
{
    return posicionJugadorActual;
}
// Calcula las unidades que puede reclamar el jugador.
int Turno::calcularNuevasUnidades(const Jugador& jugador, const Tablero& tablero, int bonificacionCartas) const
{
    string color = jugador.obtenerColor();

    int cantidadTerritorios = tablero.contarTerritorios(color);

    // La division entera toma solo las unidades completas.
    int unidadesTerritorios = cantidadTerritorios / 3;

    int unidadesContinentes = tablero.calcularBonificacionContinentes(color);

    return unidadesTerritorios + unidadesContinentes + bonificacionCartas;
}
// Permite repartir las unidades nuevas en los territorios del jugador.
bool Turno::ejecutarObtencionUnidades(Jugador& jugador, Tablero& tablero, int bonificacionCartas)
{
    if(etapaActual != ETAPA_OBTENER_UNIDADES){
        return false;
    }

    int unidadesPendientes = calcularNuevasUnidades(jugador, tablero, bonificacionCartas);

    // Guarda los cambios cuando se termine de repartir.
    Tablero tableroTemporal = tablero;

    cout << "Unidades disponibles: " << unidadesPendientes << endl;

    while(unidadesPendientes > 0){

        cout << "Escriba el codigo del territorio y la cantidad de unidades: ";

        string linea;

        if(!getline(cin, linea)){
            return false;
        }

        istringstream entrada(linea);
        string codigo;
        int cantidad;
        string datoExtra;

        if(!(entrada >> codigo >> cantidad)){
            cout << "Debe escribir un codigo y una cantidad entera." << endl;
        }
        else if(entrada >> datoExtra){
            cout << "Solo debe escribir el codigo y la cantidad." << endl;
        }
        else if(cantidad <= 0){
            cout << "La cantidad debe ser mayor que cero." << endl;
        }
        else if(cantidad > unidadesPendientes){
            cout << "No tiene suficientes unidades disponibles." << endl;
        }
        else if(!tableroTemporal.existeTerritorio(codigo)){
            cout << "El territorio no existe." << endl;
        }
        else if(!tableroTemporal.agregarUnidades(codigo, jugador.obtenerColor(), cantidad)){
            cout << "No se pudieron agregar las unidades. Elija un territorio propio." << endl;
        }
        else{
            unidadesPendientes -= cantidad;

            cout << "Unidades restantes: " << unidadesPendientes << endl;
        }

    }

    tablero = tableroTemporal;
    etapaActual = ETAPA_ATACAR;

    return true;
}
// Retorna la etapa actual del turno.
EtapaTurno Turno::obtenerEtapaActual() const
{
    return etapaActual;
}
// Pasa a fortificar cuando termina la etapa de ataque.
void Turno::registrarAtaqueTerminado()
{
    if(etapaActual == ETAPA_ATACAR){
        etapaActual = ETAPA_FORTIFICAR;
    }
}
// Permite mover unidades entre dos territorios propios vecinos.
bool Turno::ejecutarFortificacion(Jugador& jugador, Tablero& tablero)
{
    if(etapaActual != ETAPA_FORTIFICAR){
        return false;
    }

    bool terminada = false;

    while(!terminada){

        cout << "Escriba origen, destino y cantidad, o n para no trasladar: ";

        string linea;

        if(!getline(cin, linea)){
            return false;
        }

        istringstream entrada(linea);
        string codigoOrigen;
        string codigoDestino;
        string datoExtra;
        int cantidad;

        if(!(entrada >> codigoOrigen)){
            cout << "Debe escribir los datos o n para terminar." << endl;
        }
        else if(codigoOrigen == "n" || codigoOrigen == "N"){

            if(entrada >> datoExtra){
                cout << "Escriba solo n para terminar sin trasladar." << endl;
            }
            else{
                terminada = true;
            }

        }
        else if(!(entrada >> codigoDestino >> cantidad)){
            cout << "Debe escribir origen, destino y una cantidad entera." << endl;
        }
        else if(entrada >> datoExtra){
            cout << "Solo debe escribir origen, destino y cantidad." << endl;
        }
        else if(codigoOrigen == codigoDestino){
            cout << "Debe escoger dos territorios diferentes." << endl;
        }
        else if(cantidad <= 0){
            cout << "La cantidad debe ser mayor que cero." << endl;
        }
        else if(!tablero.existeTerritorio(codigoOrigen) ||
                !tablero.existeTerritorio(codigoDestino)){
            cout << "Uno de los territorios no existe." << endl;
        }
        else if(!tablero.sonVecinos(codigoOrigen, codigoDestino)){
            cout << "Los territorios deben ser vecinos." << endl;
        }
        else{

            // Guarda el traslado solamente si se completa.
            Tablero tableroTemporal = tablero;
 
            if(!tableroTemporal.trasladarUnidades(
                codigoOrigen, codigoDestino, jugador.obtenerColor(), cantidad, 1)){

                cout << "No se pudo realizar el traslado." << endl;
                cout << "Ambos territorios deben ser propios y el origen debe conservar al menos una unidad." << endl;

            }
            else{

                tablero = tableroTemporal;
                terminada = true;

                cout << "Las unidades fueron trasladadas correctamente." << endl;

            }

        }

    }

    return true;
}
// Pasa al siguiente jugador y reinicia las etapas.
void Turno::finalizarTurno(int cantidadJugadores)
{
    if(cantidadJugadores <= 0){
        return;
    }

    posicionJugadorActual++;

    // Despues del ultimo jugador vuelve al primero.
    if(posicionJugadorActual >= cantidadJugadores){
        posicionJugadorActual = 0;
    }

    etapaActual = ETAPA_OBTENER_UNIDADES;
}