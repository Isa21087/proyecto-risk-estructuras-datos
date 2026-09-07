#include "Partida.h"

Partida::Partida() {
    // Al crear una partida, todavia no ha comenzado ni ha terminado.
    inicializada = false;
    terminada = false;
    ganador = "";
}

int Partida::buscarPosicionJugador(string nombreJugador) const {
    int posicion = 0;

    // Recorre los jugadores buscando el nombre recibido.
    for (const Jugador& jugador : jugadores) {
        if (jugador.obtenerNombre() == nombreJugador) {
            // Devuelve la posicion donde encontro al jugador.
            return posicion;
        }

        posicion++;
    }

    // Devuelve -1 cuando el jugador no existe.
    return -1;
}

bool Partida::estaInicializada() const {
    // Informa si la partida ya fue inicializada.
    return inicializada;
}

bool Partida::estaTerminada() const {
    // Informa si la partida ya termino.
    return terminada;
}

string Partida::obtenerGanador() const {
    // Devuelve el nombre del ganador.
    return ganador;
}