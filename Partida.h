#ifndef PARTIDA_H
#define PARTIDA_H
#include <string>
#include <vector>
#include "Tipos.h"
#include "Jugador.h"
#include "Tablero.h"
#include "Turno.h"
#include "Ataque.h"
#include "Mazo.h"
using namespace std;
class Partida {
private:
    vector<Jugador> jugadores;
    Tablero tablero;
    Turno turno;
    Ataque ataque;
    Mazo mazo;
    bool inicializada;
    bool terminada;
    string ganador;
public:
    Partida();
    EstadoComando inicializar(string nombreArchivo);
    EstadoComando obtenerUnidades(string nombreJugador);
    EstadoComando atacar(string nombreJugador);
    EstadoComando fortificar(string nombreJugador);
    EstadoComando validarEstadoJuego() const;
    int buscarPosicionJugador(string nombreJugador) const;
    bool comprobarGanador();
    void mostrarEstadoJuego() const;
    bool estaInicializada() const;
    bool estaTerminada() const;
    string obtenerGanador() const;
};
#endif
