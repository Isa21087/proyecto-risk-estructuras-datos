#ifndef TURNO_H
#define TURNO_H
#include "Tipos.h"
using namespace std;
class Jugador;
class Tablero;
class Turno {
private:
    int posicionJugadorActual;
    EtapaTurno etapaActual;
public:
    Turno();
    void iniciar(int primeraPosicion);
    int obtenerPosicionJugadorActual() const;
    EtapaTurno obtenerEtapaActual() const;
    bool esTurnoDe(int posicionJugador) const;
    bool puedeObtenerUnidades() const;
    bool puedeAtacar() const;
    bool puedeFortificar() const;
    int calcularNuevasUnidades(
        const Jugador& jugador,
        const Tablero& tablero,
        int bonificacionCartas
    ) const;
    bool ejecutarObtencionUnidades(
        Jugador& jugador,
        Tablero& tablero,
        int bonificacionCartas,
        string codigoTerritorio
    );
    void registrarAtaqueTerminado();
    bool ejecutarFortificacion(
        Jugador& jugador,
        Tablero& tablero,
        string codigoOrigen,
        string codigoDestino,
        int cantidad
    );
    void finalizarTurno(int cantidadJugadores);
};
#endif
