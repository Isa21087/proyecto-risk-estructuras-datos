#include "Partida.h"

Partida::Partida()
    : jugadores(),
      tablero(),
      turno(),
      ataque(),
      mazo(),
      inicializada(false),
      terminada(false),
      ganador("") {
}

Jugador* Partida::buscarJugador(string nombreJugador) {
    for (Jugador& jugador : jugadores) {
        if (jugador.obtenerNombre() == nombreJugador) {
            return &jugador;
        }
    }

    return nullptr;
}

const Jugador* Partida::buscarJugador(string nombreJugador) const {
    for (const Jugador& jugador : jugadores) {
        if (jugador.obtenerNombre() == nombreJugador) {
            return &jugador;
        }
    }

    return nullptr;
}

int Partida::buscarPosicionJugador(string nombreJugador) const {
    for (size_t i = 0; i < jugadores.size(); i++) {
        if (jugadores[i].obtenerNombre() == nombreJugador) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

bool Partida::estaInicializada() const {
    return inicializada;
}

bool Partida::estaTerminada() const {
    return terminada;
}

string Partida::obtenerGanador() const {
    return ganador;
}
