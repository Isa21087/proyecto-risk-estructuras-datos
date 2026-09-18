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

    // Guarda los jugadores que participan en la partida.
    vector<Jugador> jugadores;

    // Guarda la informacion de los continentes y territorios del juego.
    Tablero tablero;

    // Controla el jugador actual y la etapa del turno.
    Turno turno;

    // Se encarga de las acciones y validaciones realizadas durante un ataque.
    Ataque ataque;

    // Guarda las cartas utilizadas durante la partida.
    Mazo mazo;

    // Indica si la partida ya fue inicializada correctamente.
    bool inicializada;

    // Indica si la partida ya termino.
    bool terminada;

    // Guarda el nombre del jugador que gano la partida.
    string ganador;

public:

    // Crea una partida con su estado inicial.
    Partida();

    // Inicializa la partida utilizando la informacion de un archivo.
    EstadoComando inicializar(string nombreArchivo);

    // Calcula y permite ubicar las unidades que puede reclamar un jugador.
    EstadoComando obtenerUnidades(string nombreJugador);

    // Ejecuta la etapa de ataque del jugador indicado.
    EstadoComando atacar(string nombreJugador);

    // Permite trasladar unidades entre territorios propios durante la fortificacion.
    EstadoComando fortificar(string nombreJugador);

    // Verifica si el estado actual permite consultar la informacion de la partida.
    EstadoComando validarEstadoJuego() const;

    // Busca la posicion de un jugador dentro de la secuencia usando su nombre.
    // Retorna -1 si el jugador no existe.
    int buscarPosicionJugador(string nombreJugador) const;

    // Comprueba si algun jugador controla todos los territorios y gano la partida.
    bool comprobarGanador();

    // Muestra la informacion actual de la partida sin modificarla.
    void mostrarEstadoJuego() const;

    // Retorna si la partida fue inicializada correctamente.
    bool estaInicializada() const;

    // Retorna si la partida ya termino.
    bool estaTerminada() const;

    // Retorna el nombre del ganador de la partida.
    string obtenerGanador() const;
};

#endif