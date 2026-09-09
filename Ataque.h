#ifndef ATAQUE_H
#define ATAQUE_H
#include <string>
#include "Tipos.h"
#include "Dados.h"
using namespace std;
class Jugador;
class Tablero;
class Ataque {
private:
    Dados dadosAtacante;
    Dados dadosDefensor;
public:
    Ataque();
    bool configuracionValida(
        string codigoOrigen,
        string codigoDestino,
        string colorAtacante,
        const Tablero& tablero
    ) const;
    ResultadoAtaque ejecutar(
        Jugador& jugadorAtacante,
        Tablero& tablero
    );
};
#endif
