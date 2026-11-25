
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include "Partida.h"

using namespace std;

int main()
{
    Partida partida;

    // no se puede consultar una partida sin inicializar
    assert(partida.conquistaMasBarata("Isa") == JUEGO_NO_INICIALIZADO);

    assert(partida.inicializar("partida.txt") == COMANDO_CORRECTO);

    // rechazamos a un jugador que no existe
    assert(partida.conquistaMasBarata("Pedro") == JUGADOR_NO_VALIDO);

    // guardamos el texto para revisar tanto el recorrido como el costo
    ostringstream salidaIsa;
    streambuf *salidaOriginal = cout.rdbuf(salidaIsa.rdbuf());

    EstadoComando estadoIsa = partida.conquistaMasBarata("Isa");

    cout.rdbuf(salidaOriginal);

    assert(estadoIsa == COMANDO_CORRECTO);

    string textoIsa = salidaIsa.str();

    assert(textoIsa.find("territorio 4.2 desde el territorio 4.3") != string::npos);
    assert(textoIsa.find("pasando por los territorios 4.2") != string::npos);
    assert(textoIsa.find("Debe conquistar 2 unidades de ejercito") != string::npos);

    cout << "Resultado para Isa:\n" << textoIsa << endl;

    // volvemos a calcular desde la perspectiva de otro jugador
    ostringstream salidaSaul;
    salidaOriginal = cout.rdbuf(salidaSaul.rdbuf());

    EstadoComando estadoSaul = partida.conquistaMasBarata("Saul");

    cout.rdbuf(salidaOriginal);

    assert(estadoSaul == COMANDO_CORRECTO);

    string textoSaul = salidaSaul.str();

    assert(textoSaul.find("territorio 4.3 desde el territorio 4.2") != string::npos);
    assert(textoSaul.find("pasando por los territorios 4.3") != string::npos);
    assert(textoSaul.find("Debe conquistar 2 unidades de ejercito") != string::npos);

    cout << "Resultado para Saul:\n" << textoSaul << endl;

    // comprobamos que cambiar de jugador no altera el resultado de Isa
    ostringstream salidaIsaOtraVez;
    salidaOriginal = cout.rdbuf(salidaIsaOtraVez.rdbuf());

    EstadoComando estadoRepetido = partida.conquistaMasBarata("Isa");

    cout.rdbuf(salidaOriginal);

    assert(estadoRepetido == COMANDO_CORRECTO);
    assert(salidaIsaOtraVez.str() == textoIsa);

    cout << "Las pruebas iniciales de conquista_mas_barata pasaron" << endl;

    return 0;
}
