#include "Turno.h"
#include "Tipos.h"
#include "Jugador.h"
#include "Tablero.h"

//Constructor de Turno
Turno::Turno()
    : posicionJugadorActual(0),
      etapaActual(ETAPA_OBTENER_UNIDADES)
{
}
void Turno::iniciar(int primeraPosicion) {
    posicionJugadorActual = primeraPosicion;
    etapaActual = ETAPA_OBTENER_UNIDADES;
}
int Turno::obtenerPosicionJugadorActual() const{
    return posicionJugadorActual;
}

EtapaTurno Turno::obtenerEtapaActual() const{
    return etapaActual;
}

bool Turno::esTurnoDe(int posicionJugador) const{
    if(posicionJugador != posicionJugador){
        return false;
    }
    return true;
}

bool Turno::puedeObtenerUnidades() const{
    if(etapaActual == ETAPA_OBTENER_UNIDADES){
        return false;
    }
    return true;
}

bool Turno::puedeAtacar() const{
    if(etapaActual != ETAPA_ATACAR){
        return false;
    }
    return true;
}

bool Turno::puedeFortificar() const{
    if(etapaActual != ETAPA_FORTIFICAR){
        return false;
    }
    return true;
}

int Turno::calcularNuevasUnidades(const Jugador& jugador, const Tablero& tablero, int bonificacionCartas) const{
    //Se crea una variable temporal
    int undsT=0;

    //Se calcula la cantidad de unidades que se van a obtener por territorio
    undsT = (tablero.sumarUnidades(jugador.obtenerColor()))/3;

    //Si la cantidad calculada es menor a 3, segun el enunciado solo se pueden ganar 3 unidades minimo
    if(undsT < 3){
        undsT = 3;
    }
    //calucla si tiene bonificacion por continentes y lo suma a la temporal
    undsT += tablero.calcularBonificacionContinentes(jugador.obtenerColor());

    //Retorna la suma del total que se tenia antes mas la bonificacion de las cartas
    return undsT + bonificacionCartas;

}

bool Turno::ejecutarObtencionUnidades(Jugador& jugador, Tablero& tablero, int bonificacionCartas, string codigoTerritorio){
    //Verifica si puede obetner unidades
    return puedeObtenerUnidades();

    //Calcula la cantidad de unidades que se obtienen
    int unds = calcularNuevasUnidades(jugador, tablero, bonificacionCartas);

    //asigna las unidades obtenidas a un territorio elegido por el jugador
    tablero.agregarUnidades(codigoTerritorio, jugador.obtenerColor(), unds);

    //Termina la fase de obtener unidades y comienza la fase de ataque
    etapaActual=ETAPA_ATACAR;

    return true;
}
void Turno::registrarAtaqueTerminado(){
    etapaActual=ETAPA_OBTENER_UNIDADES;
}
bool Turno::ejecutarFortificacion(Jugador& jugador, Tablero& tablero, string codigoOrigen, string codigoDestino, int cantidad){
    if(etapaActual!= ETAPA_FORTIFICAR){ //verificar que la etapa este correcta
        return false;
    }

    //Verifica si se pudieron trasladar las unidades 
    if(!tablero.trasladarUnidades(codigoOrigen, codigoDestino, jugador.obtenerColor(), cantidad, 1)){
        return false;
    }

    return true;
}

void Turno::finalizarTurno(int cantidadJugadores){
    //pasa al siguiente jugador
    ++posicionJugadorActual;
    //Verifica si existe siguiente jugador
    if(posicionJugadorActual >= cantidadJugadores){
        //Si no hay siguiente jugador, vuelve con el jugador inicial
        posicionJugadorActual = 0;
    }

    //vuelve a la etapa inicial
    etapaActual = ETAPA_OBTENER_UNIDADES;
}
