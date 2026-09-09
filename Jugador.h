#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>
#include <vector>
#include "Carta.h"
using namespace std;
class Jugador {
private:
    string nombre;
    string color;
    vector<Carta> cartas;
public:
    Jugador();
    Jugador(string nuevoNombre, string nuevoColor);
    string obtenerNombre() const;
    string obtenerColor() const;
    void agregarCarta(const Carta& nuevaCarta);
    vector<Carta>& obtenerCartas();
    const vector<Carta>& obtenerCartas() const;
    string getNombre() const { 
        return nombre; 
    }
    string getColor() const { 
        return color; 
    }
};
#endif

