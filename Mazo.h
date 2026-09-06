#ifndef MAZO_H
#define MAZO_H
#include <vector>
#include "Carta.h"
using namespace std;
class Jugador;
class Tablero;
class Mazo {
private:
    vector<Carta> cartasDisponibles;
    int cantidadIntercambios;
public:
    Mazo();
    void inicializarMazo();
    bool tieneCartasDisponibles() const;
    bool entregarCarta(Jugador& jugador);
    bool combinacionValida(const vector<Carta>& cartas) const;
    int procesarIntercambio(
        Jugador& jugador,
        Tablero& tablero
    );
};
#endif
