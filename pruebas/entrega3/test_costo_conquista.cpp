
#include <iostream>
#include <cassert>
#include "Partida.h"

using namespace std;

int main()
{
    Partida partida;

    // no podemos consultar una partida que aun no fue inicializada
    assert(partida.costoConquista("Isa", "1.4") == JUEGO_NO_INICIALIZADO);

    // cargamos la configuracion que ya usamos en las entregas anteriores
    assert(partida.inicializar("partida.txt") == COMANDO_CORRECTO);

    // el jugador debe existir
    assert(partida.costoConquista("Pedro", "1.4") == JUGADOR_NO_VALIDO);

    // el destino debe existir
    assert(partida.costoConquista("Isa", "9.9") == TERRITORIO_NO_VALIDO);

    // validacion provisional para un destino que ya pertenece al jugador
    assert(partida.costoConquista("Isa", "1.2") == DESTINO_YA_CONTROLADO);

    // CC01 debe encontrar 1.8 -> 1.4 con costo 3
    assert(partida.costoConquista("Isa", "1.4") == COMANDO_CORRECTO);

    // CC02 debe encontrar un recorrido de dos conexiones con costo 6
    assert(partida.costoConquista("Isa", "1.3") == COMANDO_CORRECTO);

    // repetimos con otro jugador para comprobar la actualizacion de costos
    assert(partida.costoConquista("Saul", "1.2") == COMANDO_CORRECTO);

    cout << "Las pruebas iniciales de costo_conquista pasaron" << endl;

    return 0;
}
