#ifndef MAZO_H
#define MAZO_H
#include <vector>
#include "Carta.h"
using namespace std;

class Jugador;
class Tablero;

class Mazo {

private:

    // Guarda las cartas que todavia pueden entregarse.
    vector<Carta> cartasDisponibles;

    // Cuenta los intercambios realizados entre todos los jugadores.
    int cantidadIntercambios;

public:

    Mazo();

    void inicializarMazo();

    // El const indica que la funcion consulta el mazo
    // pero no modifica sus atributos.
    bool tieneCartasDisponibles() const;

    // El jugador se recibe por referencia porque se agrega
    // la carta directamente a su vector de cartas.
    bool entregarCarta(Jugador& jugador);

    // El vector se recibe por referencia para evitar una copia.
    // Tambien tiene const porque solamente se consulta.
    bool combinacionValida(
        const vector<Carta>& cartas
    ) const;

    // Las posiciones corresponden a las tres cartas
    // seleccionadas por el jugador.
    //
    // Jugador y Tablero se reciben por referencia porque
    // el canje modifica las cartas y algunas unidades.
    int procesarIntercambio(
        Jugador& jugador,
        Tablero& tablero,
        int posicionUno,
        int posicionDos,
        int posicionTres
    );
};

#endif