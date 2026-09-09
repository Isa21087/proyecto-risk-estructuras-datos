#include "Jugador.h"

Jugador::Jugador()
    : nombre(""), color(""), cartas() {
}

Jugador::Jugador(string nuevoNombre, string nuevoColor)
    : nombre(nuevoNombre), color(nuevoColor), cartas() {
}

string Jugador::obtenerNombre() const {
    return nombre;
}

string Jugador::obtenerColor() const {
    return color;
}

void Jugador::agregarCarta(const Carta& nuevaCarta) {
    cartas.push_back(nuevaCarta);
}

vector<Carta>& Jugador::obtenerCartas() {
    return cartas;
}

const vector<Carta>& Jugador::obtenerCartas() const {
    return cartas;
}