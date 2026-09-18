#include "Jugador.h"

// Crea un jugador con el nombre y el color vacios.
// La secuencia de cartas comienza vacia.
Jugador::Jugador()
    : nombre(""), color(""), cartas() {
}

// Crea un jugador con el nombre y el color recibidos.
// La secuencia de cartas comienza vacia.
Jugador::Jugador(string nuevoNombre, string nuevoColor)
    : nombre(nuevoNombre), color(nuevoColor), cartas() {
}

// Retorna el nombre guardado del jugador.
string Jugador::obtenerNombre() const {
    return nombre;
}

// Retorna el color que identifica al jugador.
string Jugador::obtenerColor() const {
    return color;
}

// Agrega una nueva carta al final de la secuencia.
// Se recibe por referencia para evitar copiar toda la carta y const evita modificarla.
void Jugador::agregarCarta(const Carta& nuevaCarta) {
    cartas.push_back(nuevaCarta);
}

// Devuelve las cartas por referencia para poder modificarlas sin copiar todo el vector.
vector<Carta>& Jugador::obtenerCartas() {
    return cartas;
}

// Devuelve las cartas por referencia sin copiarlas.
// const evita que las cartas se puedan modificar desde esta funcion.
const vector<Carta>& Jugador::obtenerCartas() const {
    return cartas;
}