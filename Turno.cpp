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
    
}
    bool ejecutarObtencionUnidades(
        Jugador& jugador,
        Tablero& tablero,
        int bonificacionCartas
    );
    void registrarAtaqueTerminado();
    bool ejecutarFortificacion(
        Jugador& jugador,
        Tablero& tablero
    );
    void finalizarTurno(int cantidadJugadores);
