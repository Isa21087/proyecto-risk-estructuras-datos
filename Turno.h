#ifndef TURNO_H
#define TURNO_H
// Se necesita porque Turno recibe codigos de territorios como string.
#include <string>
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

    // El const al final indica que la funcion
    // no modifica los atributos de Turno.
    int obtenerPosicionJugadorActual() const;

    EtapaTurno obtenerEtapaActual() const;

    bool esTurnoDe(int posicionJugador) const;

    bool puedeObtenerUnidades() const;

    bool puedeAtacar() const;

    bool puedeFortificar() const;

    // El & evita crear copias del jugador y del tablero.
    // El const evita modificarlos durante el calculo.
    int calcularNuevasUnidades(
        const Jugador& jugador,
        const Tablero& tablero,
        int bonificacionCartas
    ) const;

    // El tablero se recibe por referencia sin const
    // porque sus unidades deben modificarse.
    bool ejecutarObtencionUnidades(
        const Jugador& jugador,
        Tablero& tablero,
        string codigoTerritorio,
        int cantidad
    );

    void registrarUnidadesObtenidas();

    void registrarAtaqueTerminado();

    // El jugador se recibe con const porque solo necesitamos
    // consultar su color. El tablero si debe modificarse.
    bool ejecutarFortificacion(
        const Jugador& jugador,
        Tablero& tablero,
        string codigoOrigen,
        string codigoDestino,
        int cantidad
    );

    void finalizarTurno(int cantidadJugadores);
};

#endif